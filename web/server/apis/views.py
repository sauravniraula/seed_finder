import ctypes
from django.http import JsonResponse, Http404
from django.shortcuts import render
from django.views.decorators.csrf import csrf_exempt
from rest_framework.parsers import JSONParser
from django.core.files import File

from .models import CustomSeed, Version

from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework import permissions
from rest_framework.renderers import TemplateHTMLRenderer
from .serializers import CustomSpawnSerializer

import random, json, zipfile, os
from .decorators import allow_post
from .extras import Sbiomes

base_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

@csrf_exempt
@allow_post
def get_better_seeds(request):
  version = JSONParser().parse(request)
  mc_version = Version.objects.get(**version)
  better_seeds_files = mc_version.betterseed_set.all()
  total_available_files = len(better_seeds_files)
  selected_file = better_seeds_files[random.randint(0, total_available_files - 1)]

  with open(base_dir + "/media/" + selected_file.seed_file.name, 'r') as file_opened:
    seeds = json.loads(file_opened.read())

  total_seeds = len(seeds)
  selected_seeds = []

  if total_seeds == 0:
    raise Http404('Not Found')

  random_num = random.randint(0, total_seeds - 1)
  selected_seeds = seeds[random_num: random_num + 20 if total_seeds > 20 else total_seeds]

  return JsonResponse({ "seeds" : selected_seeds })    


@csrf_exempt
@allow_post
def get_seed_info(request, seed):
  version = int(JSONParser().parse(request)['version'])
  height = 100
  area = 3000
  biome_info = {}

  shared_file_path = base_dir + '/media/shared/shared_python.so'
  cfunc = ctypes.CDLL(shared_file_path)  

  cfunc.getBiomeInfo.restype = Sbiomes
  biome_info_arr = cfunc.getBiomeInfo(ctypes.c_uint64(seed), ctypes.c_int(version), ctypes.c_int(height), ctypes.c_int(area))

  for i in range(biome_info_arr.totalBiomes):
    biome_info[biome_info_arr.biomeInfoArr[i][2]] = [ biome_info_arr.biomeInfoArr[i][0],  biome_info_arr.biomeInfoArr[i][1] ]

  return JsonResponse({ "seed" : seed, "spawn" : [ biome_info_arr.spawn[0], biome_info_arr.spawn[1] ], "spawnOn": biome_info_arr.spawnOn, "totalBiomes": biome_info_arr.totalBiomes , "detail" : biome_info })



@csrf_exempt
@allow_post
def get_custom_seeds(request):
  data = JSONParser().parse(request)
  mc_version = Version.objects.get(version=data['version'])

  try:
    custom_seeds_file = mc_version.customseed_set.get(biome_id=data["biome_id"])
  except CustomSeed.DoesNotExist:
    raise Http404("Not Found")

  with open(base_dir + "/media/" + custom_seeds_file.seed_file.name, 'r') as file_opened:
    seeds = json.loads(file_opened.read())

  total_seeds = len(seeds)
  selected_seeds = []

  if total_seeds == 0:
    raise Http404('Not Found')

  random_num = random.randint(0, total_seeds - 20)
  selected_seeds = seeds[random_num:random_num + 20 if total_seeds > 20 else total_seeds]

  return JsonResponse({ "seeds" : selected_seeds })





class AddCustomSpawnData(APIView):
  permission_classes = [permissions.IsAdminUser]
  renderer_classes = [TemplateHTMLRenderer]
  template_name = 'apis/custom-spawn-form.html'

  def get(self, request):
    return Response({'serializer': CustomSpawnSerializer()})

  def post(self, request):
    file = request.FILES['files']
    version = request.data['version']
    dir_ = base_dir + "/temp/" + version + "/"

    with zipfile.ZipFile(file, 'r') as zip_ref:
      zip_ref.extractall(dir_)

    names = os.listdir(dir_)

    for each in names:
      with open(dir_ + each, 'rb') as temp_file:
        version_fk = Version.objects.get(version=version)
        django_file = File(temp_file)
        django_file.name = django_file.name.split("/")[1:]
        django_file.name = "/".join(django_file.name)
        CustomSeed.objects.create(better_seeds_id=version_fk, biome_id=each.split(".")[0], seed_file=django_file)
        os.remove(dir_ + each)
      
    os.rmdir(base_dir + "/temp/" + version)

    return Response({'serializer': CustomSpawnSerializer()})
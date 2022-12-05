from django.http import JsonResponse
import json

def send_json_message(message):
  return JsonResponse(json.dumps({ "message" : message }))

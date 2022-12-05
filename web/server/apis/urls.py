from django.urls import path

from .views import *

urlpatterns = [
  path("get-seeds", get_better_seeds),
  path("seed/<int:seed>", get_seed_info),
  path("get-custom-seeds", get_custom_seeds),
  path("add-custom-spawn-data", AddCustomSpawnData.as_view())
]
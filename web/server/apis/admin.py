from django.contrib import admin
from .models import Version, BetterSeed, CustomSeed

admin.site.register(Version)
admin.site.register(BetterSeed)
admin.site.register(CustomSeed)
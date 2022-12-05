from rest_framework import serializers

class CustomSpawnSerializer(serializers.Serializer):
  version = serializers.IntegerField()
  files = serializers.FileField()


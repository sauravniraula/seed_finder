from django.db import models

class Version(models.Model):
  version = models.IntegerField()

  def __str__(self):
    return str(self.version);

class BetterSeed(models.Model):
  better_seeds_id = models.ForeignKey(Version, on_delete=models.CASCADE)
  seed_file = models.FileField(upload_to='betterSeeds/')

  def __str__(self):
    name = self.seed_file.name.split(".")[0]
    return name.split("/")[1]

class CustomSeed(models.Model):
  better_seeds_id = models.ForeignKey(Version, on_delete=models.CASCADE)
  biome_id = models.IntegerField()
  seed_file = models.FileField(upload_to='customSeeds/')

  def __str__(self):
    return f'{self.better_seeds_id.version} - {self.biome_id}'
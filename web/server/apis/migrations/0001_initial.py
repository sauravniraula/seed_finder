# Generated by Django 4.0.5 on 2022-07-03 17:11

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Version',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('version', models.IntegerField()),
            ],
        ),
        migrations.CreateModel(
            name='CustomSeed',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('seed_file', models.FileField(upload_to='customSeeds/')),
                ('better_seeds_id', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='apis.version')),
            ],
        ),
        migrations.CreateModel(
            name='BetterSeed',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('seed_file', models.FileField(upload_to='betterSeeds/')),
                ('better_seeds_id', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='apis.version')),
            ],
        ),
    ]
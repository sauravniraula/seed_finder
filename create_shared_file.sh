#! /bin/bash

gcc -shared -fPIC -o minecraft_biome_shared.so ./cubiomes/*.o cubiome_add_func.o
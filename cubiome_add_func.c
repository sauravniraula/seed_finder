#include "./cubiomes/generator.h"
#include "./cubiomes/finders.h"
#include <stdio.h>
#include <stdlib.h>


int get_biome_id(uint64_t seed, int version, int x, int y, int z) {
    Generator g;
    setupGenerator(&g, version, 0);
    applySeed(&g, 0, seed);
     
    return getBiomeAt(&g, 1, x, y, z);
}

int get_spawn_x(uint64_t seed, int version) {
    Generator g;
    setupGenerator(&g, version, 0);
    applySeed(&g, 0, seed);

    return getSpawn(&g).x;
}

int get_spawn_z(uint64_t seed, int version) {
    Generator g;
    setupGenerator(&g, version, 0);
    // applySeed(&g, 0, strtoul(seed, NULL, 10));
    applySeed(&g, 0, seed);

    return getSpawn(&g).z;
}

// int main() {
//     uint64_t seed = 9999999999;
//     printf("%d", get_biome_id(seed, 18, 0, 60, 0));
//     return 0;
// }
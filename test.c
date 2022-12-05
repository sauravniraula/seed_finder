#include "./cubiomes/generator.h"
#include <stdio.h>

int main() {
    Generator g;
    setupGenerator(&g, MC_1_18, 0);

    uint64_t seed = 186864;
    applySeed(&g, 0, seed);

    int biomeId = getBiomeAt(&g, 1, 0, 60, 0);
    printf("%d", biomeId);

    return 0;
}
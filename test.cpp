#include "./cubiomes/generator.h"
#include "iostream"

using namespace std;

int main() {
    Generator g;
    setupGenerator(&g, MC_1_18, 0);

    uint64_t seed = 1;
    applySeed(&g, 0, seed);

    int biomeId = getBiomeAt(&g, 1, 1408, 63, 2928);
    cout << biomeId;

    return 0;
}

#include "../cubiomes/generator.h"
#include "../cubiomes/finders.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


typedef struct biomeStruct {
  int biomeInfoArr[100][3];
  int spawn[2];
  int spawnOn;
  int totalBiomes;
} Sbiomes;

typedef struct customSeeds {
  int seeds[20];
  int totalSeeds;
} CustomSeeds;


int checkIfPresent(int biomeInfo[100][3], int tot, int biomeId) {
  int found = -99;
  for(int i = 0; i<tot; i++) {
    if(biomeInfo[i][2] == biomeId) {
      found = i;
    }
  }
  return found;
}

int getEuclideanDistance(int* x, int* y) {
  int distance;
  distance = sqrt(pow(x[0]-y[0], 2) + pow(x[1] - y[1], 2));
  return distance;
}

Sbiomes getBiomeInfo(uint64_t seed, int version, int height, int area) {
  Generator g;
  setupGenerator(&g, version, 0);
  applySeed(&g, 0, seed);


  Pos spawnPos = getSpawn(&g);

  Sbiomes bInfo;
  bInfo.spawn[0] = spawnPos.x,
  bInfo.spawn[1] = spawnPos.z,
  bInfo.spawnOn = getBiomeAt(&g, 1, bInfo.spawn[0], height, bInfo.spawn[1]);
  bInfo.totalBiomes = 0;

  int modifiedArea = (area * 2) / 16;
  int x = bInfo.spawn[0] - area;
  int z = bInfo.spawn[1] - area;

  for (int i=0; i<=modifiedArea; i++)  {
    for (int j=0; j<=modifiedArea; j++) {

      int biomeId = getBiomeAt(&g, 1, x, height, z);
      int found = checkIfPresent(bInfo.biomeInfoArr, bInfo.totalBiomes, biomeId);
      if(found > -99) {
        int oldCoords[2], newCoords[2];
        oldCoords[0] = bInfo.biomeInfoArr[found][0];
        oldCoords[1] = bInfo.biomeInfoArr[found][1];
        newCoords[0] = x;
        newCoords[1] = z;

        int dist = getEuclideanDistance(bInfo.spawn, oldCoords) - getEuclideanDistance(bInfo.spawn, newCoords);
        if(dist > 0) {
          bInfo.biomeInfoArr[found][0] = newCoords[0];
          bInfo.biomeInfoArr[found][1] = newCoords[1];
        }
      }
      else {
        bInfo.biomeInfoArr[bInfo.totalBiomes][0] = x;
        bInfo.biomeInfoArr[bInfo.totalBiomes][1] = z;
        bInfo.biomeInfoArr[bInfo.totalBiomes][2] = biomeId;
        bInfo.totalBiomes++;
      }

      z += 16;
    }
    x += 16;
    z = bInfo.spawn[1] - area;
  }

  return bInfo;

}

CustomSeeds get_custom_seeds(int id, int version, int height) {

  Generator g;
  setupGenerator(&g, version, 0);

  srand(time(0));
  uint64_t seed = rand();

  CustomSeeds Cseeds;
  Cseeds.totalSeeds = 0;

  while(Cseeds.totalSeeds != 10) {
    applySeed(&g, 0, seed);
    Pos spawn = getSpawn(&g);
    int biomeId = getBiomeAt(&g, 1, spawn.x, height, spawn.z);
    if(biomeId == id) {
      Cseeds.seeds[Cseeds.totalSeeds] = seed;
      Cseeds.totalSeeds++;
    }
    seed++;
  }
}


int main() {
//   Sbiomes biomeInf;
//   biomeInf = getBiomeInfo(9999, 18, 100, 1000);

//   for(int i=0; i<100;i++) {
//     printf("( %d , %d ) - %d \n", biomeInf.biomeInfoArr[i][0], biomeInf.biomeInfoArr[i][1], biomeInf.biomeInfoArr[i][2]);
//   }

  // get_custom_seeds(4, 18, 100);

  return 1;
}
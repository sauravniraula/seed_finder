#include "world.h"

string minecraft_biomes[200] = { 
  "ocean",
  "plains",
  "desert",
  "windswept_hills",
  "forest",
  "taiga",
  "swamp",
  "river",
  "nether_wastes",
  "the_end",
  "frozen_ocean",
  "frozen_river",
  "snowy_plains",
  "snowy_mountains",
  "mushroom_fields",
  "mushroom_field_shore",
  "beach",
  "desert_hills",
  "wooded_hills",
  "taiga_hills",
  "mountain_edge",
  "jungle",
  "jungle_hills",
  "sparse_jungle",
  "deep_ocean",
  "stony_shore",
  "snowy_beach",
  "birch_forest",
  "birch_forest_hills",
  "dark_forest",
  "snowy_taiga",
  "snowy_taiga_hills",
  "old_growth_pine_taiga",
  "giant_tree_taiga_hills",
  "windswept_forest",
  "savanna",
  "savanna_plateau",
  "badlands",
  "wooded_badlands",
  "badlands_plateau",
  "small_end_islands",
  "end_midlands",
  "end_highlands",
  "end_barrens",
  "warm_ocean",
  "lukewarm_ocean",
  "cold_ocean",
  "deep_warm_ocean",
  "deep_lukewarm_ocean",
  "deep_cold_ocean",
  "deep_frozen_ocean",  //50
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
  "the_void",
  "",
  "sunflower_plains",   // 129
  "desert_lakes",
  "windswept_gravelly_hills",
  "flower_forest",
  "taiga_mountains",
  "swamp_hills",
  "", "", "", "", "",
  "ice_spikes",
  "", "", "", "", "", "", "", "",
  "modified_jungle",
  "",
  "modified_jungle_edge",
  "", "", "",
  "old_growth_birch_forest",
  "tall_birch_hills",
  "dark_forest_hills",
  "snowy_taiga_mountains",
  "",
  "old_growth_spruce_taiga",
  "giant_spruce_taiga_hills",
  "modified_gravelly_mountains",
  "windswept_savanna",
  "shattered_savanna_plateau",
  "eroded_badlands",
  "modified_wooded_badlands_plateau",
  "modified_badlands_plateau" ,
  "bamboo_jungle" ,
  "bamboo_jungle_hills",
  "soul_sand_valley" ,
  "crimson_forest" ,
  "warped_forest"  ,
  "basalt_deltas",
  "dripstone_caves",
  "lush_caves",
  "",
  "meadow",
  "grove" ,
  "snowy_slopes",
  "jagged_peaks",
  "frozen_peaks",
  "stony_peaks",
};

void World::initializeWorld() {
  setupGenerator(&generator, version , 0);
}
void World::initializeSeed() {
  applySeed(&generator, 0, seed);
}
void World::changeSeed(uint64_t newSeed) {
  seed = newSeed;
  initializeSeed();
}
void World::changeVersion(int version) {
  version = version;
  updateWorld();
}
void World::updateWorld() {
  initializeWorld();
  initializeSeed();
}
Generator World::getGenerator() {
  return generator;
}
int World::biomeAt(int x, int y, int z) {
  return getBiomeAt(&generator, 1, x, y, z);
}
int* World::getWorldSpawn() {
  Pos spawnPos = getSpawn(&generator);
  // int* pos = new int[2];
  // pos[0] = spawnPos.x;
  // pos[1] = spawnPos.z;
  // or
  int* pos = ( int *) malloc (2 * sizeof(int));
  *pos = spawnPos.x;
  *(pos+1) = spawnPos.z;
  return pos;
}

void World::scanArea(int area, bool detailed) {
  int* spawn = getWorldSpawn(); 
  int chunkDivision = 16;

  generateBiomeInfo(area, spawn, detailed);
}

void World::generateBiomeInfo(int area, int* spawn, bool detailed) {

  if(detailed) {
    biomeInfo.clear();    // clearing the map containing biomeInfo
  }
  else {
    biomes.clear();
  }


  int modifiedArea = int((area * 2) / 16);
  int x = spawn[0] - area;
  int z = spawn[1] - area;

  for (int i=0; i<=modifiedArea; i++)  {
    for (int j=0; j<=modifiedArea; j++) {

      if(detailed) {    // if detailed info is needed of the biome
        vector<int> v1;
        v1.push_back(x);
        v1.push_back(z);
        int biomeId = biomeAt(x, 60, z);
        if(checkKey(biomeInfo, biomeId)) {
          auto oldBiome = biomeInfo.find(biomeId);
          int oldBiomeCoords[2] = { oldBiome->second[0], oldBiome->second[1] };
          int currentBiomeCoords[2] = { v1[0], v1[1] };
          int oldDistance = getEuclideanDistance(spawn, oldBiomeCoords);
          int newDistance = getEuclideanDistance(spawn, currentBiomeCoords);
          if(oldDistance > newDistance) {
            biomeInfo.erase(oldBiome);
            biomeInfo[biomeId] = v1;
          }
        }
        else {
          biomeInfo[biomeId] = v1;
        }
      }

      else {    // if only info about number of biomes and type is needed
        int biomeId = biomeAt(x, 60, z);
        if(!searchElement(&biomes, biomeId)) {
          biomes.push_back(biomeId);
        }
      }

      z += 16;
    }
    x += 16;
    z = spawn[1] - area;
  }
}

uint64_t World::getSeed() {
  return seed;
}

int World::getSpawnBiome() {
  int *coords = getWorldSpawn();
  return biomeAt(coords[0], 100, coords[1]);
}

int totalBiomes(vector<int> biomes) {
  return biomes.size();
}

string biomesToJson(vector<int> biomes, uint64_t seed, int spawnBiome, int totBiomes) {

  string str = "{";
  str += "\"seed\" : " + to_string(seed) + ", ";
  str += "\"spawnAt\" : " + to_string(spawnBiome) + ", ";
  str += "\"totalBiomes\" : " + to_string(totBiomes);
  // str += "\"totalBiomes\" : " + to_string(totBiomes) + ", ";
  // str += "\"details\" : [ ";
  // vector<int>::iterator itr; 
  // for(itr = biomes.begin(); itr !=biomes.end();itr++) {
  //   if(itr != biomes.begin()) {
  //     str += ", ";
  //   }
  //   str += "\"" + to_string(*itr) + "\"";
  // }
  // str += "] }";
  str += "}";
  return str;
}

string mapToJson(map<int, vector<int>> someMap, uint64_t seed) {
  string str = " { ";
  str += "\"seed\" : " + to_string(seed) + ", ";
  map<int, vector<int>>::iterator itr;
  for(itr=someMap.begin();itr!=someMap.end();itr++) {
    vector<int> value = itr->second;
    if(itr != someMap.begin()) {
      str += ", ";
    }
    str += "\"" + to_string(itr->first) + "\" : [" + to_string(value[0]) + "," + to_string(value[1]) + "] ";
  }
  str += "}";
  return str;
}

void printMap(map<int, vector<int>> someMap, string* minecraft_biomes) {
  map<int, vector<int>>::iterator itr;
  for(itr=someMap.begin();itr!=someMap.end();itr++) {
    vector<int> value = itr->second;
    cout<<minecraft_biomes[itr->first]<<" : [ "<< value[0] << ", " << value[1] << " ]" <<endl;
  }
}

bool searchElement(vector<int> *biomes, int ele) {
  bool isPresent = false;
  if(find(biomes->begin(), biomes->end(), ele) != biomes->end()) {
    isPresent = true;
  }
  return isPresent;
}

bool checkKey(map<int, vector<int>> someMap, int key) {
  bool isKeyPresent = false;
  if(someMap.find(key) != someMap.end()) {
    isKeyPresent = true;
  }
  return isKeyPresent;
}

int getEuclideanDistance(int* x, int* y) {
  int distance;
  distance = sqrt(pow(x[0]-y[0], 2) + pow(x[1] - y[1], 2));
  return int(distance);
}

// int main() {
  // World world = World();
  // world.initializeWorld();
  // world.initializeSeed();
  // world.getWorldSpawn();
  // world.scanArea(3000); 
  // world.printBiomeId();
// }
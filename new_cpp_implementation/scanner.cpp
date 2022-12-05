#include "iostream"
#include "world.h"
#include "chrono"
#include "thread"

using namespace std;

ofstream newFile;

void scanSeed(uint64_t seed, string *str, int version) {  // used by scanseeds
  World world = World(); 
  world.initializeWorld();
  world.changeSeed(seed);
  world.changeVersion(version);
  world.scanArea(3000, false);
  cout << "Scanned seed :- " + to_string(seed) << endl;
  if(totalBiomes(world.biomes) >= 50) {
    if(*str != "[ ") {

      newFile.open("biomes.json", ios::app);
      newFile << ", ";
      newFile.close();

      // *str += ", ";
    }
    // *str += biomesToJson(world.biomes, world.getSeed(), world.getSpawnBiome(), totalBiomes(world.biomes));
    string temp = biomesToJson(world.biomes, world.getSeed(), world.getSpawnBiome(), totalBiomes(world.biomes));
    newFile.open("biomes.json", ios::app);
    newFile << temp;
    newFile.close();
    *str = "adfasdf";
  }
}

string scanSeeds(uint64_t from, uint64_t to, int version) {   // scan seeds to find better seeds
  string str = "[ ";

  newFile.open("betterSeeds/biomes.json", ios::app);
  newFile << "[ ";
  newFile.close();

  vector<thread> threads;
  for (uint64_t seed = from; seed < to; seed++) {
    threads.push_back(thread(scanSeed, seed, &str, version));
    if(threads.size() == 8) {
      for(auto &th : threads) {
        th.join();
      }
      threads.clear();
    }
  }
  str += " ]";

  newFile.open("betterSeeds/biomes.json", ios::app);
  newFile << " ]";
  newFile.close();

  return str;
}


void getCustomSpawn(int biomeId, int version, uint64_t seedFrom, uint64_t tot, int count, bool single, bool at_0_0) {    // used by scanCustomSpawn
  World world = World();
  world.initializeWorld();
  world.changeVersion(version);

  ofstream someFile;

  string file_name = single ? to_string(biomeId) + " - " + to_string(count) + ".json" : to_string(biomeId) + ".json";

  someFile = ofstream(file_name, ios::app);
  someFile << "[ ";
  someFile.close();

  for (uint64_t i = seedFrom; i < tot; i++) {
    if(i % 1000 == 0) {
      cout << "Scanned seed :- " + to_string(i) << endl;
    }
    world.changeSeed(i);
    if(at_0_0 ? world.biomeAt(0,100,0) : world.getSpawnBiome() == biomeId) {
      someFile = ofstream(file_name, ios::app);
      someFile << "{ \"seed\": " << i << " },";
      someFile.close();
    }
  }
  someFile = ofstream(file_name, ios::app);
  someFile << " ]";
  someFile.close();
}

void scanCustomSpawns(vector<int> customBiomes, int version, uint64_t startFrom, uint64_t end, bool at_0_0) {    // scan for custom spawn
  uint64_t tot;
  tot = end - startFrom;

  vector<thread> threads;
  for(int i = 0; i < customBiomes.size(); i++) {
    threads.push_back(thread(getCustomSpawn, customBiomes[i], version, startFrom, tot, i, false, at_0_0));
    if(threads.size() == 8 || i == customBiomes.size() - 1) {
      for(auto &th : threads) {
        th.join();
      }
      threads.clear();
    }
  }
}

void scanSpawnForSingleBiome(uint64_t startFrom, uint64_t end, int version, int biomeId, bool at_0_0) {
  uint64_t tot;
  tot = end - startFrom;

  int one_thread_part = tot/8;

  vector<thread> threads;
  for(int i = 0; i < 8 ; i++) {
    threads.push_back(thread(getCustomSpawn, biomeId, version, startFrom + i * one_thread_part, startFrom + (i + 1) * one_thread_part, i, true, at_0_0));    // true for single biome scan
    if(i == 7) {
      for(auto &th : threads) {
        th.join();
      }
      threads.clear();
    }
  }
}


int main() {
  uint64_t startFrom, endAt;
  int version;
  cout << "Version : " << endl;
  cin >> version;
  cout << "Start from : " << endl;
  cin >> startFrom;
  cout << "End At : " << endl;
  cin >> endAt;
  // scanSeeds(startFrom, endAt, version);
  // vector<int> customBiomes = { 0,1,2,3,4,5,6,7,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,44,45,46,47,48,49,50,129,130,131,132,133,134,140,149,151,155,156,157,158,160,161,162,163,164,165,166,167,168,169,177,178,179,180,181,182,183,184 };
  // vector<int> customBiomes = { 183,184 };
  // scanCustomSpawns(customBiomes, version, startFrom, endAt, false);
  scanSpawnForSingleBiome(startFrom, endAt, version, 14, true);


  return 0;
}

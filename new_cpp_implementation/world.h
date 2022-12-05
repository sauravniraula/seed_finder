#ifndef WORLD_HEADER
#define WORLD_HEADER

#include "iostream"
#include "cmath"
#include "map"
#include "vector"
#include "string"
#include "algorithm"
#include "fstream"
#include "../cubiomes/generator.h"
#include "../cubiomes/finders.h"

using namespace std;

class World {
  private:
    uint64_t seed = 0;
    Generator generator;
    int version = MC_1_18;

  public:
    map<int, vector<int>> biomeInfo;    // gets the detailed biome info
    vector<int> biomes;    // gets the biomes present

    void initializeWorld();
    void initializeSeed();
    void updateWorld();
    void changeSeed(uint64_t);
    void changeVersion(int);
    uint64_t getSeed();
    Generator getGenerator();
    int biomeAt(int, int, int);
    int* getWorldSpawn();
    int getSpawnBiome();
    void scanArea(int, bool);
    void generateBiomeInfo(int, int*, bool);
};


bool checkKey(map<int, vector<int>>, int);
int getEuclideanDistance(int*, int*);
void printMap(map<int, vector<int>>, string*);
bool searchElement(vector<int>*, int);
string mapToJson(map<int, vector<int>>, uint64_t);
string biomesToJson(vector<int>, uint64_t, int, int);
int totalBiomes(vector<int>);

#endif
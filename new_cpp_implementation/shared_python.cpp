#include "world.h"


int seed_info(string seed, int version, int x, int y, int z) {
  World world = World();  
  world.changeVersion(version);
  // world.changeSeed(seed);
  return 1;
}
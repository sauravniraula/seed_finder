from ctypes import *
import time
import json
import numpy as np

shared_lib_file = '/home/random/prog/minecraft_biome_project/minecraft_biome_shared.so'
cfunc = CDLL(shared_lib_file)

# init_time = time.time()
# print(cfunc.return_biome_id(0, 0,0,0))
# print(time.time() - init_time)

# time for one chunk - 0.00011086463928222656s

# seed = 0
# height_to_check = 60
# chunk_inc = 16


def check_coords(seed, ini_coord, fin_coord, height=60, chunk_inc=16):  #check the given coords and put in right order
    delx = fin_coord[0] - ini_coord[0]
    dely = fin_coord[1] - ini_coord[1]

    if delx < 0:
        temp = ini_coord[0]
        ini_coord[0] = fin_coord[0]
        fin_coord[0] = temp

    if dely < 0:
        temp = ini_coord[1]
        ini_coord[1] = fin_coord[1]
        fin_coord[1] = temp

    return (seed, ini_coord, delx, dely, chunk_inc, height)
        


def get_biomes(seed, ini_coord, delx, dely, chunk_inc, height_to_check): #get the biomes info of a single seed

    biome_at_coords = {}
    for x in range(int(abs(delx)/chunk_inc)):
        for y in range(int(abs(dely)/chunk_inc)):
            biome_id = cfunc.return_biome_id(seed, ini_coord[0] + x * chunk_inc, height_to_check, ini_coord[1] + y * chunk_inc)
            # biome_at_coords.append([[x,y], biome_id])

            if biome_id in biome_at_coords.keys():
                biome_at_coords[biome_id].append([x,y])
            else:
                biome_at_coords[biome_id] = [[x,y]]

    return biome_at_coords


def filter_biomes_raw_data(biomes_and_coords): #fetch the nearest chunk data of biome
    filtered_data = {}
    all_keys = biomes_and_coords.keys()
    no_of_biomes = len(all_keys)
    for id in all_keys:
        biomes_and_coords[id].sort(key=sort_coords)
        filtered_data[id] = biomes_and_coords[id][0]

    return filtered_data, no_of_biomes

def sort_coords(coord):
    return coord[0] + coord[1]
        

if __name__ == '__main__':
    # ini_coord = [-3000, -3000]
    # fin_coord = [3000, 3000]
    # ini, fin, dx, dy = check_coords(ini, fin)
    # ini = time.time()
    # biome_info = get_biomes(*check_coords(0, ini_coord, fin_coord))
    # print(time.time() - ini)
    # ini = time.time()
    # biome_info, total_biomes = filter_biomes_raw_data(biome_info)
    # print(time.time()-ini)
    # data = {
    #     "data": {
    #         "biome_coordinate" : biome_info,
    #         "total_biomes" : total_biomes
    #     }
    # }

    # # print(biome_info)

    # with open("biome_info.json", "w") as f:
    #     json.dump(data, f)

    # print(cfunc.return_biome_id(np.uint64(99999999999), 0,64,0,))
    print(np.uint64(999999999).__dir__())

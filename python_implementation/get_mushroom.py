from some_func import *
import threading

# shared_lib_file = '/home/random/prog/minecraft_biome_project/minecraft_biome_shared.so'
# cfunc = ctypes.CDLL(shared_lib_file)

biomes = []
refined_data = {
    "data": {}
}

for i in range(199990, 200000):
    biome = cfunc.return_biome_id(i, 0, 60, 0)
    # if biome == 14:
    biomes.append(i)
    
    if i%10000 == 0:
        print(i)

print("total seeds = ", len(biomes))

ini_coord = [-3000, -3000]
fin_coord = [3000, 3000]

def task_for_individual_threads(each_seed, ini_coord, fin_coord):
    print("Analyzing for seed - ", each_seed)
    seed_info, total_biomes = filter_biomes_raw_data(get_biomes(*check_coords(each_seed, ini_coord, fin_coord))) 
    if total_biomes > 49:
        refined_data["data"][each_seed] = {
            "biome_coordinate" : seed_info,
            "total_biomes" : total_biomes
        }

        

all_threads = []

for each_seed in biomes:
    all_threads.append(threading.Thread(target=task_for_individual_threads, args=(each_seed, ini_coord, fin_coord,)))


for each_thread in all_threads:
    each_thread.start()

for each_thread in all_threads:
    each_thread.join()

with open("filtered_seeds.json", "a") as f:
    json.dump(refined_data,f)

# for each_seed in mushroom_biomes:
#     print("SEED:- ", each_seed)
#     seed_info, total_biomes = filter_biomes_raw_data(get_biomes(*check_coords(each_seed, ini_coord, fin_coord))) 
#     refined_data["data"][each_seed] = {
#         "biome_coordinate" : seed_info,
#         "total_biomes" : total_biomes
#     }

# with open("filtered_seeds.json", "a") as f:
#     json.dump(refined_data,f)
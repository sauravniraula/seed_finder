<template>
  <div class="seed-main minh-full relative">
    <Loader v-if="fetchingData" />
    <div v-else class="seed-main-wrapper font-semibold w-11/12 mx-auto flex flex-col pb-10">
      <span class="text-3xl md:text-4xl clr-1">Seed</span>
      <span class="text-2xl md:text-3xl mt-2">{{ params.slug }}</span>
      <span class="text-3xl md:text-4xl clr-1 mt-8">Spawn Coordinates</span>
      <span class="text-2xl md:text-3xl mt-2">{{ data.spawn[0] + ", " + data.spawn[1]}}</span>
      <span class="text-3xl md:text-4xl clr-1 mt-8">Spawn On</span>
      <span class="text-2xl md:text-3xl mt-2">{{minecraft_biomes[data.spawnOn]}}</span>
      <span class="text-3xl md:text-4xl clr-1 mt-8">Biomes with in 3000 blocks around spawn</span>
      <span class="text-xl md:text-2xl mt-4">Total Biomes : <span class="clr-1">{{data.totalBiomes}}</span></span>
      <div class="mt-5 search-main lg:w-4/5 xl:w-3/5">
        <div class="search-wrapper flex">
          <input type="text" v-model="searchText" class="w-full h-10 f1 py-1 px-2 search-box mb-2" placeholder="search biome"> 
        </div>
      </div>
      <table class="mt-4 border-collapse lg:w-4/5 xl:w-3/5">
        <thead>
          <tr class="text-xl lg:text-2xl">
            <td>Biomes</td>
            <td class="w-2/6">Nearest At</td>
          </tr>
        </thead>
        <tbody>
          <tr v-for="value,key,index in filteredData" :key="index">
            <td>{{minecraft_biomes[key]}}</td>
            <td>{{value[0] + ", " + value[1]}}</td>
          </tr>
        </tbody>
      </table>
    </div>
    <span class="copyright-message absolute clr-1 bottom-1">copyright © seedfinder</span>
  </div>
</template>

<script setup>
  import {ref, computed} from "vue";
  import newAxios from "@/mixins/axios";
  import { minecraft_biomes, selected_version } from "@/store";

  const { params } = useRoute();
  const fetchingData = ref(true);
  const data = ref();
  const searchText = ref("");

  const filteredData = computed(() => {
    let filtered = {};
    let filteredBiomes = [];
    for (const key in data.value.detail) {
      filteredBiomes.push(minecraft_biomes[key]);
    }
    filteredBiomes = filteredBiomes.filter(each => each.search(searchText.value.toLowerCase()) > -1);
    filteredBiomes = filteredBiomes.map(each => minecraft_biomes.indexOf(each));

    filteredBiomes.forEach(eachKey => {
      filtered[eachKey] = data.value.detail[eachKey]
    });

    return filtered;
  });

  function get_seed_info() {
    newAxios.post("seed/" + params.slug, { version: selected_version.value})
    .then(res => {
      data.value = res.data;
    })
    .catch()
    .finally(() => {
      fetchingData.value = false;
    })
  }

  onMounted(() => {
    get_seed_info();
  })
  

</script>

<style lang="scss" scoped>
.copyright-message {
  left: calc(50% - 100px);
}
</style>
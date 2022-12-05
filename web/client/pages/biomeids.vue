<template>
  <div class="biomeids-main minh-full">
    <div class="biomeids-main-wrapper mx-4 lg:mx-12">
      <div class="search-main lg:w-3/4 xl:w-8/12 2xl:w-2/4">
        <div class="search-wrapper flex">
          <input type="text" v-model="searchText" class="w-full h-10 f1 py-1 px-2 search-box mb-2" placeholder="search biome"> 
        </div>
      </div>
      <table class="w-full lg:w-3/4 xl:w-8/12 2xl:w-2/4 font-semibold">
        <thead>
          <tr class="text-lg lg:text-2xl">
            <td>Biome</td>
            <td class="w-3/12">Biome Id</td>
          </tr>
        </thead>
        <tbody>
          <tr v-for="each in biomes" :key="each[1]">
            <td>{{ each[1] }}</td>
            <td>{{ each[0] }}</td>
          </tr>
        </tbody>
      </table>
    </div>
  </div>
</template>

<script setup>

import { ref } from "vue";
import { minecraft_biomes } from "@/store"

const searchText = ref("");

const biomes = computed(() => {
  let temp = []
  minecraft_biomes.forEach((each, index) => {
    if(each !== "") {
      temp.push([index, each]);
    }
  })
  temp = temp.filter(each => each[1].search(searchText.value.toLowerCase()) > -1)
  return temp;
})

</script>

<style>
.search-box {
  border: 2px solid #FF7D3E;
  border-radius: 5px;
  outline: none;
}
</style>
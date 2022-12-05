<template>
  <div class="betterseeds-main minh-full bg-clr-5 relative">
    <div class="betterseeds-main-wrapper w-11/12 h-full mx-auto pt-8">
      <span class="text-4xl font-semibold clr-1 underline f1">{{ props.title }}</span>
      <RefreshLine />
      <div v-if="props.seeds" class="seeds-container mt-10 grid sm:grid-cols-2 md:grid-cols-3 lg:grid-cols-4 xl:grid-cols-5 2xl:grid-cols-6 gap-10 pb-10">
        <div v-for="eachSeed, index in seeds" :key="index" class="each-seed-box bg-white f1 font-semibold cursor-pointer">
          <nuxt-link :to="`/seed/${eachSeed.seed}`" >
            <div class="flex flex-col p-5">
              <span class="text-3xl clr-1 uppercase">Seed</span>
              <span class="mt-2">{{eachSeed.seed}}</span>
              <span class="text-3xl clr-1 mt-10">Spawn On</span>
              <span class="mt-2">{{ props.biomeId ? minecraft_biomes[props.biomeId] : minecraft_biomes[eachSeed.spawnAt] }}</span>
            </div>
          </nuxt-link>
        </div>
      </div>
    </div>
    <span class="copyright-message absolute clr-1 bottom-1 text-m">copyright © seedfinder</span>
  </div>
</template>

<script setup>

  import { minecraft_biomes } from "@/store"

  const props = defineProps(['title', 'seeds', 'biomeId']);

</script>


<style lang="scss" scoped>
.betterseeds-main-wrapper {
  max-width: 2000px;
}
.each-seed-box {
  min-height: 250px;
  filter: drop-shadow(0px 4px 4px rgba(0, 0, 0, 0.25));
}
.copyright-message {
  left: calc(50% - 100px);
}
</style>
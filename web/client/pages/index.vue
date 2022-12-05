<template>
  <div class="index-main flex flex-col justify-center">
    <div class="index-main-wrapper flex flex-col md:flex-row relative minh-full">
      <div class="index-first flex flex-col gap-8 xl:gap-10 px-4 md:px-12 min-h-full justify-center mb-10 md:mb-0">
        <h1 class="clr-1 f1 font-bold text-4xl xl:text-6xl">
          Find best seed for your new world
        </h1>
        <p class="text-xl xl:text-2xl">
          Find randomized best seeds of world with interesting structures and
          more easily reachable biomes for perfect start of new world. You can
          also find seeds with particular spawns.
        </p>
        <div class="flex flex-col gap-5">
          <div class="w-36 h-12 cursor-pointer z-10 bg-clr-3">
            <div tabindex="0" @focus="showVersionDropDown = true" @blur="slowby200ms(() => {showVersionDropDown = false})" class="clr-4 h-full flex gap-5 items-center justify-center">
              <img class="w-5" src="@/assets/img/down.svg" alt="...">
              <span class="text-lg xl:text-xl f1 ">{{versions[selected_version]}}</span>
            </div>
            <div v-show="showVersionDropDown" class="bg-clr-7 version-dropdown-wrapper py-2 max-h-44 overflow-scroll">
              <div v-for="each_version in Object.keys(versions).sort().reverse()" class="each-dropdown-item h-12 text-md xl:text-lg clr-4 f1 w-full">
                <div @click="change_version(each_version)" class="flex items-center justify-center h-full">
                  {{versions[each_version]}}
                </div>
              </div>
            </div>
          </div>
          <button @click="router.push('betterseeds')"
            class="w-60 h-16 xl:w-72 xl:h-20 bg-clr-1 text-white font-bold text-xl xl:text-2xl f1">Get Seeds</button>
        </div>
      </div>
      <div class="index-second min-h-full bg-clr-3">
        <div class="ml-4 mt-4 md:ml-6 md:mt-6 xl:ml-12 xl:mt-12 flex flex-col">
          <span class="clr-4 text-2xl xl:text-4xl font-bold f1">Favourite Picks</span>
          <ul class="favourite-picks-list clr-1 text-xl xl:text-2xl pl-6 mt-8 f1">
            <nuxt-link to="/custom-spawn/140">
              <li class="mb-2">Ice-spikes Spawn</li>
            </nuxt-link>
            <nuxt-link to="/custom-spawn/21">
              <li class="mb-2">Jungle Spawn</li>
            </nuxt-link>
            <nuxt-link to="/custom-spawn/37">
              <li >Badlands Spawn</li>
            </nuxt-link>
          </ul>
          <span class="clr-4 text-2xl xl:text-4xl font-bold mt-16 f1">Search custom spawn</span>
          <div class="mt-6 h-14 xl:h-20 w-10/12 z-10">
            <input @focus="showDropDown = true" @blur="slowby200ms(() => { showDropDown = false } )"
              class="biomeid-input h-full w-full pl-3 xl:pl-10 text-l xl:text-xl f1" v-model="biomeName" type="text"
              placeholder="enter biome name">
            <div v-if="showDropDown" class="dropdown max-h-48 bg-clr-7 px-3 pt-2 overflow-scroll">
              <div v-for="each_biome in filteredBiomeNames"
                class="each-dropdown-item clr-1 text-md xl:text-lg f1 cursor-pointer">
                <div @click="biomeName = each_biome" class="p-1">{{ each_biome }}</div>
              </div>
            </div>
          </div>
          <button @click="searchCustomSpawn" :disabled="hasBiomeNameErr" :style="{backgroundColor: hasBiomeNameErr ? 'lightgray' : ''}"
            class="f1 text-white font-bold bg-clr-1 h-12 w-40 xl:h-16 xl:w-60 mt-6 text-l xl:text-xl">Search</button>
          <span class="clr-4 text-xl xl:text-2xl font-bold mt-16 f1">Find "<span class="clr-1">biome id</span>" of
            certain biome</span>
          <button @click="router.push('biomeids')"
            class="f1 text-white font-bold bg-clr-1 h-12 w-60 xl:h-16 xl:w-72 mt-6 mb-12 md:my-6 text-l xl:text-xl">Find
            biome id</button>
        </div>
      </div>
      <div class="copyright-message absolute f1 bottom-1 clr-1 text-m">copyright © seedfinder</div>
    </div>
  </div>
</template>

<script setup>
import { ref, computed } from 'vue';
import { minecraft_biomes, versions, selected_version } from '@/store';

const router = useRouter();
const biomeName = ref('');
const showDropDown = ref(false);
const showVersionDropDown = ref(false);

const filteredBiomeNames = computed(() => {
  let filteredBiomes = minecraft_biomes.filter(each => each != "");
  filteredBiomes = filteredBiomes.filter(each => {
    return each.search(biomeName.value.toLowerCase()) > -1;
  })
  return filteredBiomes;
})

const hasBiomeNameErr = computed(() => {
  return filteredBiomeNames.value.filter(each => each === biomeName.value.toLowerCase()).length < 1;
});

function change_version(version) {
  selected_version.value = version;
  window.localStorage.setItem('version', version);
}

function slowby200ms(someFunc){
  setTimeout(() => {
    someFunc();
  }, 200)
}

function searchCustomSpawn() {
  router.push('/custom-spawn/' + minecraft_biomes.indexOf(biomeName.value));
}
</script>

<style lang="scss" scoped>
.index-first {
  flex-basis: 70%;

  p {
    width: 70%;
  }
}

.index-second {
  flex-basis: 30%;
}

.favourite-picks-list {
  list-style: disc;

  li {
    cursor: pointer;
  }
}

.biomeid-input {
  // width: 90%;

  &:focus {
    outline: 2px solid #FF7D3E;
  }
}

.each-dropdown-item:hover {
  background-color: rgb(236, 236, 236);
}

.copyright-message {
  left: calc(35% - 100px);
}

@media (max-width: 1024px) {
  .index-first {
    p {
      width: 90%;
    }
  }

  .index-second {
    flex-basis: 40%;
  }
}

@media (max-width: 768px) {
  .copyright-message {
    left: calc(50% - 91px);
  }
}
</style>
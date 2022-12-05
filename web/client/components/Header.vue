<template>
  <div class="header-main">
    <div :style="headerMainDS" class="header-main-wrapper duration-300 overflow-hidden relative flex flex-col md:flex-row px-6 lg:px-12 h-14 md:h-40 md:items-center gap-8 md:gap-0 mt-6 md:mt-0 md:justify-between">
      <img @click="isExpanded = !isExpanded" class="absolute md:hidden top-5 right-6 cursor-pointer" src="@/assets/img/hamburger.svg" alt="...">
      <nuxt-link to="/">
        <img class="logo-img" src="@/assets/img/logo.png" alt="...">
      </nuxt-link>
      <div class="flex flex-col md:flex-row gap-8 md:gap-16 lg:gap-20 ml-a text-xl lg:text-2xl">
        <nuxt-link to="/">
          <span class="f1 clr-1 cursor-pointer">Home</span>
        </nuxt-link>
        <span class="f1 clr-1 cursor-pointer">Blog</span>
        <span class="f1 clr-2 cursor-pointer">About Us</span>
      </div>
    </div>
  </div>
</template>

<script setup>

  import { computed, ref } from 'vue';
  import getScreenInfo from '@/mixins/trackScreenWidth';

  // from composables
  const { _, isMobile } = getScreenInfo();

  const isExpanded = ref(false);
  const headerMainDS = computed(() => {
    let style = {
      height: '90px'
    }
    if(isExpanded.value) style.height = '270px';
    return isMobile.value ? style : {};
  });

</script>

<style lang="scss" scoped>
.logo-img {
  height: 75px;
}
@media (max-width: 768px) {
  .logo-img {
    height: 58px;
    width: 200px;
  } 
}
</style>
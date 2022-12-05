<template>
  <div class="mt-4"> You can
    <span @click="reloadPage()" class="clr-1 font-bold cursor-pointer">refresh</span>
    to get new seeds
  </div>
</template>

<script setup>
  function reloadPage() {
    window.location.reload();
  }
</script>
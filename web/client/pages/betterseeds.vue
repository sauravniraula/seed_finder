<template>
  <div>
    <ErrorPage v-if="errorOccured" />
    <SeedsBody v-else-if="!fetchingData" title="Better Seeds" :seeds="data.seeds"/> 
    <Loader v-else />
  </div>
</template>

<script setup>
  import { onMounted, ref } from 'vue';
  import newAxios from '@/mixins/axios';
  import {selected_version} from "@/store";

  const fetchingData = ref(true);
  const errorOccured = ref(false);
  const data = ref();

  function get_seeds() {
    newAxios.post("get-seeds", {
      version: selected_version.value
    })
    .then(res => {
      data.value = res.data;
    })
    .catch((err) => {
      errorOccured.value = true;
    })
    .finally(() => {
      fetchingData.value = false;
    })
  }

  onMounted(() => {
    get_seeds(); 
  })

</script>

<template>
  <ErrorPage v-if="errorOccured" />
  <SeedsBody v-else-if="!fetchingData" :title="get_title_name + ' spawn'"  :seeds="data.seeds" :biomeId="params.slug" />
  <Loader v-else />
</template>

<script setup>

  import newAxios from "@/mixins/axios";
  import { minecraft_biomes, selected_version } from "@/store";

  const { params } = useRoute();
  const fetchingData = ref(true);
  const errorOccured = ref(false);
  const data = ref();

  function get_custom_seeds() {
    newAxios.post("get-custom-seeds", {
      version: selected_version.value,
      biome_id: params.slug
    })
    .then(res => {
      data.value = res.data;
    })
    .catch(() => {
      errorOccured.value = true;
    })
    .finally(() => {
      fetchingData.value = false
    })
  }

  const get_title_name = computed(() => {
    return minecraft_biomes[params.slug];
  })

  onMounted(() => {
    get_custom_seeds();
  })

</script>

import { ref, onMounted, onUnmounted, computed } from 'vue';

export default function getScreenInfo() {

  const screenWidth = ref(9999);

  const isMobile = computed(() => {
    return screenWidth.value <= 768;
  })
  onMounted(() => {
    screenWidth.value = window.innerWidth; 
    window.addEventListener('resize', () => {
      screenWidth.value = window.innerWidth;
    });
  });
  onUnmounted(() => {
    window.removeEventListener('resize');
  })

  return {screenWidth, isMobile};
}
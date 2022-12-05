<template>
  <div class="loader-main minh-full flex justify-center items-center">
    <div class="loader flex gap-1">
      <div class="dot-1"></div>
      <div class="dot-2"></div>
      <div class="dot-3"></div>
    </div>
  </div>  
</template>

<style>

.loader > div {
  width: 20px;
  height: 20px;
  border-radius: 100%;
  background-color: rgb(214, 214, 214);
}

.dot-1 {
  animation: animation1 1s infinite;
}
.dot-2 {
  animation: animation2 1s infinite;
}
.dot-3 {
  animation: animation3 1s infinite;
}

@keyframes animation1 {
  10% {
    background-color: #FF7D3E;
  } 
}
@keyframes animation2 {
  40% {
    background-color: #FF7D3E;
  } 
}
@keyframes animation3 {
  70% {
    background-color: #FF7D3E;
  } 
}

</style>
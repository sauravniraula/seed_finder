import { defineNuxtConfig } from 'nuxt'

// https://v3.nuxtjs.org/api/configuration/nuxt.config
export default defineNuxtConfig({
  ssr: false,
  app: {
    head: {
      title: "Seed Finder"
    }
  },
  css: [
    '@/assets/scss/main.scss'
  ],
  modules: [
    '@nuxtjs/tailwindcss'
  ]
})
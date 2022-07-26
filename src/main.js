import Vue from 'vue'
import App from './App.vue'

import vgl from 'vue-golden-layout'
Vue.use(vgl);

import 'golden-layout/src/css/goldenlayout-dark-theme.css'

Vue.config.productionTip = false

import { BootstrapVue, IconsPlugin } from 'bootstrap-vue'

// Import Bootstrap and BootstrapVue CSS files (order is important)
import './app.scss'

// Make BootstrapVue available throughout your project
Vue.use(BootstrapVue)
// Optionally install the BootstrapVue icon components plugin
Vue.use(IconsPlugin)

new Vue({
  render: h => h(App),
}).$mount('#app')

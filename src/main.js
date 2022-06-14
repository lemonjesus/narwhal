import Vue from 'vue'
import App from './App.vue'

import vgl from 'vue-golden-layout'
Vue.use(vgl);

import 'golden-layout/src/css/goldenlayout-dark-theme.css'

Vue.config.productionTip = false

new Vue({
  render: h => h(App),
}).$mount('#app')

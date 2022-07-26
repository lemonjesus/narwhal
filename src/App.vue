<template>
  <div>
    <div id="toolbar">
      <b-navbar toggleable="lg" type="dark" variant="info">
        <b-navbar-brand>Narwhal</b-navbar-brand>

        <b-navbar-toggle target="nav-collapse"></b-navbar-toggle>

        <b-collapse id="nav-collapse" is-nav>
          <b-navbar-nav>
            <b-nav-item-dropdown text="File">
              <b-dropdown-item v-b-modal.modal-1>New</b-dropdown-item>
              <b-dropdown-item href="#">Open</b-dropdown-item>
              <b-dropdown-item href="#">Save</b-dropdown-item>
            </b-nav-item-dropdown>
          </b-navbar-nav>
        </b-collapse>
      </b-navbar>
    </div>

    <golden-layout class="hscreen" v-if="vm.cpu">
      <gl-row>
        <gl-component title="CPU State">
          <ProcessorWindow msg="hello"></ProcessorWindow>
        </gl-component>
        <gl-stack>
          <gl-component title="Memory">
            <MemoryWindow msg="memory"></MemoryWindow>
          </gl-component>
          <gl-component title="component3">
            <h1>Component 3</h1>
          </gl-component>
        </gl-stack>
      </gl-row>
    </golden-layout>

    <div v-if="!vm.cpu" class="text-dark">
      <h1>No CPU</h1>
      Select <kbd>File > New</kbd> to get started, or <kbd>File > Open</kbd> to resume a session.
    </div>
  
    <b-modal id="modal-1" centered title="Setup New Project">
      <p class="my-1">Select a processor type to get started:</p>
      <!-- make a dropdown box of processor types -->
      <b-form-select v-model="processorType" :options="vm.getCPUTypes" placeholder="Select a processor type"></b-form-select>
      <b-form-select 
        class="mt-1"
        v-if="processorType" 
        v-model="processorSubType" 
        :options="vm.getCPUTypes.filter((x) => x.value == processorType)[0].subtypes" 
        placeholder="Select a processor subtype">
      </b-form-select>
      <template v-slot:modal-footer>
        <div class="">
          <b-button variant="primary" size="sm">Cancel</b-button>
          <b-button class="ml-2" variant="success" size="sm" @click="createProject" :disabled="!(processorType !== null && processorSubType !== null)">Create Project</b-button>
        </div>
      </template>
    </b-modal>
  </div>
</template>

<script>
import ProcessorWindow from './components/ProcessorWindow.vue'
import MemoryWindow from './components/MemoryWindow.vue'

import { useVmStore } from './stores/vm'

export default {
  name: 'App',
  components: {ProcessorWindow, MemoryWindow},
  data() {
    return {
      processorType: null,
      processorSubType: null,
    }
  },
  methods: {
    createProject: function () {
      this.vm.reset(this.processorType, this.processorSubType)
      this.$bvModal.hide('modal-1')
    },
  },
  setup() {
    const vm = useVmStore()

    return {
      vm
    };
  }
}
</script>

<style>
html, body {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: white;
  margin: 0;
  padding: 0;
}

.hscreen {
	width: 100vw;
	height: 100vh;
}

#toolbar .navbar {
  padding: 0rem 1rem;
}
</style>

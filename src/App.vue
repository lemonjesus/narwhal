<template>
  <golden-layout class="hscreen">
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
</template>

<script>
import ProcessorWindow from './components/ProcessorWindow.vue'
import MemoryWindow from './components/MemoryWindow.vue'

export default {
  name: 'App',
  components: {ProcessorWindow, MemoryWindow}
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
</style>

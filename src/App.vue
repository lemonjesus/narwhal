<template>
  <div>
    <div id="toolbar">
      <b-navbar toggleable="lg" type="dark" variant="info">
        <b-navbar-brand>Narwhal</b-navbar-brand>

        <b-navbar-toggle target="nav-collapse"></b-navbar-toggle>

        <b-collapse id="nav-collapse" is-nav>
          <b-navbar-nav>
            <b-nav-item-dropdown text="File">
              <b-dropdown-item href="#">New</b-dropdown-item>
              <b-dropdown-item href="#">Open</b-dropdown-item>
              <b-dropdown-item href="#">Save</b-dropdown-item>
            </b-nav-item-dropdown>
          </b-navbar-nav>
        </b-collapse>
      </b-navbar>
    </div>

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
  </div>

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

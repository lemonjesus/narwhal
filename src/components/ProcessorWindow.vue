<template>
    <h1>{{ msg }}</h1>
</template>

<script>
import { useVmStore } from '../stores/vm'

export default {
  name: 'ProcessorWindow',
  props: {
    msg: String
  },
  setup() {
    const vm = useVmStore()

    return {
      vm
    };
  }
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
h3 {
  margin: 40px 0 0;
}
ul {
  list-style-type: none;
  padding: 0;
}
li {
  display: inline-block;
  margin: 0 10px;
}
a {
  color: #42b983;
}
</style>

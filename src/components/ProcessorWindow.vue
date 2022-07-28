<template>
  <div class="container pt-2">
    <div v-for="group in this.vm.getRegisters" :key="group.name">
      <h6 class="reg-separator">{{ group.name }}</h6>
      <table class="table table-sm table-striped">
        <thead>
          <tr>
            <th>Name</th>
            <th>Value</th>
          </tr>
        </thead>
        <tbody class="table-hover">
          <tr v-for="reg in group.regs" :key="reg.name">
            <td>{{ reg.name }}</td>
            <td v-html="reg.formatter ? reg.formatter(vm.getCPU.reg_read_i32(reg.id)) : vm.getCPU.reg_read_i32(reg.id)"></td>
          </tr>
        </tbody>
      </table>
    </div>
  </div>
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
.table-sm {
  font-size: 0.8rem;
  font-family: monospace;
}
.table-sm * {
  border-color: #444;
  border-top: none;
}
</style>

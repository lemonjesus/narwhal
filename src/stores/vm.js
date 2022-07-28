/* eslint-disable no-undef */
import { defineStore } from "pinia";
import registers from "../data/registers"

export const useVmStore = defineStore('vm', {
  state: () => ({
    cpu: null,
    memory: {},
  }),
  getters: {
    getCPU: (state) => state.cpu,
    getArch: (state) => state.cpu.arch,
    getMode: (state) => state.cpu.mode,
    getMemory: (state) => state.memory,
    getCPUTypes: () => [
      {value: uc.ARCH_ARM, text: 'ARM', subtypes: [{value: uc.MODE_ARM, text: 'ARM'}, {value: uc.MODE_THUMB, text: 'Thumb'}]}, 
      {value: uc.ARCH_ARM64, text: 'ARM64', subtypes: [{value: uc.MODE_ARM, text: 'ARM'}, {value: uc.MODE_THUMB, text: 'Thumb'}]},
      {value: uc.ARCH_MIPS, text: 'MIPS', subtypes: [{value: uc.MODE_MIPS32, text: 'MIPS32'}, {value: uc.MODE_MIPS64, text: 'MIPS64'}]},
      {value: uc.ARCH_X86, text: 'X86', subtypes: [{value: uc.MODE_16, text: '16-bit'}, {value: uc.MODE_32, text: '32-bit'}, {value: uc.MODE_64, text: '64-bit'}]},
    ],
    getRegisters: (state) => registers[state.cpu.arch],
  },
  actions: {
    reset(arch, mode) {
      this.cpu = new uc.Unicorn(arch, mode);
      this.memory = {};
    }
  }
})
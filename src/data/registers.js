/* eslint-disable no-undef */

const hexFormatter = (value, bits) => {
  value = value.toString(16);
  // prepend with appropriate zeros
  while (value.length < bits / 4) {
    value = '0' + value;
  }
  value = value.toUpperCase();
  value = "0x" + value;
  return value;
}

const hex = (bits) => {
  return function(value) {
    return hexFormatter(value, bits);
  }
}

export default {
  // ARM registers
  [uc.ARCH_ARM]: [
    {name: "General Purpose Registers", regs: [
      {name: "R0", size: 32, id: uc.ARM_REG_R0, formatter: hex(32)},
      {name: "R1", size: 32, id: uc.ARM_REG_R1, formatter: hex(32)},
      {name: "R2", size: 32, id: uc.ARM_REG_R2, formatter: hex(32)},
      {name: "R3", size: 32, id: uc.ARM_REG_R3, formatter: hex(32)},
      {name: "R4", size: 32, id: uc.ARM_REG_R4, formatter: hex(32)},
      {name: "R5", size: 32, id: uc.ARM_REG_R5, formatter: hex(32)},
      {name: "R6", size: 32, id: uc.ARM_REG_R6, formatter: hex(32)},
      {name: "R7", size: 32, id: uc.ARM_REG_R7, formatter: hex(32)},
      {name: "R8", size: 32, id: uc.ARM_REG_R8, formatter: hex(32)},
      {name: "R9", size: 32, id: uc.ARM_REG_R9, formatter: hex(32)},
      {name: "R10", size: 32, id: uc.ARM_REG_R10, formatter: hex(32)},
      {name: "R11", size: 32, id: uc.ARM_REG_R11, formatter: hex(32)},
      {name: "R12", size: 32, id: uc.ARM_REG_R12, formatter: hex(32)},
      {name: "R13", size: 32, id: uc.ARM_REG_R13, formatter: hex(32)},
      {name: "R14", size: 32, id: uc.ARM_REG_R14, formatter: hex(32)},
      {name: "R15", size: 32, id: uc.ARM_REG_R15, formatter: hex(32)},
      {name: "SP", size: 32, id: uc.ARM_REG_SP, formatter: hex(32)},
      {name: "LR", size: 32, id: uc.ARM_REG_LR, formatter: hex(32)},
      {name: "PC", size: 32, id: uc.ARM_REG_PC, formatter: hex(32)},
      {name: "CPSR", size: 32, id: uc.ARM_REG_CPSR, formatter: (value) => {
        // parse CPSR for ARM
        let output = "";
        output += "<span class='badge " + (value & (0x1 << 31) ? "badge-success" : "badge-dark") + "'>N</span>";
        output += "<span class='badge " + (value & (0x1 << 30) ? "badge-success" : "badge-dark") + "'>Z</span>";
        output += "<span class='badge " + (value & (0x1 << 29) ? "badge-success" : "badge-dark") + "'>C</span>";
        output += "<span class='badge " + (value & (0x1 << 28) ? "badge-success" : "badge-dark") + "'>V</span>";
        output += "<small class='ml-2'>(" + (hex(32)(value)) + ")</small>";
        return output;
      }}
    ]}],
}
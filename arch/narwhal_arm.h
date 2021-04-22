#ifndef NARWHAL_ARCH_ARM
#define NARWHAL_ARCH_ARM

#include <unicorn/unicorn.h>

const uc_arm_reg arm_regs[] = { //UC_ARM_REG_APSR,
                                //UC_ARM_REG_APSR_NZCV,
                                // UC_ARM_REG_CPSR,
                                // UC_ARM_REG_FPEXC,
                                // UC_ARM_REG_FPINST,
                                // UC_ARM_REG_FPSCR,
                                // UC_ARM_REG_FPSCR_NZCV,
                                // UC_ARM_REG_FPSID,
                                // UC_ARM_REG_ITSTATE,
                                // UC_ARM_REG_LR,
                                UC_ARM_REG_PC,
                                UC_ARM_REG_SP,
                                // UC_ARM_REG_SPSR,
                                // UC_ARM_REG_D0,
                                // UC_ARM_REG_D1,
                                // UC_ARM_REG_D2,
                                // UC_ARM_REG_D3,
                                // UC_ARM_REG_D4,
                                // UC_ARM_REG_D5,
                                // UC_ARM_REG_D6,
                                // UC_ARM_REG_D7,
                                // UC_ARM_REG_D8,
                                // UC_ARM_REG_D9,
                                // UC_ARM_REG_D10,
                                // UC_ARM_REG_D11,
                                // UC_ARM_REG_D12,
                                // UC_ARM_REG_D13,
                                // UC_ARM_REG_D14,
                                // UC_ARM_REG_D15,
                                // UC_ARM_REG_D16,
                                // UC_ARM_REG_D17,
                                // UC_ARM_REG_D18,
                                // UC_ARM_REG_D19,
                                // UC_ARM_REG_D20,
                                // UC_ARM_REG_D21,
                                // UC_ARM_REG_D22,
                                // UC_ARM_REG_D23,
                                // UC_ARM_REG_D24,
                                // UC_ARM_REG_D25,
                                // UC_ARM_REG_D26,
                                // UC_ARM_REG_D27,
                                // UC_ARM_REG_D28,
                                // UC_ARM_REG_D29,
                                // UC_ARM_REG_D30,
                                // UC_ARM_REG_D31,
                                // UC_ARM_REG_FPINST2,
                                // UC_ARM_REG_MVFR0,
                                // UC_ARM_REG_MVFR1,
                                // UC_ARM_REG_MVFR2,
                                // UC_ARM_REG_Q0,
                                // UC_ARM_REG_Q1,
                                // UC_ARM_REG_Q2,
                                // UC_ARM_REG_Q3,
                                // UC_ARM_REG_Q4,
                                // UC_ARM_REG_Q5,
                                // UC_ARM_REG_Q6,
                                // UC_ARM_REG_Q7,
                                // UC_ARM_REG_Q8,
                                // UC_ARM_REG_Q9,
                                // UC_ARM_REG_Q10,
                                // UC_ARM_REG_Q11,
                                // UC_ARM_REG_Q12,
                                // UC_ARM_REG_Q13,
                                // UC_ARM_REG_Q14,
                                // UC_ARM_REG_Q15,
                                UC_ARM_REG_R0,
                                UC_ARM_REG_R1,
                                UC_ARM_REG_R2,
                                UC_ARM_REG_R3,
                                UC_ARM_REG_R4,
                                UC_ARM_REG_R5,
                                UC_ARM_REG_R6,
                                UC_ARM_REG_R7,
                                UC_ARM_REG_R8,
                                UC_ARM_REG_R9,
                                UC_ARM_REG_R10,
                                UC_ARM_REG_R11,
                                UC_ARM_REG_R12,
                                // UC_ARM_REG_S0,
                                // UC_ARM_REG_S1,
                                // UC_ARM_REG_S2,
                                // UC_ARM_REG_S3,
                                // UC_ARM_REG_S4,
                                // UC_ARM_REG_S5,
                                // UC_ARM_REG_S6,
                                // UC_ARM_REG_S7,
                                // UC_ARM_REG_S8,
                                // UC_ARM_REG_S9,
                                // UC_ARM_REG_S10,
                                // UC_ARM_REG_S11,
                                // UC_ARM_REG_S12,
                                // UC_ARM_REG_S13,
                                // UC_ARM_REG_S14,
                                // UC_ARM_REG_S15,
                                // UC_ARM_REG_S16,
                                // UC_ARM_REG_S17,
                                // UC_ARM_REG_S18,
                                // UC_ARM_REG_S19,
                                // UC_ARM_REG_S20,
                                // UC_ARM_REG_S21,
                                // UC_ARM_REG_S22,
                                // UC_ARM_REG_S23,
                                // UC_ARM_REG_S24,
                                // UC_ARM_REG_S25,
                                // UC_ARM_REG_S26,
                                // UC_ARM_REG_S27,
                                // UC_ARM_REG_S28,
                                // UC_ARM_REG_S29,
                                // UC_ARM_REG_S30,
                                // UC_ARM_REG_S31,

                                // UC_ARM_REG_C1_C0_2,
                                // UC_ARM_REG_C13_C0_2,
                                // UC_ARM_REG_C13_C0_3,

                                UC_ARM_REG_IPSR,
                                UC_ARM_REG_MSP,
                                UC_ARM_REG_PSP,
                                // UC_ARM_REG_CONTROL,
                                // UC_ARM_REG_ENDING,
};

const char* const arm_reg_names[] = { //"APSR",
                                // "APSR_NZCV",
                                // "CPSR",
                                // "FPEXC",
                                // "FPINST",
                                // "FPSCR",
                                // "FPSCR_NZCV",
                                // "FPSID",
                                // "ITSTATE",
                                // "LR",
                                "PC",
                                "SP",
                                // "SPSR",
                                // "D0",
                                // "D1",
                                // "D2",
                                // "D3",
                                // "D4",
                                // "D5",
                                // "D6",
                                // "D7",
                                // "D8",
                                // "D9",
                                // "D10",
                                // "D11",
                                // "D12",
                                // "D13",
                                // "D14",
                                // "D15",
                                // "D16",
                                // "D17",
                                // "D18",
                                // "D19",
                                // "D20",
                                // "D21",
                                // "D22",
                                // "D23",
                                // "D24",
                                // "D25",
                                // "D26",
                                // "D27",
                                // "D28",
                                // "D29",
                                // "D30",
                                // "D31",
                                // "FPINST2",
                                // "MVFR0",
                                // "MVFR1",
                                // "MVFR2",
                                // "Q0",
                                // "Q1",
                                // "Q2",
                                // "Q3",
                                // "Q4",
                                // "Q5",
                                // "Q6",
                                // "Q7",
                                // "Q8",
                                // "Q9",
                                // "Q10",
                                // "Q11",
                                // "Q12",
                                // "Q13",
                                // "Q14",
                                // "Q15",
                                "R0",
                                "R1",
                                "R2",
                                "R3",
                                "R4",
                                "R5",
                                "R6",
                                "R7",
                                "R8",
                                "R9",
                                "R10",
                                "R11",
                                "R12",
                                // "S0",
                                // "S1",
                                // "S2",
                                // "S3",
                                // "S4",
                                // "S5",
                                // "S6",
                                // "S7",
                                // "S8",
                                // "S9",
                                // "S10",
                                // "S11",
                                // "S12",
                                // "S13",
                                // "S14",
                                // "S15",
                                // "S16",
                                // "S17",
                                // "S18",
                                // "S19",
                                // "S20",
                                // "S21",
                                // "S22",
                                // "S23",
                                // "S24",
                                // "S25",
                                // "S26",
                                // "S27",
                                // "S28",
                                // "S29",
                                // "S30",
                                // "S31",

                                // "C1_C0_2",
                                // "C13_C0_2",
                                // "C13_C0_3",

                                "IPSR",
                                "MSP",
                                "PSP",
                                // "CONTROL",
                                // "ENDING",
};

void show_arm_cpu_window();
#endif
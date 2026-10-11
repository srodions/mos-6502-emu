/*
 * MOS Technology 6502 processor emulator
 */
#include "typedefs.h"
#include "cpu.h"

int main()
{
	mem_t mem;
	cpu_t cpu;

	CPU_Reset(&cpu);
	MEM_Init(&mem);

    // START OF INS SET
    u32 cycles = 9;
    mem.data[0xFFFC] = INS_JSR;
    mem.data[0xFFFD] = 0x42;
    mem.data[0xFFFE] = 0x42;
    mem.data[0x4242] = INS_LDA_IM;
    mem.data[0x4243] = 0x84;
	CPU_Exec(&cycles, &cpu, &mem);
    // END OF INS SET

	return 0;
}

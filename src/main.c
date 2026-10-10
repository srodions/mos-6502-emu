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
    u32 cycles = 2;
    mem.data[0xFFFC] = INS_LDA_ZP;
    mem.data[0xFFFD] = 0x42;
    mem.data[0x0042] = 0x84;
	CPU_Exec(&cycles, &cpu, &mem);
    // END OF INS SET

	return 0;
}

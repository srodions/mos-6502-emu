#include <stdio.h>
#include "typedefs.h"
#include "cpu.h"

void CPU_Reset(cpu_t* cpu)
{
	cpu->pc = VEC_RESET;
	cpu->sp = VEC_ZEROPG;	// Sets the stack pointer to the beginning of the stack

	SET_FLAG(cpu, FLAG_C, 0);	// Sets all the status flags to zero (flags must be 0x00)
	SET_FLAG(cpu, FLAG_Z, 0);	// 00000010(2) -> 00000000(2)
	SET_FLAG(cpu, FLAG_I, 0);	// ...
	SET_FLAG(cpu, FLAG_D, 0);
	SET_FLAG(cpu, FLAG_B, 0);
	SET_FLAG(cpu, FLAG_V, 0);
	SET_FLAG(cpu, FLAG_N, 0);

	cpu->a = cpu->x = cpu->y = 0;	// Sets all the registers to zero
}

byte CPU_FetchByte(u32* cycles, cpu_t* cpu, mem_t* mem)
{
	byte data = mem->data[cpu->pc];
	++(cpu->pc);
	--(*cycles);

	return data;
}

/** read 1 byte */
byte CPU_ReadByte(u32* cycles, byte addr, mem_t* mem)
{
    byte data = mem->data[addr];
    --(*cycles);

    return data;
}

word CPU_FetchWord(u32* cycles, cpu_t* cpu, mem_t* mem)
{
    // 6502 is a little-endian
    word data = mem->data[cpu->pc];
    ++(cpu->pc);

    data |= (mem->data[cpu->pc] << 8);
    ++(cpu->pc);

    *cycles -= 2;

    /*
     * If you wanted to handle endianness
     * you would have to swap bytes here
     * if (PLATFORM_BIG_ENDIAN)
     * SwapBytesInWorld(data)
     */

    return data;
}

void CPU_LDASetStatus(cpu_t* cpu)
{
    SET_FLAG(cpu, FLAG_Z, cpu->a == 0);
    // if the biggest (7th) bit of the accumulator is set then the number is negative
    SET_FLAG(cpu, FLAG_N, (cpu->a & 0b10000000) > 0);
}

void CPU_Exec(u32* cycles, cpu_t* cpu, mem_t* mem)
{
	while (*cycles > 0)
	{
		byte ins = CPU_FetchByte(cycles, cpu, mem);
        byte zeroPgAddr;

		switch (ins) 
		{
			case INS_LDA_IM:
				byte value = CPU_FetchByte(cycles, cpu, mem);
				cpu->a = value;
                CPU_LDASetStatus(cpu);
				break;
            case INS_LDA_ZP:
                zeroPgAddr = CPU_FetchByte(cycles, cpu, mem);
                cpu->a = CPU_ReadByte(cycles, zeroPgAddr, mem);
                CPU_LDASetStatus(cpu);
                break;
            case INS_LDA_ZPX:
                zeroPgAddr = CPU_FetchByte(cycles, cpu, mem);
                zeroPgAddr += cpu->x;
                --(*cycles);
                cpu->a = CPU_ReadByte(cycles, zeroPgAddr, mem);
                CPU_LDASetStatus(cpu);
                break;
            case INS_JSR:
                word subAddr = CPU_FetchWord(cycles, cpu, mem); // subAddr = Subroutine address
                MEM_WriteWord(mem, cpu->pc - 1, cpu->sp + 1, cycles);
                cpu->pc = subAddr;
                --(*cycles);
                break;
            default:
                printf("Instruction not handled %d\n", ins);
                break;
		}
	}
}

void MEM_Init(mem_t* mem)
{
	for (u32 i = 0; i < MAX_MEM; ++i)
	{
		mem->data[i] = 0x00;
	}
}

/** write 2 bytes */
void MEM_WriteWord(mem_t* mem, word value, u32 addr, u32* cycles)
{
    mem->data[addr]      = value & 0xFF;
    mem->data[addr + 1]  = (value >> 8);
    *cycles -= 2;
}



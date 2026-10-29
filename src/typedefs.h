#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

#include <stdint.h>

// CPU status flags (7 bits of flags)
#define FLAG_C (1 << 0)     // CARRY
#define FLAG_Z (1 << 1)     // ZERO
#define FLAG_I (1 << 2)     // INTERRUPT DISABLE
#define FLAG_D (1 << 3)     // DECIMAL MODE
#define FLAG_B (1 << 4)     // BREAK COMMAND
#define FLAG_V (1 << 5)     // OVERFLOW
#define FLAG_N (1 << 6)     // NEGATIVE

#define MAX_MEM (1024 * 64)	// 64 kilobytes

typedef uint8_t     byte;	// 8 bits
typedef uint16_t    word;	// 16 bits
typedef uint32_t    u32;	// 32 bits
typedef int32_t     s32;    // 32 bits

// CPU vectors; 2 bytes (16 bits) address size
static constexpr word VEC_RESET     = 0xFFFC;
static constexpr word VEC_ZEROPG    = 0x0100;

// CPU opcodes
static constexpr byte INS_LDA_IM    = 0xA9;
static constexpr byte INS_LDA_ZP    = 0xA5;
static constexpr byte INS_LDA_ZPX   = 0xB5;
static constexpr byte INS_JSR       = 0x20;

typedef struct MEM
{
	byte data[MAX_MEM];
} mem_t;

typedef struct CPU
{
	word pc;			// Program counter
	word sp;			// Stack pointer
	byte a;				// Register A (Accumulator)
	byte x;				// Register X (X-index)
	byte y;				// Register Y (Y-index)
	byte cpu_status;	// Status flags register
} cpu_t;

#endif /* TYPEDEFS_H_ */

#ifndef CPU_H_
#define CPU_H_

#include "typedefs.h"

#define SET_FLAG(cpu, flag, cond) \
((cpu)->cpu_status = ((cpu)->cpu_status & ~flag) | ((cond) ? flag : 0))

void CPU_Reset(cpu_t*);
byte CPU_FetchByte(u32*, cpu_t*, mem_t*);
byte CPU_ReadByte(u32*, byte, mem_t*);
word CPU_FetchWord(u32*, cpu_t*, mem_t*);
void CPU_Exec(u32*, cpu_t*, mem_t*);
void CPU_LDASetStatus(cpu_t*);
void MEM_Init(mem_t*);
void MEM_WriteWord(mem_t*, word, u32, u32*);

#endif /* CPU_H_ */

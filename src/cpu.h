#ifndef CPU_H_
#define CPU_H_

typedef struct CPU cpu_t;
typedef struct MEM mem_t;

#define SET_FLAG(cpu, flag, cond) \
((cpu)->cpu_status = ((cpu)->cpu_status & ~flag) | ((cond) ? flag : 0))

void CPU_Reset(cpu_t*);
unsigned char CPU_FetchByte(unsigned int*, cpu_t* cpu, mem_t* mem);
unsigned char CPU_ReadByte(unsigned int* cycles, unsigned char addr, mem_t* mem);
void CPU_Exec(unsigned int*, cpu_t*, mem_t*);
void MEM_Init(mem_t*);

#endif /* CPU_H_ */

# MOS Technology 6502 Emulator  
The MOS Technology 6502 is a legendary 8-bit microprocessor designed in 1975. It powered iconic systems like the Apple II, Commodore 64, Atari 2600, and the Nintendo Entertainment System (NES/Dendy).  

## 1. CPU Architecture & Registers  

The 6502 has an extremely minimal register set consisting of only 6 registers, most of which are 8-bit.  

• A (Accumulator) — 8-bit. The primary operational register. All arithmetic (addition, subtraction) and logical operations must pass through it.  
• X (Index Register X) — 8-bit. Used for counters, loops, and specialized memory addressing modes (indexing).  
• Y (Index Register Y) — 8-bit. Similar to the X register, frequently used for memory indexing and indirect addressing modes.  
• PC (Program Counter) — 16-bit. Holds the memory address of the current instruction being executed. It allows the CPU to address up to 64 KB of RAM.  
• SP (Stack Pointer) — 8-bit. Holds the offset for the system stack. The stack is hardcoded to page 1 of memory (addresses $0100 to $01FF).  
• P (Processor Status) — 8-bit. Holds system flags that reflect the outcome of the most recent execution.  

## 2. Processor Status Flags (P Register)  

Only 7 of the 8 bits are actively used to represent system states:  

• N (Negative) — Set if the most significant bit (Bit 7) of the result is 1 (indicating a negative number).  
• V (Overflow) — Set if an arithmetic operation results in a signed overflow.  
• B (Break Command) — Indicates that an interrupt was triggered by a software BRK instruction.  
• D (Decimal Mode) — Switches the CPU into Binary Coded Decimal (BCD) math mode when set (hardwired to off in the NES CPU).  
• I (Interrupt Disable) — Disables maskable hardware interrupts (IRQ) when set.  
• Z (Zero) — Set if the result of the last operation equals 0.  
• C (Carry) — Used as a carry bit for additions, a borrow bit for subtractions, and a buffer for bit-shift operations.  

## 3. Instructions & Opcodes  

The 6502 assembly language consists of 56 official instructions, each represented by a 3-letter mnemonic.  
Because the processor features 13 unique addressing modes, a single instruction (like LDA — Load Accumulator) compiles into completely different opcodes (machine code bytes) with variable execution cycle times depending on how it accesses memory. There are 151 official opcodes out of 256 possible byte combinations (the remaining 105 are "unofficial/illegal" opcodes).  

Core Instruction Groups:  

## Load and Store Operations:  
	• LDA, LDX, LDY — Load a value from memory into the A, X, or Y register.  
	• STA, STX, STY — Store the value of the A, X, or Y register into memory.  
## Register Transfers:  
	• TAX, TAY, TXA, TYA — Transfer data between the Accumulator and X or Y.  
	• TSX, TXS — Transfer data between Index X and the Stack Pointer.  
## Arithmetic & Logical:  
	• ADC — Add to accumulator with carry.  
	• SBC — Subtract from accumulator with carry (borrow).  
	• AND, ORA (OR), EOR (Exclusive OR) — Bitwise logical operations.  
## Increment & Decrement:  
	• INC, DEC — Increment or decrement a value directly in memory.  
	• INX, DEX, INY, DEY — Increment or decrement the X or Y registers.  
## Shifts & Bit Manipulations:  
	• ASL, LSR, ROL, ROR — Arithmetic and rotational bit shifts left or right.  
	• BIT — Test specific bits in memory against the accumulator.  
## Jumps & Branches:  
	• JMP — Unconditional jump to an absolute memory address.  
	• JSR — Jump to subroutine (pushes the return address onto the stack).  
	• RTS — Return from subroutine.  
	• BCC, BCS, BEQ, BNE, BMI, BPL, BVC, BVS — Conditional branches based on status flags (e.g., BEQ branches if the Zero flag Z is set).  
## Flag Controls:  
	• CLC, SEC — Clear or set the Carry flag C.  
	• CLD, SED — Clear or set the Decimal flag D.  
	• CLI, SEI — Clear or set the Interrupt flag I.  
	• CLV — Clear the Overflow flag V.  
## Stack & System Operations:  
	• PHA, PLA — Push or pull (pop) the Accumulator to/from the stack.  
	• PHP, PLP — Push or pull the Processor Status register to/from the stack.  
	• BRK — Force a software interrupt.  
	• NOP — No operation (wastes 2 clock cycles).  

#pragma once
#include "headers.h"

// forward declaration of the class
class Bus; 

class Cpu
{
    public:
        Cpu();
        ~Cpu();
        void ConnectBus(Bus *b) { bus = b;}
        
        // registers
        u16 ip = 0x0000; 
        u8 status = 0x00;
        u8 acc = 0x00;
        u8 sp = 0x00;
        u8 x = 0x00;
        u8 y = 0x00;
        
        // cpu flags
        enum cpu_flags { 
            C = (1<<0), //Carry
            Z = (1<<1), //Zero
            I = (1<<2), //Interrupt disable
            D = (1<<3), //Decimal mode
            B = (1<<4), //Break instr
            U = (1<<5), //Unused
            V = (1<<6), //Overflow
            N = (1<<7), //Negative
        };

        // external signals to cpu
        void Clock(); void Reset(); void IRQ(); void NMI();
        bool Complete();

    private:
        Bus *bus = nullptr;
        u8 fetched = 0x00; u16 tmp = 0x0000;
        u16 addr_abs = 0x0000; u16 addr_rel = 0x00;
        u8 opcode = 0x00; u8 cycles = 0;
        u_int32_t clock_count = 0;

        void Write(u16 addr, u8 data);
        u8 Read(u16 addr);
        u8 GetFlag(cpu_flags f);
        void SetFlag(cpu_flags f, bool b);
        u8 Fetch(); 
        
        // addressing modes to return increment of IP and adjust clock cycles
        u8 IMP(); u8 IMM(); u8 ZP0(); u8 ZPX();	u8 ZPY(); u8 REL(); 
        u8 ABS(); u8 ABX();	u8 ABY(); u8 IND();	u8 IZX(); u8 IZY();

        // opcodes for different possible operations 2^8 possibilies
        u8 ADC();	u8 AND();	u8 ASL();	u8 BCC();
        u8 BCS();	u8 BEQ();	u8 BIT();	u8 BMI();
        u8 BNE();	u8 BPL();	u8 BRK();	u8 BVC();
        u8 BVS();	u8 CLC();	u8 CLD();	u8 CLI();
        u8 CLV();	u8 CMP();	u8 CPX();	u8 CPY();
        u8 DEC();	u8 DEX();	u8 DEY();	u8 EOR();
        u8 INC();	u8 INX();	u8 INY();	u8 JMP();
        u8 JSR();	u8 LDA();	u8 LDX();	u8 LDY();
        u8 LSR();	u8 NOP();	u8 ORA();	u8 PHA();
        u8 PHP();	u8 PLA();	u8 PLP();	u8 ROL();
        u8 ROR();	u8 RTI();	u8 RTS();	u8 SBC();
        u8 SEC();	u8 SED();	u8 SEI();	u8 STA();
        u8 STX();	u8 STY();	u8 TAX();	u8 TAY();
        u8 TSX();	u8 TXA();	u8 TXS();	u8 TYA(); u8 XXX();

        struct INSTRUCTION
	    {
            std::string name;		
            u8 (Cpu::*operate )(void) = nullptr;
            u8 (Cpu::*addrmode)(void) = nullptr;
            u8 cycles = 0;
	    };

	std::vector<INSTRUCTION> lookup; 
};
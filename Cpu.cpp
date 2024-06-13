#include "Cpu.h"
#include "Bus.h"

////////////////////
// cpu functions //
///////////////////
Cpu::Cpu()
{
    using a = Cpu;
    lookup = 
	{
		{ "BRK", &a::BRK, &a::IMM, 7 },{ "ORA", &a::ORA, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::ZP0, 3 },{ "ASL", &a::ASL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHP", &a::PHP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::IMM, 2 },{ "ASL", &a::ASL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABS, 4 },{ "ASL", &a::ASL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BPL", &a::BPL, &a::REL, 2 },{ "ORA", &a::ORA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ZPX, 4 },{ "ASL", &a::ASL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLC", &a::CLC, &a::IMP, 2 },{ "ORA", &a::ORA, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABX, 4 },{ "ASL", &a::ASL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "JSR", &a::JSR, &a::ABS, 6 },{ "AND", &a::AND, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "BIT", &a::BIT, &a::ZP0, 3 },{ "AND", &a::AND, &a::ZP0, 3 },{ "ROL", &a::ROL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLP", &a::PLP, &a::IMP, 4 },{ "AND", &a::AND, &a::IMM, 2 },{ "ROL", &a::ROL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "BIT", &a::BIT, &a::ABS, 4 },{ "AND", &a::AND, &a::ABS, 4 },{ "ROL", &a::ROL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BMI", &a::BMI, &a::REL, 2 },{ "AND", &a::AND, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ZPX, 4 },{ "ROL", &a::ROL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEC", &a::SEC, &a::IMP, 2 },{ "AND", &a::AND, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ABX, 4 },{ "ROL", &a::ROL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "RTI", &a::RTI, &a::IMP, 6 },{ "EOR", &a::EOR, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "EOR", &a::EOR, &a::ZP0, 3 },{ "LSR", &a::LSR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHA", &a::PHA, &a::IMP, 3 },{ "EOR", &a::EOR, &a::IMM, 2 },{ "LSR", &a::LSR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::ABS, 3 },{ "EOR", &a::EOR, &a::ABS, 4 },{ "LSR", &a::LSR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BVC", &a::BVC, &a::REL, 2 },{ "EOR", &a::EOR, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ZPX, 4 },{ "LSR", &a::LSR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLI", &a::CLI, &a::IMP, 2 },{ "EOR", &a::EOR, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ABX, 4 },{ "LSR", &a::LSR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "RTS", &a::RTS, &a::IMP, 6 },{ "ADC", &a::ADC, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ADC", &a::ADC, &a::ZP0, 3 },{ "ROR", &a::ROR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLA", &a::PLA, &a::IMP, 4 },{ "ADC", &a::ADC, &a::IMM, 2 },{ "ROR", &a::ROR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::IND, 5 },{ "ADC", &a::ADC, &a::ABS, 4 },{ "ROR", &a::ROR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BVS", &a::BVS, &a::REL, 2 },{ "ADC", &a::ADC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ZPX, 4 },{ "ROR", &a::ROR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEI", &a::SEI, &a::IMP, 2 },{ "ADC", &a::ADC, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ABX, 4 },{ "ROR", &a::ROR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "???", &a::NOP, &a::IMP, 2 },{ "STA", &a::STA, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZP0, 3 },{ "STA", &a::STA, &a::ZP0, 3 },{ "STX", &a::STX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "DEY", &a::DEY, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 2 },{ "TXA", &a::TXA, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "STY", &a::STY, &a::ABS, 4 },{ "STA", &a::STA, &a::ABS, 4 },{ "STX", &a::STX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "BCC", &a::BCC, &a::REL, 2 },{ "STA", &a::STA, &a::IZY, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZPX, 4 },{ "STA", &a::STA, &a::ZPX, 4 },{ "STX", &a::STX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "TYA", &a::TYA, &a::IMP, 2 },{ "STA", &a::STA, &a::ABY, 5 },{ "TXS", &a::TXS, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::NOP, &a::IMP, 5 },{ "STA", &a::STA, &a::ABX, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::XXX, &a::IMP, 5 },
		{ "LDY", &a::LDY, &a::IMM, 2 },{ "LDA", &a::LDA, &a::IZX, 6 },{ "LDX", &a::LDX, &a::IMM, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "LDY", &a::LDY, &a::ZP0, 3 },{ "LDA", &a::LDA, &a::ZP0, 3 },{ "LDX", &a::LDX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "TAY", &a::TAY, &a::IMP, 2 },{ "LDA", &a::LDA, &a::IMM, 2 },{ "TAX", &a::TAX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "LDY", &a::LDY, &a::ABS, 4 },{ "LDA", &a::LDA, &a::ABS, 4 },{ "LDX", &a::LDX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "BCS", &a::BCS, &a::REL, 2 },{ "LDA", &a::LDA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "LDY", &a::LDY, &a::ZPX, 4 },{ "LDA", &a::LDA, &a::ZPX, 4 },{ "LDX", &a::LDX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "CLV", &a::CLV, &a::IMP, 2 },{ "LDA", &a::LDA, &a::ABY, 4 },{ "TSX", &a::TSX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 4 },{ "LDY", &a::LDY, &a::ABX, 4 },{ "LDA", &a::LDA, &a::ABX, 4 },{ "LDX", &a::LDX, &a::ABY, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "CPY", &a::CPY, &a::IMM, 2 },{ "CMP", &a::CMP, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPY", &a::CPY, &a::ZP0, 3 },{ "CMP", &a::CMP, &a::ZP0, 3 },{ "DEC", &a::DEC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INY", &a::INY, &a::IMP, 2 },{ "CMP", &a::CMP, &a::IMM, 2 },{ "DEX", &a::DEX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "CPY", &a::CPY, &a::ABS, 4 },{ "CMP", &a::CMP, &a::ABS, 4 },{ "DEC", &a::DEC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BNE", &a::BNE, &a::REL, 2 },{ "CMP", &a::CMP, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ZPX, 4 },{ "DEC", &a::DEC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLD", &a::CLD, &a::IMP, 2 },{ "CMP", &a::CMP, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ABX, 4 },{ "DEC", &a::DEC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "CPX", &a::CPX, &a::IMM, 2 },{ "SBC", &a::SBC, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPX", &a::CPX, &a::ZP0, 3 },{ "SBC", &a::SBC, &a::ZP0, 3 },{ "INC", &a::INC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INX", &a::INX, &a::IMP, 2 },{ "SBC", &a::SBC, &a::IMM, 2 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::SBC, &a::IMP, 2 },{ "CPX", &a::CPX, &a::ABS, 4 },{ "SBC", &a::SBC, &a::ABS, 4 },{ "INC", &a::INC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BEQ", &a::BEQ, &a::REL, 2 },{ "SBC", &a::SBC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ZPX, 4 },{ "INC", &a::INC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SED", &a::SED, &a::IMP, 2 },{ "SBC", &a::SBC, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ABX, 4 },{ "INC", &a::INC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
	};
}

Cpu::~Cpu()
{
}

u8 Cpu::Read(u16 addr)
{
    return bus->Read(addr,false);
}

void Cpu::Write(u16 addr, u8 datacc)
{
    bus->Write(addr,datacc);
}

// Interrupt requests are a complex operation and only happen if the
// "disable interrupt" flag is 0. IRQs can happen at any time, but
// you dont want them to be destructive to the operation of the running 
// program. Therefore the current instruction is allowed to finish
// (which I facilitate by doing the whole thing when cycles == 0) and 
// then the current program counter is stored on the stack. Then the
// current status register is stored on the stack. When the routine
// that services the interrupt has finished, the status register
// and program counter can be restored to how they where before it 
// occurred. This is impemented by the "RTI" instruction. Once the IRQ
// has happened, in a similar way to a reset, a programmable address
// is read form hard coded location 0xFFFE, which is subsequently
// set to the program counter.
void Cpu::IRQ()
{
	// If interrupts are allowed
	if (GetFlag(I) == 0)
	{
		// Push the program counter to the stack. It's 16-bits dont
		// forget so that takes two pushes
		Write(0x0100 + sp, (ip >> 8) & 0x00FF);
		sp--;
		Write(0x0100 + sp, ip & 0x00FF);
		sp--;

		// Then Push the status register to the stack
		SetFlag(B, 0);
		SetFlag(U, 1);
		SetFlag(I, 1);
		Write(0x0100 + sp, status);
		sp--;

		// Read new program counter location from fixed address
		addr_abs = 0xFFFE;
		uint16_t lo = Read(addr_abs + 0);
		uint16_t hi = Read(addr_abs + 1);
		ip = (hi << 8) | lo;

		// IRQs take time
		cycles = 7;
	}
}


// A Non-Maskable Interrupt cannot be ignored. It behaves in exactly the
// same way as a regular IRQ, but reads the new program counter address
// form location 0xFFFA.
void Cpu::NMI()
{
	Write(0x0100 + sp, (ip >> 8) & 0x00FF);
	sp--;
	Write(0x0100 + sp, ip & 0x00FF);
	sp--;

	SetFlag(B, 0);
	SetFlag(U, 1);
	SetFlag(I, 1);
	Write(0x0100 + sp, status);
	sp--;

	addr_abs = 0xFFFA;
	uint16_t lo = Read(addr_abs + 0);
	uint16_t hi = Read(addr_abs + 1);
	ip = (hi << 8) | lo;

	cycles = 8;
}

void Cpu::Reset()
{
    // set address to known location
    addr_abs = 0xFFFC;
    u16 lo = Read(addr_abs+0);
    u16 hi = Read(addr_abs+1);
    // set ip to location
    ip = (hi << 8) | lo;

    // reset other registers
    acc = x = y = sp = 0; status = 0x00 | U;

    // clear remaining vars
    addr_rel = addr_abs = 0x0000; fetched = 0x00;

    // 8 cycles for rst
    cycles = 8;
}

void Cpu::Clock()
{
    if (cycles==0)
    {
        opcode = Read(ip);
        ip++;
        cycles = lookup[opcode].cycles;
        SetFlag(U, true); // always?
        
        // get additional cycles according to addressing mode and operation
        u8 addr_mode_cycle = (this->*lookup[opcode].addrmode)();
        u8 operation_cycle = (this->*lookup[opcode].operate)();
        cycles += (addr_mode_cycle & operation_cycle); // returns 1 if they need additional clock cycle which is why we & them

        SetFlag(U, true); // always?
    }

    clock_count++; // time goes up
    cycles--; // cycles remaining goes down, until 0 which fetches the next instruction
}

// get the value of a specific bit of the status register
u8 Cpu::GetFlag(cpu_flags f)
{
	return ((status & f) > 0) ? 1 : 0;
}

// set or clear a specific bit of the status register
void Cpu::SetFlag(cpu_flags f, bool b)
{
	if (b)
		status |= f;
	else
		status &= ~f;
}

/////////////////////// 
// addressing modes //
//////////////////////

// The 6502 can address between 0x0000 - 0xFFFF. The high byte is often referred
// to as the "page", and the low byte is the offset into that page. This implies
// there are 256 pages, each containing 256 bytes.
//
// Several addressing modes have the potential to require an additional clock
// cycle if they cross a page boundary. This is combined with several instructions
// that enable this additional clock cycle. So each addressing function returns
// a flag saying it has potential, as does each instruction. If both instruction
// and address function return 1, then an additional clock cycle is required.

// Address Mode: Implied
// There is no additional data required for this instruction. The instruction
// does something very simple like sets a status bit. However, we will
// target the accumulator, for instructions like PHA
u8 Cpu::IMP()
{
	fetched = acc;
	return 0;
}

// Address Mode: Immediate
// The instruction expects the next byte to be used as a value, so we'll prep
// the Read address to point to the next byte
u8 Cpu::IMM()
{
	addr_abs = ip++;	
	return 0;
}

// Address Mode: Zero Page
// To save program bytes, zero page addressing allows you to absolutely address
// a location in first 0xFF bytes of address range. Clearly this only requires
// one byte instead of the usual two.
u8 Cpu::ZP0()
{
	addr_abs = Read(ip);	
	ip++;
	addr_abs &= 0x00FF;
	return 0;
}

// Address Mode: Zero Page with X register Offset
// Fundamentally the same as Zero Page addressing, but the contents of the X Register
// is added to the supplied single byte address. This is useful for iterating through
// ranges within the first page.
u8 Cpu::ZPX()
{
	addr_abs = (Read(ip) + x);
	ip++;
	addr_abs &= 0x00FF;
	return 0;
}

// Address Mode: Zero Page with Y Offset
// Same as above but uses Y Register for offset
u8 Cpu::ZPY()
{
	addr_abs = (Read(ip) + y);
	ip++;
	addr_abs &= 0x00FF;
	return 0;
}

// Address Mode: Relative
// This address mode is exclusive to branch instructions. The address
// must reside within -128 to +127 of the branch instruction, i.e.
// you can't directly branch to any address in the addressable range.
u8 Cpu::REL()
{
	addr_rel = Read(ip);
	ip++;
	if (addr_rel & 0x80) // negative jmp
		addr_rel |= 0xFF00;
	return 0;
}

// Address Mode: Absolute 
// A full 16-bit address is loaded and used
u8 Cpu::ABS()
{
	u16 lo = Read(ip);
	ip++;
	u16 hi = Read(ip);
	ip++;

	addr_abs = (hi << 8) | lo;

	return 0;
}

// Address Mode: Absolute with X Offset
// Fundamentally the same as absolute addressing, but the contents of the X Register
// is added to the supplied two byte address. If the resulting address changes
// the page, an additional clock cycle is required
u8 Cpu::ABX()
{
	u16 lo = Read(ip);
	ip++;
	u16 hi = Read(ip);
	ip++;

	addr_abs = (hi << 8) | lo;
	addr_abs += x;

	if ((addr_abs & 0xFF00) != (hi << 8))
		return 1;
	else
		return 0;	
}

// Address Mode: Absolute with Y Offset
// Fundamentally the same as absolute addressing, but the contents of the Y Register
// is added to the supplied two byte address. If the resulting address changes
// the page, an additional clock cycle is required
u8 Cpu::ABY()
{
	u16 lo = Read(ip);
	ip++;
	u16 hi = Read(ip);
	ip++;

	addr_abs = (hi << 8) | lo;
	addr_abs += y;

	if ((addr_abs & 0xFF00) != (hi << 8))
		return 1;
	else
		return 0;
}

// Note: The next 3 address modes use indirection (aka Pointers!)

// Address Mode: Indirect
// The supplied 16-bit address is Read to get the actual 16-bit address. This is
// instruction is unusual in that it has a bug in the hardware! To emulate its
// function accurately, we also need to emulate this bug. If the low byte of the
// supplied address is 0xFF, then to Read the high byte of the actual address
// we need to cross a page boundary. This doesnt actually work on the chip as 
// designed, instead it wraps back around in the same page, yielding an 
// invalid actual address
///////// ptr = 0x10FF (low addr)
///////// ptr+1 = 0x1AFF (high addr)
///////// addr = Read(0x1000)<<8 | Read(0x10FF)
///////// ptr = 0x10AB
///////// ptr+1 = 0x10AC
///////// addr = Read(0x10AC)<<8 | Read(0x10AB)
u8 Cpu::IND()
{
	u16 ptr_lo = Read(ip);
	ip++;
	u16 ptr_hi = Read(ip);
	ip++;

	u16 ptr = (ptr_hi << 8) | ptr_lo;

	if (ptr_lo == 0x00FF) // Simulate page boundary hardware bug
	{
		addr_abs = (Read(ptr & 0xFF00) << 8) | Read(ptr + 0);
	}
	else // Behave normally
	{
		addr_abs = (Read(ptr + 1) << 8) | Read(ptr + 0);
	}
	
	return 0;
}


// Address Mode: Indirect X
// The supplied 8-bit address is offset by X Register to index
// a location in page 0x00. The actual 16-bit address is Read 
// from this location
u8 Cpu::IZX()
{
	u16 t = Read(ip);
	ip++;

	u16 lo = Read((u16)(t + (u16)x) & 0x00FF);
	u16 hi = Read((u16)(t + (u16)x + 1) & 0x00FF);

	addr_abs = (hi << 8) | lo;
	
	return 0;
}


// Address Mode: Indirect Y
// The supplied 8-bit address indexes a location in page 0x00. From 
// here the actual 16-bit address is Read, and the contents of
// Y Register is added to it to offset it. If the offset causes a
// change in page then an additional clock cycle is required.
u8 Cpu::IZY()
{
	u16 t = Read(ip);
	ip++;

	u16 lo = Read(t & 0x00FF);
	u16 hi = Read((t + 1) & 0x00FF);

	addr_abs = (hi << 8) | lo;
	addr_abs += y;
	
	if ((addr_abs & 0xFF00) != (hi << 8))
		return 1;
	else
		return 0;
}

u8 Cpu::Fetch()
{
	if (!(lookup[opcode].addrmode == &Cpu::IMP))
		fetched = Read(addr_abs);
	return fetched;
}


/////////////////////////////////
// instruction implementation //
/////////////////////////////////

// Instruction: Add with Carry In
// Function:    acc = A + M + C
// Flags Out:   C, V, N, Z
//
// Explanation:
// The purpose of this function is to add a value to the accumulator and a carry bit. If
// the result is > 255 there is an overflow setting the carry bit. Ths allows you to
// chain together ADC instructions to add numbers larger than 8-bits. This in itself is
// simple, however the 6502 supports the concepts of Negativity/Positivity and Signed Overflow.
//
// 10000100 = 128 + 4 = 132 in normal circumstances, we know this as unsigned and it allows
// us to represent numbers between 0 and 255 (given 8 bits). The 6502 can also interpret 
// this word as something else if we assume those 8 bits represent the range -128 to +127,
// i.e. it has become signed.
//
// Since 132 > 127, it effectively wraps around, through -128, to -124. This wraparound is
// called overflow, and this is a useful to know as it indicates that the calculation has
// gone outside the permissable range, and therefore no longer makes numeric sense.
//
// Note the implementation of ADD is the same in binary, this is just about how the numbers
// are represented, so the word 10000100 can be both -124 and 132 depending upon the 
// context the programming is using it in. We can prove this!
//
//  10000100 =  132  or  -124
// +00010001 = + 17      + 17
//  ========    ===       ===     See, both are valid additions, but our interpretation of
//  10010101 =  149  or  -107     the context changes the value, not the hardware!
//
// In principle under the -128 to 127 range:
// 10000000 = -128, 11111111 = -1, 00000000 = 0, 00000000 = +1, 01111111 = +127
// therefore negative numbers have the most significant set, positive numbers do not
//
// To assist us, the 6502 can set the overflow flag, if the result of the addition has
// wrapped around. V <- ~(A^M) & A^(A+M+C) :D lol, let's work out why!
//
// Let's suppose we have acc = 30, M = 10 and C = 0
//          acc = 30 = 00011110
//          M = 10 = 00001010+
//     RESULT = 40 = 00101000
//
// Here we have not gone out of range. The resulting significant bit has not changed.
// So let's make a truth table to understand when overflow has occurred. Here I take
// the MSB of each component, where R is RESULT.
//
// A  M  R | V | A^R | A^M |~(A^M) | 
// 0  0  0 | 0 |  0  |  0  |   1   |
// 0  0  1 | 1 |  1  |  0  |   1   |
// 0  1  0 | 0 |  0  |  1  |   0   |
// 0  1  1 | 0 |  1  |  1  |   0   |  so V = ~(A^M) & (A^R)
// 1  0  0 | 0 |  1  |  1  |   0   |
// 1  0  1 | 0 |  0  |  1  |   0   |
// 1  1  0 | 1 |  1  |  0  |   1   |
// 1  1  1 | 0 |  0  |  0  |   1   |
//
// We can see how the above equation calculates V, based on A, M and R. V was chosen
// based on the following hypothesis:
//       Positive Number + Positive Number = Negative Result -> Overflow
//       Negative Number + Negative Number = Positive Result -> Overflow
//       Positive Number + Negative Number = Either Result -> Cannot Overflow
//       Positive Number + Positive Number = Positive Result -> OK! No Overflow
//       Negative Number + Negative Number = Negative Result -> OK! NO Overflow

u8 Cpu::ADC()
{
	// Grab the data that we are adding to the accumulator
	Fetch();
	
	// Add is performed in 16-bit domain for emulation to capture any
	// carry bit, which will exist in bit 8 of the 16-bit word
	tmp = (u16)acc + (u16)fetched + (u16)GetFlag(C);
	
	// The carry flag out exists in the high byte bit 0
	SetFlag(C, tmp > 255);
	
	// The Zero flag is set if the result is 0
	SetFlag(Z, (tmp & 0x00FF) == 0);
	
	// The signed Overflow flag is set based on all that up there! :D
	SetFlag(V, (~((u16)acc ^ (u16)fetched) & ((u16)acc ^ (u16)tmp)) & 0x0080);
	
	// The negative flag is set to the most significant bit of the result
	SetFlag(N, tmp & 0x80);
	
	// Load the result into the accumulator (it's 8-bit dont forget!)
	acc = tmp & 0x00FF;
	
	// This instruction has the potential to require an additional clock cycle
	return 1;
}


// Instruction: Subtraction with Borrow In
// Function:    acc = A - M - (1 - C)
// Flags Out:   C, V, N, Z
//
// Explanation:
// Given the explanation for ADC above, we can reorganise our data
// to use the same computation for addition, for subtraction by multiplying
// the data by -1, i.e. make it negative
//
// acc = A - M - (1 - C)  ->  acc = A + -1 * (M - (1 - C))  ->  acc = A + (-M + 1 + C)
//
// To make a signed positive number negative, we can invert the bits and add 1
// (OK, I lied, a little bit of 1 and 2s complement :P)
//
//  5 = 00000101
// -5 = 11111010 + 00000001 = 11111011 (or 251 in our 0 to 255 range)
//
// The range is actually unimportant, because if I take the value 15, and add 251
// to it, given we wrap around at 256, the result is 10, so it has effectively 
// subtracted 5, which was the original intention. (15 + 251) % 256 = 10
//
// Note that the equation above used (1-C), but this got converted to + 1 + C.
// This means we alReady have the +1, so all we need to do is invert the bits
// of M, the data(!) therfore we can simply add, exactly the same way we did 
// before.

u8 Cpu::SBC()
{
	Fetch();
	
	// Operating in 16-bit domain to capture carry out
	
	// We can invert the bottom 8 bits with bitwise xor
	u16 value = ((u16)fetched) ^ 0x00FF;
	
	// Notice this is exactly the same as addition from here!
	tmp = (u16)acc + value + (u16)GetFlag(C);
	SetFlag(C   , tmp & 0xFF00);
	SetFlag(Z, ((tmp & 0x00FF) == 0));
	SetFlag(V, (tmp ^ (u16)acc) & (tmp ^ value) & 0x0080);
	SetFlag(N, tmp & 0x0080);
	acc = tmp & 0x00FF;
	return 1;
}

// OK! Complicated operations are done! the following are much simpler
// and conventional. The typical order of events is:
// 1) Fetch the data you are working with
// 2) Perform calculation
// 3) Store the result in desired place
// 4) Set Flags of the status register
// 5) Return if instruction has potential to require additional 
//    clock cycle


// Instruction: Bitwise Logic AND
// Function:    acc = A & M
// Flags Out:   N, Z
u8 Cpu::AND()
{
	Fetch();
	acc = acc & fetched;
	SetFlag(Z, acc == 0x00);
	SetFlag(N, acc & 0x80);
	return 1;
}


// Instruction: Arithmetic Shift Left
// Function:    acc = C <- (A << 1) <- 0
// Flags Out:   N, Z, C
u8 Cpu::ASL()
{
	Fetch();
	tmp = (u16)fetched << 1;
	SetFlag(C, (tmp & 0xFF00) > 0);
	SetFlag(Z, (tmp & 0x00FF) == 0x00);
	SetFlag(N, tmp & 0x80);
	if (lookup[opcode].addrmode == &Cpu::IMP)
		acc = tmp & 0x00FF;
	else
		Write(addr_abs, tmp & 0x00FF);
	return 0;
}


// Instruction: Branch if Carry Clear
// Function:    if(C == 0) pc = address 
u8 Cpu::BCC()
{
	if (GetFlag(C) == 0)
	{
		cycles++;
		addr_abs = ip + addr_rel;
		
		if((addr_abs & 0xFF00) != (ip & 0xFF00))
			cycles++;
		
		ip = addr_abs;
	}
	return 0;
}


// Instruction: Branch if Carry Set
// Function:    if(C == 1) ip = address
u8 Cpu::BCS()
{
	if (GetFlag(C) == 1)
	{
		cycles++;
		addr_abs = ip + addr_rel;

		if ((addr_abs & 0xFF00) != (ip & 0xFF00))
			cycles++;

		ip = addr_abs;
	}
	return 0;
}


// Instruction: Branch if Equal
// Function:    if(Z == 1) ip = address
u8 Cpu::BEQ()
{
	if (GetFlag(Z) == 1)
	{
		cycles++;
		addr_abs = ip + addr_rel;

		if ((addr_abs & 0xFF00) != (ip & 0xFF00))
			cycles++;

		ip = addr_abs;
	}
	return 0;
}

u8 Cpu::BIT()
{
	Fetch();
	tmp = acc & fetched;
	SetFlag(Z, (tmp & 0x00FF) == 0x00);
	SetFlag(N, fetched & (1 << 7));
	SetFlag(V, fetched & (1 << 6));
	return 0;
}


// Instruction: Branch if Negative
// Function:    if(N == 1) ip = address
u8 Cpu::BMI()
{
	if (GetFlag(N) == 1)
	{
		cycles++;
		addr_abs = ip + addr_rel;

		if ((addr_abs & 0xFF00) != (ip & 0xFF00))
			cycles++;

		ip = addr_abs;
	}
	return 0;
}


// Instruction: Branch if Not Equal
// Function:    if(Z == 0) ip = address
u8 Cpu::BNE()
{
	if (GetFlag(Z) == 0)
	{
		cycles++;
		addr_abs = ip + addr_rel;

		if ((addr_abs & 0xFF00) != (ip & 0xFF00))
			cycles++;

		ip = addr_abs;
	}
	return 0;
}


// Instruction: Branch if Positive
// Function:    if(N == 0) ip = address
u8 Cpu::BPL()
{
	if (GetFlag(N) == 0)
	{
		cycles++;
		addr_abs = ip + addr_rel;

		if ((addr_abs & 0xFF00) != (ip & 0xFF00))
			cycles++;

		ip = addr_abs;
	}
	return 0;
}

// Instruction: Break
// Function:    Program Sourced Interrupt
u8 Cpu::BRK()
{
	ip++;
	
	SetFlag(I, 1);
	Write(0x0100 + sp, (ip >> 8) & 0x00FF);
	sp--;
	Write(0x0100 + sp, ip & 0x00FF);
	sp--;

	SetFlag(B, 1);
	Write(0x0100 + sp, status);
	sp--;
	SetFlag(B, 0);

	ip = (u16)Read(0xFFFE) | ((u16)Read(0xFFFF) << 8);
	return 0;
}


// Instruction: Branch if Overflow Clear
// Function:    if(V == 0) ip = address
u8 Cpu::BVC()
{
	if (GetFlag(V) == 0)
	{
		cycles++;
		addr_abs = ip + addr_rel;

		if ((addr_abs & 0xFF00) != (ip & 0xFF00))
			cycles++;

		ip = addr_abs;
	}
	return 0;
}


// Instruction: Branch if Overflow Set
// Function:    if(V == 1) ip = address
u8 Cpu::BVS()
{
	if (GetFlag(V) == 1)
	{
		cycles++;
		addr_abs = ip + addr_rel;

		if ((addr_abs & 0xFF00) != (ip & 0xFF00))
			cycles++;

		ip = addr_abs;
	}
	return 0;
}


// Instruction: Clear Carry Flag
// Function:    C = 0
u8 Cpu::CLC()
{
	SetFlag(C, false);
	return 0;
}


// Instruction: Clear Decimal Flag
// Function:    D = 0
u8 Cpu::CLD()
{
	SetFlag(D, false);
	return 0;
}


// Instruction: Disable Interrupts / Clear Interrupt Flag
// Function:    I = 0
u8 Cpu::CLI()
{
	SetFlag(I, false);
	return 0;
}


// Instruction: Clear Overflow Flag
// Function:    V = 0
u8 Cpu::CLV()
{
	SetFlag(V, false);
	return 0;
}

// Instruction: Compare Accumulator
// Function:    C <- A >= M      Z <- (A - M) == 0
// Flags Out:   N, C, Z
u8 Cpu::CMP()
{
	Fetch();
	tmp = (u16)acc - (u16)fetched;
	SetFlag(C, acc >= fetched);
	SetFlag(Z, (tmp & 0x00FF) == 0x0000);
	SetFlag(N, tmp & 0x0080);
	return 1;
}


// Instruction: Compare X Register
// Function:    C <- X >= M      Z <- (X - M) == 0
// Flags Out:   N, C, Z
u8 Cpu::CPX()
{
	Fetch();
	tmp = (u16)x - (u16)fetched;
	SetFlag(C, x >= fetched);
	SetFlag(Z, (tmp & 0x00FF) == 0x0000);
	SetFlag(N, tmp & 0x0080);
	return 0;
}


// Instruction: Compare Y Register
// Function:    C <- Y >= M      Z <- (Y - M) == 0
// Flags Out:   N, C, Z
u8 Cpu::CPY()
{
	Fetch();
	tmp = (u16)y - (u16)fetched;
	SetFlag(C, y >= fetched);
	SetFlag(Z, (tmp & 0x00FF) == 0x0000);
	SetFlag(N, tmp & 0x0080);
	return 0;
}


// Instruction: Decrement Value at Memory Location
// Function:    M = M - 1
// Flags Out:   N, Z
u8 Cpu::DEC()
{
	Fetch();
	tmp = fetched - 1;
	Write(addr_abs, tmp & 0x00FF);
	SetFlag(Z, (tmp & 0x00FF) == 0x0000);
	SetFlag(N, tmp & 0x0080);
	return 0;
}


// Instruction: Decrement X Register
// Function:    X = X - 1
// Flags Out:   N, Z
u8 Cpu::DEX()
{
	x--;
	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);
	return 0;
}


// Instruction: Decrement Y Register
// Function:    Y = Y - 1
// Flags Out:   N, Z
u8 Cpu::DEY()
{
	y--;
	SetFlag(Z, y == 0x00);
	SetFlag(N, y & 0x80);
	return 0;
}


// Instruction: Bitwise Logic XOR
// Function:    acc = A xor M
// Flags Out:   N, Z
u8 Cpu::EOR()
{
	Fetch();
	acc = acc ^ fetched;	
	SetFlag(Z, acc == 0x00);
	SetFlag(N, acc & 0x80);
	return 1;
}


// Instruction: Increment Value at Memory Location
// Function:    M = M + 1
// Flags Out:   N, Z
u8 Cpu::INC()
{
	Fetch();
	tmp = fetched + 1;
	Write(addr_abs, tmp & 0x00FF);
	SetFlag(Z, (tmp & 0x00FF) == 0x0000);
	SetFlag(N, tmp & 0x0080);
	return 0;
}


// Instruction: Increment X Register
// Function:    X = X + 1
// Flags Out:   N, Z
u8 Cpu::INX()
{
	x++;
	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);
	return 0;
}


// Instruction: Increment Y Register
// Function:    Y = Y + 1
// Flags Out:   N, Z
u8 Cpu::INY()
{
	y++;
	SetFlag(Z, y == 0x00);
	SetFlag(N, y & 0x80);
	return 0;
}


// Instruction: Jump To Location
// Function:    ip = address
u8 Cpu::JMP()
{
	ip = addr_abs;
	return 0;
}


// Instruction: Jump To Sub-Routine
// Function:    Push current ip to stack, ip = address
u8 Cpu::JSR()
{
	ip--;

	Write(0x0100 + sp, (ip >> 8) & 0x00FF);
	sp--;
	Write(0x0100 + sp, ip & 0x00FF);
	sp--;

	ip = addr_abs;
	return 0;
}


// Instruction: Load The Accumulator
// Function:    acc = M
// Flags Out:   N, Z
u8 Cpu::LDA()
{
	Fetch();
	acc = fetched;
	SetFlag(Z, acc == 0x00);
	SetFlag(N, acc & 0x80);
	return 1;
}


// Instruction: Load The X Register
// Function:    X = M
// Flags Out:   N, Z
u8 Cpu::LDX()
{
	Fetch();
	x = fetched;
	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);
	return 1;
}


// Instruction: Load The Y Register
// Function:    Y = M
// Flags Out:   N, Z
u8 Cpu::LDY()
{
	Fetch();
	y = fetched;
	SetFlag(Z, y == 0x00);
	SetFlag(N, y & 0x80);
	return 1;
}

u8 Cpu::LSR()
{
	Fetch();
	SetFlag(C, fetched & 0x0001);
	tmp = fetched >> 1;	
	SetFlag(Z, (tmp & 0x00FF) == 0x0000);
	SetFlag(N, tmp & 0x0080);
	if (lookup[opcode].addrmode == &Cpu::IMP)
		acc = tmp & 0x00FF;
	else
		Write(addr_abs, tmp & 0x00FF);
	return 0;
}

u8 Cpu::NOP()
{
	// Sadly not all NOPs are equal, Ive added a few here
	// based on https://wiki.nesdev.com/w/index.php/CPU_unofficial_opcodes
	// and will add more based on game compatibility, and ultimately
	// I'd like to cover all illegal opcodes too
	switch (opcode) {
	case 0x1C:
	case 0x3C:
	case 0x5C:
	case 0x7C:
	case 0xDC:
	case 0xFC:
		return 1;
		break;
	}
	return 0;
}


// Instruction: Bitwise Logic OR
// Function:    acc = A | M
// Flags Out:   N, Z
u8 Cpu::ORA()
{
	Fetch();
	acc = acc | fetched;
	SetFlag(Z, acc == 0x00);
	SetFlag(N, acc & 0x80);
	return 1;
}


// Instruction: Push Accumulator to Stack
// Function:    A -> stack
u8 Cpu::PHA()
{
	Write(0x0100 + sp, acc);
	sp--;
	return 0;
}


// Instruction: Push Status Register to Stack
// Function:    status -> stack
// Note:        Break flag is set to 1 before push
u8 Cpu::PHP()
{
	Write(0x0100 + sp, status | B | U);
	SetFlag(B, 0);
	SetFlag(U, 0);
	sp--;
	return 0;
}


// Instruction: Pop Accumulator off Stack
// Function:    A <- stack
// Flags Out:   N, Z
u8 Cpu::PLA()
{
	sp++;
	acc = Read(0x0100 + sp);
	SetFlag(Z, acc == 0x00);
	SetFlag(N, acc & 0x80);
	return 0;
}


// Instruction: Pop Status Register off Stack
// Function:    Status <- stack
u8 Cpu::PLP()
{
	sp++;
	status = Read(0x0100 + sp);
	SetFlag(U, 1);
	return 0;
}

u8 Cpu::ROL()
{
	Fetch();
	tmp = (u16)(fetched << 1) | GetFlag(C);
	SetFlag(C, tmp & 0xFF00);
	SetFlag(Z, (tmp & 0x00FF) == 0x0000);
	SetFlag(N, tmp & 0x0080);
	if (lookup[opcode].addrmode == &Cpu::IMP)
		acc = tmp & 0x00FF;
	else
		Write(addr_abs, tmp & 0x00FF);
	return 0;
}

u8 Cpu::ROR()
{
	Fetch();
	tmp = (u16)(GetFlag(C) << 7) | (fetched >> 1);
	SetFlag(C, fetched & 0x01);
	SetFlag(Z, (tmp & 0x00FF) == 0x00);
	SetFlag(N, tmp & 0x0080);
	if (lookup[opcode].addrmode == &Cpu::IMP)
		acc = tmp & 0x00FF;
	else
		Write(addr_abs, tmp & 0x00FF);
	return 0;
}

u8 Cpu::RTI()
{
	sp++;
	status = Read(0x0100 + sp);
	status &= ~B;
	status &= ~U;

	sp++;
	ip = (u16)Read(0x0100 + sp);
	sp++;
	ip |= (u16)Read(0x0100 + sp) << 8;
	return 0;
}

u8 Cpu::RTS()
{
	sp++;
	ip = (u16)Read(0x0100 + sp);
	sp++;
	ip |= (u16)Read(0x0100 + sp) << 8;
	
	ip++;
	return 0;
}




// Instruction: Set Carry Flag
// Function:    C = 1
u8 Cpu::SEC()
{
	SetFlag(C, true);
	return 0;
}


// Instruction: Set Decimal Flag
// Function:    D = 1
u8 Cpu::SED()
{
	SetFlag(D, true);
	return 0;
}


// Instruction: Set Interrupt Flag / Enable Interrupts
// Function:    I = 1
u8 Cpu::SEI()
{
	SetFlag(I, true);
	return 0;
}


// Instruction: Store Accumulator at Address
// Function:    M = A
u8 Cpu::STA()
{
	Write(addr_abs, acc);
	return 0;
}


// Instruction: Store X Register at Address
// Function:    M = X
u8 Cpu::STX()
{
	Write(addr_abs, x);
	return 0;
}


// Instruction: Store Y Register at Address
// Function:    M = Y
u8 Cpu::STY()
{
	Write(addr_abs, y);
	return 0;
}


// Instruction: Transfer Accumulator to X Register
// Function:    X = A
// Flags Out:   N, Z
u8 Cpu::TAX()
{
	x = acc;
	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);
	return 0;
}


// Instruction: Transfer Accumulator to Y Register
// Function:    Y = A
// Flags Out:   N, Z
u8 Cpu::TAY()
{
	y = acc;
	SetFlag(Z, y == 0x00);
	SetFlag(N, y & 0x80);
	return 0;
}


// Instruction: Transfer Stack Pointer to X Register
// Function:    X = stack pointer
// Flags Out:   N, Z
u8 Cpu::TSX()
{
	x = sp;
	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);
	return 0;
}

// Instruction: Transfer X Register to Accumulator
// Function:    acc = X
// Flags Out:   N, Z
u8 Cpu::TXA()
{
	acc = x;
	SetFlag(Z, acc == 0x00);
	SetFlag(N, acc & 0x80);
	return 0;
}

// Instruction: Transfer X Register to Stack Pointer
// Function:    stack pointer = X
u8 Cpu::TXS()
{
	sp = x;
	return 0;
}

// Instruction: Transfer Y Register to Accumulator
// Function:    acc = Y
// Flags Out:   N, Z
u8 Cpu::TYA()
{
	acc = y;
	SetFlag(Z, acc == 0x00);
	SetFlag(N, acc & 0x80);
	return 0;
}

// This function captures illegal opodes
u8 Cpu::XXX()
{
	return 0;
}

///////////////////////
// helper functions //
///////////////////////

bool Cpu::Complete()
{
	return cycles == 0;
}
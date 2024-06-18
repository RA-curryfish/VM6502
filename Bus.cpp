#include "Bus.h"

Bus::Bus()
{
    cpu.ConnectBus(this);
    for (auto cell : cpuRAM) cell = 0x00;
}

Bus::~Bus()
{
}

void Bus::CpuWrite(u16 addr, u8 data)
{
    if (cart->CpuWrite(addr, data))
	{
		// cartridge gets priority for reads and writes
	}
	else if(addr >= 0x0000 && addr <= 0x1FFF)
        cpuRAM[addr & 0x07FF] = data;
    else if (addr >= 0x2000 && addr <= 0x3FFF)
		ppu.CpuWrite(addr & 0x0007, data);
}

u8 Bus::CpuRead(u16 addr, bool bReadOnly)
{
	u8 data = 0x00;
	if (cart->CpuRead(addr, data))
	{
		// cartridge gets priority for reads and writes
	}
    else if(addr >= 0x0000 && addr <= 0x1FFF)
        data = cpuRAM[addr & 0x07FF]; // set range between 0 to 2kB. The other bytes are mirrored
    else if (addr >= 0x2000 && addr <= 0x3FFF)
	{
		// PPU Address range, mirrored every 8 bytes
		data = ppu.CpuRead(addr & 0x0007, bReadOnly);
	}
    else
        printf("memory access error");
    return data;
}

void Bus::InsertCartridge(const std::shared_ptr<Cartridge>& cartridge)
{
	// Connects cartridge to both Main Bus and CPU Bus
	this->cart = cartridge;
	ppu.ConnectCartridge(cartridge);
}

void Bus::Reset()
{
	cpu.Reset();
	nSystemClockCounter = 0;
}

void Bus::Clock()
{
	// Clocking. The heart and soul of an emulator. The running
	// frequency is controlled by whatever calls this function.
	// So here we "divide" the clock as necessary and call
	// the peripheral devices clock() function at the correct
	// times.

	// The fastest clock frequency the digital system cares
	// about is equivalent to the PPU clock. So the PPU is clocked
	// each time this function is called.
	ppu.Clock();

	// The CPU runs 3 times slower than the PPU so we only call its
	// clock() function every 3 times this function is called. We
	// have a global counter to keep track of this.
	if (nSystemClockCounter % 3 == 0)
	{
		cpu.Clock();
	}

	nSystemClockCounter++;
}
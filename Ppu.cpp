#include "Ppu.h"
#include "Cartridge.h"

Ppu::Ppu()
{

}

Ppu::~Ppu()
{

}

// olc::Sprite& Ppu::GetScreen()
// {
// 	return *sprScreen;
// }

// olc::Sprite & Ppu::GetNameTable(uint8_t i)
// {
// 	return *sprNameTable[i];
// }

// olc::Sprite & Ppu::GetPatternTable(uint8_t i)
// {
// 	return *sprPatternTable[i];
// }

u8 Ppu::CpuRead(u16 addr, bool rdonly = false)
{
    u8 data = 0x00;

	switch (addr)
	{
	case 0x0000: // Control
		break;
	case 0x0001: // Mask
		break;
	case 0x0002: // Status
		break;
	case 0x0003: // OAM Address
		break;
	case 0x0004: // OAM Data
		break;
	case 0x0005: // Scroll
		break;
	case 0x0006: // PPU Address
		break;
	case 0x0007: // PPU Data
		break;
	}

	return data;
}

void Ppu::CpuWrite(u16 addr, u8  data)
{
    switch (addr)
	{
	case 0x0000: // Control
		break;
	case 0x0001: // Mask
		break;
	case 0x0002: // Status
		break;
	case 0x0003: // OAM Address
		break;
	case 0x0004: // OAM Data
		break;
	case 0x0005: // Scroll
		break;
	case 0x0006: // PPU Address
		break;
	case 0x0007: // PPU Data
		break;
	}
}

u8 Ppu::PpuRead(u16 addr, bool rdonly = false)
{
    uint8_t data = 0x00;
	addr &= 0x3FFF;

	if (cart->PpuRead(addr, data))
	{

	}

	return data;
}

void Ppu::PpuWrite(u16 addr, u8 data)
{
    addr &= 0x3FFF;

	if (cart->PpuWrite(addr, data))
	{

	}
}

void Ppu::ConnectCartridge(const std::shared_ptr<Cartridge>& cartridge)
{
	this->cart = cartridge;
}

void Ppu::Clock()
{
	// Fake some noise for now
	sprScreen->SetPixel(cycle - 1, scanline, palScreen[(rand() % 2) ? 0x3F : 0x30]);

	// Advance renderer - it never stops, it's relentless
	cycle++;
	if (cycle >= 341)
	{
		cycle = 0;
		scanline++;
		if (scanline >= 261)
		{
			scanline = -1;
			frame_complete = true;
		}
	}
}
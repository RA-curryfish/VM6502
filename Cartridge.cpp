#include "Cartridge.h"

Cartridge::Cartridge(const std::string& sFileName)
{
    // iNES Format Header
	struct sHeader
	{
		char name[4];
		u8 prg_rom_chunks;
		u8 chr_rom_chunks;
		u8 mapper1;
		u8 mapper2;
		u8 prg_ram_size;
		u8 tv_system1;
		u8 tv_system2;
		char unused[5];
	} header;

	bImageValid = false;

	std::ifstream ifs;
	ifs.open(sFileName, std::ifstream::binary);
	if (ifs.is_open())
	{
		ifs.read((char*)&header, sizeof(sHeader));

		// skipping first 512 bytes of "trainer" information 
		if (header.mapper1 & 0x04)
			ifs.seekg(512, std::ios_base::cur);

		// get mapper ID
		nMapperID = ((header.mapper2 >> 4) << 4) | (header.mapper1 >> 4);
		mirror = (header.mapper1 & 0x01) ? VERTICAL : HORIZONTAL;

		// "Discover" File Format
		uint8_t nFileType = 1;

		if (nFileType == 0)
		{
            // placeholder
		}
		else if (nFileType == 1)
		{
			nPRGBanks = header.prg_rom_chunks;
			vPRGMemory.resize(nPRGBanks * 16384); // 16kB bank size
			ifs.read((char*)vPRGMemory.data(), vPRGMemory.size());

			nCHRBanks = header.chr_rom_chunks;
			vCHRMemory.resize(nCHRBanks * 8192); // 8kB bank size
			ifs.read((char*)vCHRMemory.data(), vCHRMemory.size());
		}
		else if (nFileType == 2)
		{
            // placeholder
		}

		// Load appropriate mapper
		switch (nMapperID)
		{
		case 0: pMapper = std::make_shared<Mapper_000>(nPRGBanks, nCHRBanks); break;
		}

		bImageValid = true;
		ifs.close();
	}
}

Cartridge::~Cartridge()
{

}

bool Cartridge::ImageValid()
{
	return bImageValid;
}

bool Cartridge::CpuRead(u16 addr, u8 &data)
{
	uint32_t mapped_addr = 0;
	if (pMapper->CpuMapRead(addr, mapped_addr))
	{
		data = vPRGMemory[mapped_addr];
		return true;
	}
	else
		return false;
}

bool Cartridge::CpuWrite(u16 addr, u8 data)
{
	uint32_t mapped_addr = 0;
	if (pMapper->CpuMapWrite(addr, mapped_addr))
	{
		vPRGMemory[mapped_addr] = data;
		return true;
	}
	else
		return false;
}

bool Cartridge::PpuRead(u16 addr, u8 & data)
{
	uint32_t mapped_addr = 0;
	if (pMapper->PpuMapRead(addr, mapped_addr))
	{
		data = vCHRMemory[mapped_addr];
		return true;
	}
	else
		return false;
}

bool Cartridge::PpuWrite(uint16_t addr, uint8_t data)
{
	uint32_t mapped_addr = 0;
	if (pMapper->PpuMapRead(addr, mapped_addr))
	{
		vCHRMemory[mapped_addr] = data;
		return true;
	}
	else
		return false;
}
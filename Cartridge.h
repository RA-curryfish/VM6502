#pragma once
#include "headers.h"
#include "Mapper_000.h"

class Cartridge
{
    public:
        Cartridge(const std::string& sFileName);
        ~Cartridge();

        // main bus aka CPU bus
        bool CpuRead(u16 addr, u8 &data);
        bool CpuWrite(u16 addr, u8 data);
        // PPU Bus
        bool PpuRead(u16 addr, u8 &data);
        bool PpuWrite(u16 addr, u8 data);
        bool ImageValid();

        enum MIRROR
        {
            HORIZONTAL,
            VERTICAL,
            ONESCREEN_LO,
            ONESCREEN_HI,
        } mirror = HORIZONTAL;
    
    private:
        u8 nMapperID = 0;
        u8 nPRGBanks = 0;
        u8 nCHRBanks = 0;
        bool bImageValid = false;

        std::vector<u8> vPRGMemory; // memory where the prg is in the cartridge
        std::vector<u8> vCHRMemory; // memory for characters/sprites? 

        std::shared_ptr<Mapper> pMapper;

};
#pragma once
#include "headers.h"

class Mapper
{
    public:
        Mapper(u8 prgBanks, u8 chrBanks);
        ~Mapper();

    public:
        // Transform CPU bus address into PRG ROM offset
        virtual bool CpuMapRead(u16 addr, uint32_t &mapped_addr) = 0;
        virtual bool CpuMapWrite(u16 addr, uint32_t &mapped_addr) = 0;
        // Transform PPU bus address into CHR ROM offset
        virtual bool PpuMapRead(u16 addr, uint32_t &mapped_addr) = 0;
        virtual bool PpuMapWrite(u16 addr, uint32_t &mapped_addr) = 0;

    protected:
        // These are stored locally as many of the mappers require this information
        u8 nPRGBanks = 0;
        u8 nCHRBanks = 0;
};
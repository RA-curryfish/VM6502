#pragma once
#include "Mapper.h"

class Mapper_000 : public Mapper
{
    public:
        Mapper_000(u8 prgBanks, u8 chrBanks);
        ~Mapper_000();

    public:
        bool CpuMapRead(u16 addr, uint32_t &mapped_addr) override;
        bool CpuMapWrite(u16 addr, uint32_t &mapped_addr) override;
        bool PpuMapRead(u16 addr, uint32_t &mapped_addr) override;
        bool PpuMapWrite(u16 addr, uint32_t &mapped_addr) override;
};
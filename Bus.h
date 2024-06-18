#pragma once

#include "headers.h"
#include "Cartridge.h"
#include "Cpu.h"
#include "Ppu.h"

class Bus
{
    public:
        Bus();
        ~Bus();
        
        void CpuWrite(u16 addr, u8 data);
        u8 CpuRead(u16 addr, bool bReadOnly = false);

        // Inserting cartridge into the NES
	    void InsertCartridge(const std::shared_ptr<Cartridge>& cartridge);
        // Resets the system
        void Reset();
        // Clocks the system - a single whole systme tick
        void Clock();
        
        u8 cpuRAM [2048]; // total memory of 2^11 * 8
        Cpu cpu;
        Ppu ppu;
        std::shared_ptr<Cartridge> cart;

    private:
        uint32_t nSystemClockCounter = 0;

};
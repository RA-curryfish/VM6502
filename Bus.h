#pragma once
#include "headers.h"
#include "Cpu.h"

class Bus
{
    public:
        Bus();
        ~Bus();
        
        void Write(u16 addr, u8 data);
        u8 Read(u16 addr, bool bReadOnly = false);
        
        u8 memory [65536]; // total memory of 2^16 * 8
        Cpu cpu;
};
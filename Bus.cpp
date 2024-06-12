#include "Bus.h"

Bus::Bus()
{
    cpu.ConnectBus(this);
    for (auto cell : memory) cell = 0x00;
}

Bus::~Bus()
{
}

void Bus::Write(u16 addr, u8 data)
{
    if(addr >= 0x0000 && addr <= 0xFFFF)
        memory[addr] = data;
    else
        printf("memory access error");
}

u8 Bus::Read(u16 addr, bool bReadOnly)
{
    if(addr >= 0x0000 && addr <= 0xFFFF)
        return memory[addr];
    //return bReadOnly ? memory[addr] : NULL;
    else
        printf("memory access error");
}
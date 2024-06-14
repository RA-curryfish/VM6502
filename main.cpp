#include "headers.h"
#include "Bus.h"
#include "Cpu.h"
#define vector std::vector
#define string std::string

u16 GetMemoryLoc(u8 lo, u8 hi)
{
    return (hi << 8) | lo;
}

void SetROMLoc(Bus *bus, u8 lo, u8 hi)
{
    bus->memory[GetMemoryLoc(0xFC,0xFF)] = lo;
    bus->memory[GetMemoryLoc(0xFD,0xFF)] = hi;
}

// todo: convert assembly to hex code
vector<string> GetHexCode(vector<string> code)
{

}

void InjectROM(Bus *bus, vector<string> code, u8 lo, u8 hi)
{
    // todo: use hex code here
    // vector<string> hexCode = GetHexCode(code);
    // for(auto inst: hexCode)
    // {
    //      vector<u8> hexy = inst.split(" ");
    //      for(auto byt: hexy)
    //      {
    //          if(lo != 0xFF)
    //              bus->memory[GetMemoryLoc(++lo,hi)] = byt
    //          else
    //              bus->memory[GetMemoryLoc(++lo,++hi)] = byt
    // }

    bus->memory[GetMemoryLoc(lo,hi)] = 0xA9;
    bus->memory[GetMemoryLoc(lo+1,hi)] = 0x02;
}

int main()
{
    Cpu myCpu;
    Bus myBus;

    // set up the memory for the code to jump to after reset, here, 0xAA00
    SetROMLoc(&myBus, 0x00, 0xAA);
    
    // set up the memory for actual code
    // LDA 0x02  ====> A9 0x02
    // 0xAA00: A9
    // 0xAA01: 02
    vector<string> code = {"LDA 0x02", "ADC 0x03"};
    InjectROM(&myBus, code, 0x00, 0xAA);

    myCpu.ConnectBus(&myBus);
    myCpu.Reset();
    int i=100;
    while(i-->0)
        myCpu.Clock();

    printf("Accumulator: %04x\n", myCpu.acc);

    return 0;
}
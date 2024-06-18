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
    bus->cpuRAM[GetMemoryLoc(0xFC,0xFF)] = lo;
    bus->cpuRAM[GetMemoryLoc(0xFD,0xFF)] = hi;
}

// todo: code to assemble
vector<string> GetHexDump(vector<string> code)
{

}

void InjectROM(Bus *bus, vector<string> code, u8 lo, u8 hi)
{
    // todo: use hex code here
    vector<u8> hexDump = {0xA9, 0x02, 0x69, 0x03};//GetHexDump(code);
    for(auto inst: hexDump)
    {
        bus->cpuRAM[GetMemoryLoc(lo,hi)] = inst;
        if(lo == 0xFF)  hi++;
        lo++;
    }
}

int main()
{
    Cpu myCpu;
    Bus myBus;

    // set up the memory for the code to jump to after reset, here, 0xAA00
    SetROMLoc(&myBus, 0x00, 0xAA);
    
    // set up the memory for actual code
    // LDA 0x02 ====> A9 0x02
    // 0xAA00: A9
    // 0xAA01: 02
    vector<string> code = {"LDA 0x02", "ADC 0x03"};
    InjectROM(&myBus, code, 0x00, 0xAA);

    myCpu.ConnectBus(&myBus);
    myCpu.Reset();
    bool end=false;
    do
    {
        end = myCpu.Clock(); 
    } while (!end);

    printf("Accumulator: %04x\n", myCpu.acc);

    return 0;
}
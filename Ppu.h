#include "headers.h"
#include "PixelGameEngine.h"

class Ppu
{
    public:
        Ppu();
        ~Ppu();
        
        // main bus aka CPU bus
        u8 CpuRead(u16 addr, bool rdonly = false);
        void CpuWrite(u16 addr, u8  data);
        // PPU Bus
        u8 PpuRead(u16 addr, bool rdonly = false);
        void PpuWrite(u16 addr, u8 data);
        void ConnectCartridge(const std::shared_ptr<Cartridge>& cartridge);
        void Clock();

        bool frame_complete = false;
        
        // olc::Sprite& GetScreen();
        // olc::Sprite& GetNameTable(uint8_t i);
        // olc::Sprite& GetPatternTable(uint8_t i);
    
    private:
        std::shared_ptr<Cartridge> cart;
        int16_t scanline = 0;
        int16_t cycle = 0;

        u8 tblName[2][1024]; // vram for name tables
        u8 tblPalette[32]; // memory for pallete
        // u8 tblPattern[2][4096];

        olc::Pixel  palScreen[0x40];
        olc::Sprite* sprScreen;
        olc::Sprite* sprNameTable[2];
        olc::Sprite* sprPatternTable[2];
};
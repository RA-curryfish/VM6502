# MOS 6502 Emulator

This is a basic 6502 emulator I made referencing this repository: https://github.com/OneLoneCoder/olcNES/tree/master

## Features
- It is a 8-bit processor having 2kB (8kB) of memory (mirrored 3 more times) with variable length instructions
- The address has upper 8 bits termed as 'pages' while the lower 8 bits termed as 'offsets'
- The CPU starts executing after the 'Reset' signal from the address hardcoded at page 0xFFFD and offset 0xFFFC
- In the NES, The PPU accesses memory for sprites, palettes and related information (which may be stored on the cartridge)
- The program is stored on cartridge ROM addressed between 0x4020 - 0xFFFF

## Todo 
- Continue the NES emulator as in the original project? 
- Add the assembler to convert the assembly code into a hexdump
- Run doom???

# MOS 6502 Emulator

This is a basic 6502 emulator I made referencing this repository: https://github.com/OneLoneCoder/olcNES/tree/master

## Features and working
- It is a 8-bit processor having 64kB of memory with variable length instructions
- The address has upper 8 bits termed as 'pages' while the lower 8 bits termed as 'offsets' 
- The CPU starts executing after the 'Reset' signal from the address hardcoded at page 0xFFFD and offset 0xFFFC

## Todo 
- Add the assembler to convert the assembly code into a hexdump
- Use interrupt requests to handle multiple tasks??
- Display graphics
- Run doom???

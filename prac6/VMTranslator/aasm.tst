// test file for the asm translated by the main program

load a.asm,

set RAM[0] 256,       // stack pointer
set RAM[1] 300,       // base address of the local segment
set RAM[2] 400,       // base address of the argument segment
set RAM[3] 3000,      // base address of the this segment
set RAM[4] 3010,      // base address of the that segment

set RAM[16] 1,        // static 0
set RAM[17] 20,       // static 1
set RAM[18] 3,        // static 2

set RAM[300] 10,      // local 0
set RAM[301] 20,      // local 1
set RAM[302] 30,      // local 2

set RAM[400] 100,     // argument 0
set RAM[401] 200,     // argument 1
set RAM[402] 300;     // argument 2

repeat 300 { 
  ticktock;
}
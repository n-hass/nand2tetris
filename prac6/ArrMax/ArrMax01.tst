// Sample Test file for ArrMax.asm
// Follows the Test Scripting Language format described in 
// Appendix B of the book "The Elements of Computing Systems"

load,
output-file ArrMax01.out,
compare-to ArrMax01.cmp,
output-list sp%D1.6.1 local%D1.6.1 argument%D1.8.1 this%D1.6.1 that%D1.6.1
            RAM[16]%D1.6.1 RAM[17]%D1.6.1 RAM[18]%D1.6.1
            local[0]%D1.8.1 local[1]%D1.8.1 local[2]%D1.8.1
            argument[0]%D1.11.1 argument[1]%D1.11.1 argument[2]%D1.11.1;

set sp 256,        // stack pointer
set local 300,     // base address of the local segment
set argument 400,  // base address of the argument segment
set this 3000,     // base address of the this segment
set that 3010,     // base address of the that segment

set RAM[16] 0,     // static 0
set RAM[17] 2048,  // static 1
set RAM[18] 12,     // static 2

set local[0] 10,   // local 0
set local[1] 20,   // local 1
set local[2] 30,   // local 2

set argument[0] 100,  // argument 0
set argument[1] 200,  // argument 1
set argument[2] 300,  // argument 2

set RAM[2048] 0,  // Set Arr[0]
set RAM[2049] -8,  // Set Arr[1]
set RAM[2050] -7,  // Set Arr[2]
set RAM[2051] -6;  // Set Arr[3]
set RAM[2052] -5;  // Set Arr[4]
set RAM[2053] -4;  // Set Arr[5]
set RAM[2054] -20;  // Set Arr[6]
set RAM[2055] 0;  // Set Arr[7]
set RAM[2056] 0;  // Set Arr[8]
set RAM[2057] 0;  // Set Arr[9]
set RAM[2058] 1;  // Set Arr[10]
set RAM[2059] -1;  // Set Arr[11]

repeat 400 {        // Change this number to cover the number of instructions in the VM test file
  vmstep;
}
output;
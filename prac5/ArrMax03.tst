// Sample Test file for ArrMax.asm
// Follows the Test Scripting Language format described in 
// Appendix B of the book "The Elements of Computing Systems"

load ArrMax.asm,
output-file ArrMax03.out,
compare-to ArrMax03.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[25]%D2.6.2 RAM[26]%D2.6.2 RAM[27]%D2.6.2 RAM[28]%D2.6.2;

set PC 0,
set RAM[0]    0,  // Set R0
set RAM[1]   25,  // Set R1
set RAM[2]    12,  // Set R2
set RAM[25] 5748,  // Set Arr[0]
set RAM[26] 0,  // Set Arr[1]
set RAM[27] -5748,  // Set Arr[2]
set RAM[28] 5749;  // Set Arr[3]
repeat 300 {
  ticktock;       // Run for 300 clock cycles
}
set RAM[1] 25,  // Restore arguments in case program used them
set RAM[2] 12,
output;           // Output to file


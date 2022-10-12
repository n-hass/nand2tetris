// Write a program in Hack assembly to calculate the absolute value (Links to an external site.) of a given number.

// Complete the code in Abs.asm
// Inputs:
//     R1 contains the number
// Outputs:
//     Write your final answer to R0
    @R1
    D=M
    @NEG
    D;JLT
    @R0
    M=D
    @END
    0;JMP
(NEG)
    @R0
    M=-D
(END)
    @END
    0;JMP
// Calculates R1 - R2 + R3 and stores the result in R0.
// (R0, R1, R2, R3 refer to RAM[0], RAM[1], RAM[2], and RAM[3], respectively.)

// Put your code here.
@R1
D = M
@R2
A = M
D = D - A
@R3
A = M
D = D + A
@R0
M = D

@END
0; JMP

(END)
  @END
  0; JMP
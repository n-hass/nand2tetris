// Calculates the absolute value of R1 and stores the result in R0.
@R1
D = M
@INVERT
D;JLT
@R0
M = D
@END
0;JMP


(INVERT)
  @R1
  D = !M
  D = D+1
  @R0
  M = D

  @END
  0;JMP

(END)
  @END
  0;JMP
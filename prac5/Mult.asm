// Multiplies R1 and R2 and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

@R3 // negative counter
M=0

// DETECT1
@R1
D=M
@SETNEGX
D; JLT

(DETECT2)
  @R2
  D=M
  @SETNEGY
  D; JLT
  @LOOPINIT
  0;JMP

(SETNEGX)
  @R3
  M=M+1
  @R1
  M=-M
  @DETECT2
  0;JMP

(SETNEGY)
  @R3
  M=M+1
  @R2
  M=-M
  @LOOPINIT
  0;JMP

(LOOPINIT)
  @i // make a loop counter
  M=0
  @R2
  D=M
  @R0 // initalise result
  M=0
  @LOOP
  0;JMP

(LOOP)
  @i
  D=M
  @R1
  D=D-M
  @POST_LOOP
  D;JGE // if the loop counter reaches 0, ie i-R1 = 0, exit the loop

  @R2
  D=M 
  @R0
  M=D+M // one round of addition
  @i
  M=M+1 // increment the loop counter
  @LOOP
  0;JMP

(POST_LOOP) // negative manager
  @R3
  D=M
  @END
  D;JLE

  @R0
  M=-M
  @R3
  M=M-1 // decrement the neg counter
  @POST_LOOP
  0;JMP

(END)
  @END
  0;JMP
// Finds the largest element in the array of length R2 whose first element is at RAM[R1] and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// initalise
@R0
M=0      
@R2 // if the array is of length 0 or less, just output 0
D=M
@END
D; JLE
// perform the max 

@R1     // store the first array element value
A=M // dereference the pointer at R1
D=M // store the value (RAM[R1]) in D
@R0 
M=D // copy the first array element value to the current maximum value

@R1 // copy pointer to array to variable 'ptr'
D=M
@ptr
M=D+1 // ptr starts at second element as there is no need to compare the first element to itself
@i
M=1 // loop initialiser

(LOOP)
  // test the loop condition
  @i
  D=M
  @R2
  D=D-M
  @END
  D;JGE // when i-R2=0, the array end has been reached


  @ptr
  A=M // dereference RAM[ptr]
  D=M // copy value at RAM[ptr] to D
  @R0 // the current maximum
  D=M-D
  @UPDATE_MAX
  D; JLT // when: current_max - *ptr < 0, then *ptr is larger than the current max

  (MAX_RETURN)
  @i
  M=M+1 // increment the loop
  @ptr
  M=M+1 // move the ptr up one memory address
  @LOOP
  0; JMP


(UPDATE_MAX) // assumes max is currently at ptr
  @ptr
  A=M // dereference
  D=M
  @R0
  M=D
  @MAX_RETURN
  0; JMP

(END)
  @END
  0;JMP
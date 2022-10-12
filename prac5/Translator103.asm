// Sorts the array of length R2 whose first element is at RAM[R1] in ascending order in place. Sets R0 to True (-1) when complete.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
// reuse the ArrMin code do selection search

// copy the original date to a different memory adderss

    @R3     // init outer index
    M=0

(OUTER)
    @R2
    D=M
    @R4        // init the inner index
    M=D-1

(INNER)                
    @R1      
    D=M
    @R4
    A=D+M           // goes to address arr[R4]
    D=A-1          
    @R5   // stores the address of arr[R4]
    M=D

    D=D+1           // goes to address arr[R4 - 1]
    @R6  // stores the address of arr[R4 - 1]
    M=D

    @R5
    A=M
    D=M               // get the value arr[R4]
    @R6
    A=M
    D=D-M             // calc val (arr[R4] - arr[R4 - 1])
    @SWAP
    D;JGT             // if(arr[R4] - arr[R4 - 1]) > 0 then swap values

    @R4                 
    M=M-1             // R4 = R4 - 1
    D=M
    @R3
    D=D-M
    @INNER            // if (R4 > R3) jump to inner loop
    D;JGT

    @R3               
    M=M+1    
    D=M
    @R2                
    D=M-D
    @OUTER            // if (R14 - R4 > 0) jump to outer loop
    D;JGT

    D=-1
    @R0
    M=D
(END)
    @END
    0;JMP



(SWAP)                // swaps arr[R4] and arr[R4-1]
    @R5
    A=M
    D=M
    @R7       // stores value of arr[R4]
    M=D

    @R6
    A=M
    D=M
    @R8       // stores the value of arr[R4-1]
    M=D

    @R8       // stores the value of arr[R4-1] in arr[R4]
    D=M
    @R5
    A=M
    M=D

    @R7        // stores the value of arr[R4] in arr[R4-1]
    D=M
    @R6
    A=M
    M=D

    @R4                 
    M=M-1          
    D=M
    @R3
    D=D-M
    @INNER              //if(R4 - R3 > 0) jump to INNER loop
    D;JGT

    @R3               
    M=M+1                   
    D=M
    @R2                
    D=M-D
    @OUTER              //if(length - R3 > 0) jump to outer loop 
    D;JGT
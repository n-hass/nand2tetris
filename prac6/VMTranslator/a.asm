@2	// push constant 2
D=A
@SP
A=M
M=D
@SP
M=M+1
@2	// push constant 2
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP	// eq
AM=M-1
D=M
A=A-1
D=M-D
@EQ.true_1
D;JEQ
@SP
A=M-1
M=0
@EQ.skip_1
0;JMP
(EQ.true_1)
@SP
A=M-1
M=-1
(EQ.skip_1)

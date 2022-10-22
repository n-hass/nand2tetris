@17	// push static 1
D=M
@SP
A=M
M=D
@SP
M=M+1
@LCL	// push local 1
D=M
@1
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP	// lt
AM=M-1
D=M
A=A-1
D=M-D
@LT.true_1
D;JLT
@SP
A=M-1
M=0
@LT.skip_1
0;JMP
(LT.true_1)
@SP
A=M-1
M=-1
(LT.skip_1)

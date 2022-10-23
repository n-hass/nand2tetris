@R5	// push temp 0
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG	// pop argument 1
D=M
@1
D=D+A
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D
@ARG	// push argument 1
D=M
@1
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
@19	// pop static 3
D=A
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D

// call myfoo
// store callers pointers
@SP
D=M
@R13
M=D
@RET.1
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL	// store LCL on stack
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG	// store ARG on stack
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS	// store THIS on stack
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT	// store THAT on stack
D=M
@SP
A=M
M=D
@SP
M=M+1
// setup ARG and LCL for callee
@R13	// update ARG
D=M
@1
D=D-A
@ARG
M=D
@SP	// update LCL
D=M
@LCL
M=D
@FUNC.defMod.myfoo
0;JMP
(RET.1)
// returning to caller
@LCL
D=M
@5
A=D-A
D=M
@R13
M=D
@SP
A=M-1
D=M
@ARG
A=M
M=D
D=A+1
@SP
M=D
@LCL
AM=M-1
D=M
@THAT
M=D
@LCL
AM=M-1
D=M
@THIS
M=D
@LCL
AM=M-1
D=M
@ARG
M=D
@LCL
A=M-1
D=M
@LCL
M=D
@R13	// jump back to caller
A=M
0;JMP
// call mybar
// store callers pointers
@SP
D=M
@R13
M=D
@RET.3
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL	// store LCL on stack
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG	// store ARG on stack
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS	// store THIS on stack
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT	// store THAT on stack
D=M
@SP
A=M
M=D
@SP
M=M+1
// setup ARG and LCL for callee
@R13	// update ARG
D=M
@2
D=D-A
@ARG
M=D
@SP	// update LCL
D=M
@LCL
M=D
@FUNC.defMod.mybar
0;JMP
(RET.3)

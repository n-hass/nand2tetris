@a	// jump to a
0;JMP
@SP	// if-goto a
AM=M-1
D=M
@a
D;JNE
(a)	// new label: a

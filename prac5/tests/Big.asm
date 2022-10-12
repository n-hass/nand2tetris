// Test 001
// Source: 
//
// (let ((x0 7)) (let ((x1 2)) (if (> (+ 2 2) (if (> 4 x1) 2 0)) (+ x0 x0) x0)))
// 
// Result (in RAM0): 14
// -----------------------------------//
@7
D=A
@x0
M=D
@2
D=A
@x1
M=D
// Do test, leave result in D
// Leave LHS in D; ends at bool-done118.
@2
D=A
@lhs119
M=D
@2
D=A
@rhs120
M=D
// Stick LHS result lhs119 in D
@lhs119
D=M
// Stick RHS result rhs120 in A
@rhs120
A=M
D=D+A
// Move to lhs114
@lhs114
M=D
// Leave RHS in D.
// Do test, leave result in D
// Leave LHS in D; ends at bool-done128.
@4
D=A
// Move to lhs124
@lhs124
M=D
// Leave RHS in D.
@x1
D=M
@rhs125
M=D
// Subtract LHS from RHS
@lhs124
D=M
@rhs125
// These instructions are prescient ... 20130308
A=M
D=A-D
@one127
// Jump and leave 1 in D if true.
D;JLT
@0
D=A
@bool-done128
0;JMP
(one127)
@1
D=A
// Done with boolean op.
(bool-done128)
// If the result was zero, we jump to iffalse122
@iffalse122
D;JEQ
@2
D=A
// Jump to the ifend123 when done with the true case.
@ifend123
0;JMP
(iffalse122)
@0
D=A
(ifend123)
@rhs115
M=D
// Subtract LHS from RHS
@lhs114
D=M
@rhs115
// These instructions are prescient ... 20130308
A=M
D=A-D
@one117
// Jump and leave 1 in D if true.
D;JLT
@0
D=A
@bool-done118
0;JMP
(one117)
@1
D=A
// Done with boolean op.
(bool-done118)
// If the result was zero, we jump to iffalse112
@iffalse112
D;JEQ
@x0
D=M
@lhs129
M=D
@x0
D=M
@rhs130
M=D
// Stick LHS result lhs129 in D
@lhs129
D=M
// Stick RHS result rhs130 in A
@rhs130
A=M
D=D+A
// Jump to the ifend113 when done with the true case.
@ifend113
0;JMP
(iffalse112)
@x0
D=M
(ifend113)
// Move D register to RAM[0] for final result.
@0
M=D
(ENDOFLINE)
@ENDOFLINE
0;JMP
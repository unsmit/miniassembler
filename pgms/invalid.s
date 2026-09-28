// Invalid FOOTv8 test cases

// Invalid registers
ADD X32,X1,X2
ADD x1,X2,X3
ADD X1,X2,X32

// 8-bit immediate overflow
ADDI X1,X2,#128
SUBI X1,X2,#-129
MULI X1,X2,#256
DIVI X1,X2,#-256

// 16-bit immediate overflow
MOV X1,#32768
MOV X1,#-32769
B #32768
B #-32769

// Invalid immediate formats
ADDI X1,X2,10
ADDI X1,X2,#
ADDI X1,X2,#abc
ADDI X1,X2,#10abc

// Missing operands
ADD X1,X2
ADDI X1,X2
MOV X1
CBZ X1

// Too many operands
ADD X1,X2,X3,X4
MOV X1,#10,X2

// Invalid instructions
HELLO X1,X2,X3
ADDS X1,X2,X3

// Valid instructions after errors to prove assembler continues
ADD X1,X2,X3
MOV X31,#32767
EXIT
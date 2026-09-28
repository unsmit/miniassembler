// FINAL FOOTv8 EDGE-CASE TEST

// ----- Explicit + and zero immediates: VALID -----
ADDI X1,X2,#+127
SUBI X3,X4,#+0
MULI X5,X6,#-0
MOV X7,#+32767
MOV X8,#0x0

// ----- Hex boundaries: VALID -----
ADDI X1,X2,#0x7f
SUBI X3,X4,#-0x80
MOV X5,#0x7fff
MOV X6,#-0x8000

// ----- Positive hex overflow: INVALID -----
ADDI X1,X2,#0x80
MOV X1,#0x8000

// ----- More case-insensitivity tests: VALID -----
ADD X1,X2,X3
aDdI X4,X5,#10
CbNeG X6,#-2

// ----- Comments: VALID -----
ADD X1,X2,X3//comment with no space
// comment-only line

// ----- Bad register formats: INVALID -----
ADD X-1,X2,X3
ADD X1abc,X2,X3
ADD XX1,X2,X3
ADD X32,X2,X3

// Worth seeing how your parser treats leading zero
ADD X01,X2,X3

// ----- Wrong operand types: INVALID -----
ADD X1,X2,#3
ADDI X1,X2,X3
MOV X1,X2
B X1
CBZ #1,#2

// ----- Extra operands: INVALID -----
NOP X1
EXIT X1
MOV X1,#10,X2

// ----- Missing operands: INVALID -----
ADD X1,X2
ADDI X1,X2
MOV
B
CBNZ X1

// ----- Bad comma syntax: INVALID -----
ADD X1,,X2,X3
ADD X1,X2,X3,
ADD ,X1,X2,X3
MOV X1,,#10

// ----- Bad bracket syntax: INVALID -----
LD X1,[X2,#10
LD X1,X2,#10]
LD X1,[[X2,#10]]
ST X1,[X2,#10]]
ST X1,]X2,#10[

// ----- Make sure valid code still works after all errors -----
ADD X31,X0,X1
MOV X31,#-32768
B #-1
EXIT
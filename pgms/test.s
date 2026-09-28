// FOOTv8 edge-case test

// Case-insensitive mnemonics
add X1,X2,X3
SuB X4,X5,X6
mUl X7,X8,X9
DiV X10,X11,X12

// 8-bit immediate boundaries
ADDI X1,X2,#127
SUBI X3,X4,#-128
MULI X5,X6,#0x7F
DIVI X7,X8,#-0x80

// 16-bit immediate boundaries
MOV X9,#32767
MOV X10,#-32768
MOV X11,#0x7FFF

// Register boundaries
ADD X0,X0,X0
ADD X31,X31,X31

// Loads and stores
LD X1,[X2,#127]
LD X3,[X4,#-128]
ST X5,[X6,#0x7F]
ST X7,[X8,#-0x80]

// 16-bit branch immediates
B #32767
B #-32768
CBZ X0,#1
CBNZ X31,#-1
CBNEG X15,#0x10

// Different legal separators
ADD X1 X2 X3
ADD X4, X5, X6
LD X7 [X8 #10]
ST X9, [X10, #-10]

// Comments after instructions
ADDI X1,X1,#1 // comment
NOP // comment

// Blank line below


EXIT
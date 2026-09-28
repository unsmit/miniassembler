// Tabs instead of spaces
ADD	X1	X2	X3

// Lots of whitespace
     ADD     X1     X2     X3     

// Comment immediately after instruction
EXIT//comment
NOP//comment

// Hex case variations
ADDI X1,X2,#0X7F
MOV X1,#0X7FFF

// Weird immediate signs — should be INVALID
ADDI X1,X2,#++1
ADDI X1,X2,#--1
ADDI X1,X2,#+-1
ADDI X1,X2,#-+1

// Incomplete hex — should be INVALID
ADDI X1,X2,#0x
MOV X1,#-0x

// Garbage following valid registers — INVALID
ADD X1a,X2,X3
ADD X1#,X2,X3

// Garbage following valid instruction
EXIT garbage
NOP garbage

// Just punctuation — INVALID
,
[
]
,,,

// Brackets on instructions that aren't LD/ST — INVALID
ADD X1,[X2,X3]
MOV [X1,#10]

// More LD/ST separator variations that should be valid
LD X1 [ X2 #10 ]
ST X1 , [ X2 , #-10 ]

// Immediate boundaries one away from limits — VALID
ADDI X1,X2,#126
ADDI X1,X2,#-127
MOV X1,#32766
MOV X1,#-32767
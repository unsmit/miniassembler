# Mini Assembler

A command-line assembler written in C that translates FOOTv8 assembly programs into 32-bit machine code. The project implements lexical parsing, instruction validation, binary encoding, error handling, and object-file generation.

## Features

- Translates 17 FOOTv8 instructions into 32-bit machine code
- Parses arithmetic, memory, branch, and control instructions
- Encodes opcodes, registers, and signed immediate values using bitwise operations
- Supports decimal and hexadecimal immediates with 8-bit and 16-bit two's complement encoding
- Validates instruction syntax, registers, operand types, and immediate ranges
- Supports case-insensitive instruction mnemonics, comments, and multiple operand separators
- Detects malformed instructions and substitutes `NOP` instructions while preserving program offsets
- Generates ASCII hexadecimal object files from assembly source files

## Supported Instructions

`NOP` `ADD` `ADDI` `SUB` `SUBI` `MUL` `MULI` `DIV` `DIVI` `LD` `ST` `EXIT` `MOV` `B` `CBZ` `CBNZ` `CBNEG`

## Build

```bash
cd code
make
```

This builds the `asm` executable in the project root.

## Usage

```bash
./asm <program.s>
```

For example:

```bash
./asm pgms/c2f.s
```

The assembler generates an object file with the same path and filename:

```text
pgms/c2f.o
```

## Example

Assembly:

```asm
MOV X0,#4000
LD X1,[X0,#0]
MULI X1,X1,#9
DIVI X1,X1,#5
ADDI X1,X1,#32
ST X1,[X0,#4]
EXIT
```

Generated object code:

```text
00000000 11000fa0
00000004 0b010000
00000008 07010109
0000000c 09010105
00000010 03010120
00000014 0d010004
00000018 0e000000
```

## Architecture

The assembler uses a modular design that separates parsing and machine-code generation:

- `parser.c` — tokenization and validation of instructions, registers, operands, and immediate values
- `asm.c` — source-file processing, instruction encoding, and object-file generation
- `parser.h` / `asm.h` — interfaces and shared data structures
- `Makefile` — separate compilation and linking

Each source instruction is parsed and validated before its opcode and operands are packed into a 32-bit machine instruction using bitwise shifts and masks.

## Testing

Tested across valid and malformed assembly programs, including register and immediate boundaries, signed two's complement values, hexadecimal input, syntax errors, comments, and whitespace variations.

Compiled with GCC using `-Wall` and tested with Valgrind for memory errors and leaks.

## Technologies

**C · GCC · Make · Valgrind · Git**

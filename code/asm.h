#ifndef ASM_H
#define ASM_H
#include <stdbool.h>
#include "parser.h"

typedef struct {
    const char *name;
    unsigned char opcode;
} Opcode;

unsigned int encodeInstruction(Instruction *instruction);
unsigned char registerValue(char *token);
int immediateValue(char *token);
unsigned char getOpcode(char *name);

#endif
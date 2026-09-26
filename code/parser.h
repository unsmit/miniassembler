#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_TOKENS 4
#define MAX_TOKEN_LENGTH 16

typedef struct{
    char tokens[MAX_TOKENS][MAX_TOKEN_LENGTH];

} Instruction;

int parseLine(char *line, Instruction *instruction);
bool validateInstruction(Instruction *instruction);


#endif
#include "parser.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define NUM_INSTRUCTIONS 17

const char *VALID_INSTRUCTIONS[NUM_INSTRUCTIONS] = {
    "NOP",
    "ADD",
    "ADDI",
    "SUB",
    "SUBI",
    "MUL",
    "MULI",
    "DIV",
    "DIVI",
    "LD",
    "ST",
    "EXIT",
    "MOV",
    "B",
    "CBZ",
    "CBNZ",
    "CBNEG"
};

int parseLine(char *line, Instruction *instruction){
    int lineIndex = 0; // position in line
    int tokenIndex = 0; // which token
    int charIndex = 0; // position in token
    char c = line[lineIndex]; // current char

    // tokenize into tokens array in instruction struct
    while(c != '\0'){
        while(line[lineIndex] != ' ' && line[lineIndex] != ',' && line[lineIndex] != '\0'){
            instruction->tokens[tokenIndex][charIndex] = line[lineIndex];
            charIndex++;
            lineIndex++;
        }

        instruction->tokens[tokenIndex][charIndex] = '\0';
        tokenIndex++;

        if(line[lineIndex] != '\0'){
            lineIndex++;
            charIndex = 0;
        }

        while (line[lineIndex] == ' ') {
            lineIndex++;
        }

        if(line[lineIndex] == ',' || line[lineIndex] == '\0'){
           return 0;
        }

        c = line[lineIndex];
    }
    return 1; 
}

bool validateInstruction(Instruction *instruction){
    // check first token
    for(int j = 0; j < NUM_INSTRUCTIONS; j++){
        if(!strcmp(instruction->tokens[0], VALID_INSTRUCTIONS[j])){
            return true;
        }
    }

    return false;
}
#include <stdio.h>

#include "parser.h"

int main() {

    char line[] = "SUB X1,X2,";

    Instruction instruction;

    if(!parseLine(line, &instruction)){
        return 0;
    }

    
    
    if(validateInstruction(&instruction)){
        for (int i = 0; i < 4; i++) {
            printf("Token %d: %s\n", i, instruction.tokens[i]);
        }
    }

    

    return 0;

}
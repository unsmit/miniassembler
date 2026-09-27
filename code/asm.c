/*-----------------------------------------------------------------------------
	Program to create object code from assembly input
		Reads assembly program
		Writes ASCII hex version of binary machine code to object file
-----------------------------------------------------------------------------*/
#include "asm.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUM_OPCODES 17

const Opcode OPCODES[] = {
	{"nop", 0x00},
	{"add", 0x02},
	{"addi", 0x03},
	{"sub", 0x04},
	{"subi", 0x05},
	{"mul", 0x06},
	{"muli", 0x07},
	{"div", 0x08},
	{"divi", 0x09},
	{"ld", 0x0B},
	{"st", 0x0D},
	{"exit", 0x0E},
	{"mov", 0x11},
	{"b", 0x13},
	{"cbz", 0x15},
	{"cbnz", 0x17},
	{"cbneg", 0x19}};


int main(int argc, char **argv)
{
	// TODO: Code to assemble FOOTv8 assembly input goes here
	Instruction instruction;
	char line[256];
	FILE *inputFile;
	int lineNum = 0;
	unsigned int offset = 0;

	if (argc != 2)
	{
		printf("Invalid command-line usage\n");
		return 0;
	}

	FILE *outputFile;
	outputFile = fopen("output.o", "w");
	if (outputFile == NULL)
	{
		printf("Could not create output file.");
		return 1;
	}


	inputFile = fopen(argv[1], "r");
	if (inputFile == NULL)
	{
		printf("Invalid file or file path\n");
		fclose(outputFile);
		return 0;
	}

	while (fgets(line, sizeof(line), inputFile) != NULL)
	{
		lineNum++;

		if (!parseLine(line, &instruction))
		{
			printf("Invalid token on line: %d\n", lineNum);
			fprintf(outputFile, "%08x %08x\n", offset, 0);
			offset += 4;
			continue;
		}

		if (instruction.numTokens == 0)
		{
			continue;
		}

		if (!validateInstruction(&instruction))
		{
    		printf("Invalid instruction on line: %d\n", lineNum);
    		fprintf(outputFile, "%08x %08x\n", offset, 0);
    		offset += 4;
    		continue;
		}
		// parse line into instruction

		// if blank/comment-only, skip it

		// validate instruction

		// encode instruction

		// write encoded instruction

		// next iteration reuses instruction
	}

	fclose(inputFile);
	fclose(outputFile);

	return 0;
}

unsigned int encodeInstruction(Instruction *instruction){
	unsigned int value = 0;

	return value;
}

unsigned char registerValue(char *token){
	int value;
	sscanf(token+1, "%d", &value);

	return (unsigned char) value;
}

int immediateValue(char *token){
	int value;
	sscanf(token+1, "%i", &value);

	return value;
}

unsigned char getOpcode(char *name){
	for(int i = 0; i < NUM_OPCODES; i++){
		if(!strcmp(OPCODES[i].name, name)){
			return OPCODES[i].opcode;
		}
	}

	return 0;
}

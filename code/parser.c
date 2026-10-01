#include "parser.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define NUM_INSTRUCTIONS 17
#define NUM_REGISTERS 32

const char *VALID_INSTRUCTIONS[NUM_INSTRUCTIONS] = {
    "nop",
    "add",
    "addi",
    "sub",
    "subi",
    "mul",
    "muli",
    "div",
    "divi",
    "ld",
    "st",
    "exit",
    "mov",
    "b",
    "cbz",
    "cbnz",
    "cbneg"};

const char *VALID_REGISTERS[NUM_REGISTERS] = {
    "X0",
    "X1",
    "X2",
    "X3",
    "X4",
    "X5",
    "X6",
    "X7",
    "X8",
    "X9",
    "X10",
    "X11",
    "X12",
    "X13",
    "X14",
    "X15",
    "X16",
    "X17",
    "X18",
    "X19",
    "X20",
    "X21",
    "X22",
    "X23",
    "X24",
    "X25",
    "X26",
    "X27",
    "X28",
    "X29",
    "X30",
    "X31"};

int parseLine(char *line, Instruction *instruction)
{
    int lineIndex = 0;
    int tokenIndex = 0;
    int charIndex = 0;
    bool allowBrackets = false;
    bool sawOpenBracket = false;
    bool sawCloseBracket = false;

    instruction->numTokens = 0;

    while (line[lineIndex] == ' ' ||
           line[lineIndex] == '\t' ||
           line[lineIndex] == '\n' ||
           line[lineIndex] == '\r')
    {
        lineIndex++;
    }

    if (line[lineIndex] == '\0' ||
        (line[lineIndex] == '/' && line[lineIndex + 1] == '/'))
    {
        return 1;
    }

    while (line[lineIndex] != '\0' &&
           line[lineIndex] != '\n' &&
           line[lineIndex] != '\r')
    {
        if (line[lineIndex] == '/' && line[lineIndex + 1] == '/')
        {
            break;
        }

        while (line[lineIndex] == ' ' || line[lineIndex] == '\t')
        {
            lineIndex++;
        }

        if (line[lineIndex] == '\0' ||
            line[lineIndex] == '\n' ||
            line[lineIndex] == '\r' ||
            (line[lineIndex] == '/' && line[lineIndex + 1] == '/'))
        {
            break;
        }

        if (tokenIndex >= MAX_TOKENS)
        {
            return 0;
        }

        charIndex = 0;

        while (line[lineIndex] != ' ' &&
               line[lineIndex] != '\t' &&
               line[lineIndex] != ',' &&
               line[lineIndex] != '[' &&
               line[lineIndex] != ']' &&
               line[lineIndex] != '\n' &&
               line[lineIndex] != '\r' &&
               line[lineIndex] != '\0')
        {
            if (line[lineIndex] == '/' && line[lineIndex + 1] == '/')
            {
                break;
            }

            if (charIndex >= MAX_TOKEN_LENGTH - 1)
            {
                return 0;
            }

            instruction->tokens[tokenIndex][charIndex] =
                line[lineIndex];

            charIndex++;
            lineIndex++;
        }

        if (charIndex > 0)
        {
            instruction->tokens[tokenIndex][charIndex] = '\0';

            if (tokenIndex == 0)
            {
                char opcode[MAX_TOKEN_LENGTH];

                for (int i = 0; instruction->tokens[0][i] != '\0'; i++)
                {
                    opcode[i] =
                        tolower((unsigned char)instruction->tokens[0][i]);
                    opcode[i + 1] = '\0';
                }

                if (!strcmp(opcode, "ld") || !strcmp(opcode, "st"))
                {
                    allowBrackets = true;
                }
            }

            tokenIndex++;
        }

        if (line[lineIndex] == '/' && line[lineIndex + 1] == '/')
        {
            break;
        }

        while (line[lineIndex] == ' ' || line[lineIndex] == '\t')
        {
            lineIndex++;
        }

        if (line[lineIndex] == ',')
        {
            if (tokenIndex == 1)
            {
                return 0;
            }

            lineIndex++;

            while (line[lineIndex] == ' ' || line[lineIndex] == '\t')
            {
                lineIndex++;
            }

            if (line[lineIndex] == '\0' ||
                line[lineIndex] == '\n' ||
                line[lineIndex] == '\r' ||
                line[lineIndex] == ',' ||
                (line[lineIndex] == '/' && line[lineIndex + 1] == '/'))
            {
                return 0;
            }
        }

        if (line[lineIndex] == '[')
        {
            if (!allowBrackets ||
                sawOpenBracket ||
                sawCloseBracket ||
                tokenIndex != 2)
            {
                return 0;
            }

            sawOpenBracket = true;
            lineIndex++;
        }
        else if (line[lineIndex] == ']')
        {
            if (!allowBrackets ||
                !sawOpenBracket ||
                sawCloseBracket ||
                tokenIndex != 4)
            {
                return 0;
            }

            sawCloseBracket = true;
            lineIndex++;
        }
    }

    if (allowBrackets)
    {
        if (!sawOpenBracket || !sawCloseBracket)
        {
            return 0;
        }
    }
    else
    {
        if (sawOpenBracket || sawCloseBracket)
        {
            return 0;
        }
    }

    instruction->numTokens = tokenIndex;
    return 1;
}

bool validateInstruction(Instruction *instruction)
{
    for (int i = 0; instruction->tokens[0][i] != '\0'; i++)
    {
        instruction->tokens[0][i] =
            tolower((unsigned char)instruction->tokens[0][i]);
    }

    for (int j = 0; j < NUM_INSTRUCTIONS; j++)
    {
        if (!strcmp(instruction->tokens[0], VALID_INSTRUCTIONS[j]))
        {
            if (validateOps(instruction))
            {
                return true;
            }
            else
            {
                break;
            }
        }
    }

    return false;
}

bool validateOps(Instruction *instruction)
{
    bool firstInst = false;
    bool secondInst = false;
    bool thirdInst = false;

    if (!strcmp(instruction->tokens[0], "add"))
    {
        if (instruction->numTokens != 4)
        {
            return false;
        }

        for (int i = 0; i < NUM_REGISTERS; i++)
        {
            if (!strcmp(instruction->tokens[1], VALID_REGISTERS[i]))
            {
                firstInst = true;
            }

            if (!strcmp(instruction->tokens[2], VALID_REGISTERS[i]))
            {
                secondInst = true;
            }

            if (!strcmp(instruction->tokens[3], VALID_REGISTERS[i]))
            {
                thirdInst = true;
            }
        }

        if (firstInst && secondInst && thirdInst)
        {
            return true;
        }

        return false;
    }
    else if (!strcmp(instruction->tokens[0], "addi"))
    {
        if (instruction->numTokens != 4)
        {
            return false;
        }

        for (int i = 0; i < NUM_REGISTERS; i++)
        {
            if (!strcmp(instruction->tokens[1], VALID_REGISTERS[i]))
            {
                firstInst = true;
            }

            if (!strcmp(instruction->tokens[2], VALID_REGISTERS[i]))
            {
                secondInst = true;
            }
        }

        if (validImmediate(instruction->tokens[3], 8))
        {
            thirdInst = true;
        }

        if (firstInst && secondInst && thirdInst)
        {
            return true;
        }

        return false;
    }
    else if (!strcmp(instruction->tokens[0], "sub"))
    {
        if (instruction->numTokens != 4)
        {
            return false;
        }

        for (int i = 0; i < NUM_REGISTERS; i++)
        {
            if (!strcmp(instruction->tokens[1], VALID_REGISTERS[i]))
            {
                firstInst = true;
            }

            if (!strcmp(instruction->tokens[2], VALID_REGISTERS[i]))
            {
                secondInst = true;
            }

            if (!strcmp(instruction->tokens[3], VALID_REGISTERS[i]))
            {
                thirdInst = true;
            }
        }

        if (firstInst && secondInst && thirdInst)
        {
            return true;
        }

        return false;
    }
    else if (!strcmp(instruction->tokens[0], "subi"))
    {
        if (instruction->numTokens != 4)
        {
            return false;
        }

        for (int i = 0; i < NUM_REGISTERS; i++)
        {
            if (!strcmp(instruction->tokens[1], VALID_REGISTERS[i]))
            {
                firstInst = true;
            }

            if (!strcmp(instruction->tokens[2], VALID_REGISTERS[i]))
            {
                secondInst = true;
            }
        }

        if (validImmediate(instruction->tokens[3], 8))
        {
            thirdInst = true;
        }

        if (firstInst && secondInst && thirdInst)
        {
            return true;
        }

        return false;
    }
    else if (!strcmp(instruction->tokens[0], "mul"))
    {
        if (instruction->numTokens != 4)
        {
            return false;
        }

        for (int i = 0; i < NUM_REGISTERS; i++)
        {
            if (!strcmp(instruction->tokens[1], VALID_REGISTERS[i]))
            {
                firstInst = true;
            }

            if (!strcmp(instruction->tokens[2], VALID_REGISTERS[i]))
            {
                secondInst = true;
            }

            if (!strcmp(instruction->tokens[3], VALID_REGISTERS[i]))
            {
                thirdInst = true;
            }
        }

        if (firstInst && secondInst && thirdInst)
        {
            return true;
        }

        return false;
    }
    else if (!strcmp(instruction->tokens[0], "muli"))
    {
        if (instruction->numTokens != 4)
        {
            return false;
        }

        for (int i = 0; i < NUM_REGISTERS; i++)
        {
            if (!strcmp(instruction->tokens[1], VALID_REGISTERS[i]))
            {
                firstInst = true;
            }

            if (!strcmp(instruction->tokens[2], VALID_REGISTERS[i]))
            {
                secondInst = true;
            }
        }

        if (validImmediate(instruction->tokens[3], 8))
        {
            thirdInst = true;
        }

        if (firstInst && secondInst && thirdInst)
        {
            return true;
        }

        return false;
    }
    else if (!strcmp(instruction->tokens[0], "div"))
    {
        if (instruction->numTokens != 4)
        {
            return false;
        }

        for (int i = 0; i < NUM_REGISTERS; i++)
        {
            if (!strcmp(instruction->tokens[1], VALID_REGISTERS[i]))
            {
                firstInst = true;
            }

            if (!strcmp(instruction->tokens[2], VALID_REGISTERS[i]))
            {
                secondInst = true;
            }

            if (!strcmp(instruction->tokens[3], VALID_REGISTERS[i]))
            {
                thirdInst = true;
            }
        }

        if (firstInst && secondInst && thirdInst)
        {
            return true;
        }

        return false;
    }
    else if (!strcmp(instruction->tokens[0], "divi"))
    {
        if (instruction->numTokens != 4)
        {
            return false;
        }

        for (int i = 0; i < NUM_REGISTERS; i++)
        {
            if (!strcmp(instruction->tokens[1], VALID_REGISTERS[i]))
            {
                firstInst = true;
            }

            if (!strcmp(instruction->tokens[2], VALID_REGISTERS[i]))
            {
                secondInst = true;
            }
        }

        if (validImmediate(instruction->tokens[3], 8))
        {
            thirdInst = true;
        }

        if (firstInst && secondInst && thirdInst)
        {
            return true;
        }

        return false;
    }
    else if (!strcmp(instruction->tokens[0], "ld"))
    {
        if (instruction->numTokens != 4)
        {
            return false;
        }

        for (int i = 0; i < NUM_REGISTERS; i++)
        {
            if (!strcmp(instruction->tokens[1], VALID_REGISTERS[i]))
            {
                firstInst = true;
            }

            if (!strcmp(instruction->tokens[2], VALID_REGISTERS[i]))
            {
                secondInst = true;
            }
        }

        if (validImmediate(instruction->tokens[3], 8))
        {
            thirdInst = true;
        }

        if (firstInst && secondInst && thirdInst)
        {
            return true;
        }

        return false;
    }
    else if (!strcmp(instruction->tokens[0], "st"))
    {
        if (instruction->numTokens != 4)
        {
            return false;
        }

        for (int i = 0; i < NUM_REGISTERS; i++)
        {
            if (!strcmp(instruction->tokens[1], VALID_REGISTERS[i]))
            {
                firstInst = true;
            }

            if (!strcmp(instruction->tokens[2], VALID_REGISTERS[i]))
            {
                secondInst = true;
            }
        }

        if (validImmediate(instruction->tokens[3], 8))
        {
            thirdInst = true;
        }

        if (firstInst && secondInst && thirdInst)
        {
            return true;
        }

        return false;
    }
    else if (!strcmp(instruction->tokens[0], "exit"))
    {
        if (instruction->numTokens != 1)
        {
            return false;
        }

        return true;
    }
    else if (!strcmp(instruction->tokens[0], "mov"))
    {
        if (instruction->numTokens != 3)
        {
            return false;
        }

        for (int i = 0; i < NUM_REGISTERS; i++)
        {
            if (!strcmp(instruction->tokens[1], VALID_REGISTERS[i]))
            {
                firstInst = true;
            }
        }

        if (validImmediate(instruction->tokens[2], 16))
        {
            secondInst = true;
        }

        if (firstInst && secondInst)
        {
            return true;
        }

        return false;
    }
    else if (!strcmp(instruction->tokens[0], "b"))
    {
        if (instruction->numTokens != 2)
        {
            return false;
        }

        if (validImmediate(instruction->tokens[1], 16))
        {
            return true;
        }

        return false;
    }
    else if (!strcmp(instruction->tokens[0], "cbz"))
    {
        if (instruction->numTokens != 3)
        {
            return false;
        }

        for (int i = 0; i < NUM_REGISTERS; i++)
        {
            if (!strcmp(instruction->tokens[1], VALID_REGISTERS[i]))
            {
                firstInst = true;
            }
        }

        if (validImmediate(instruction->tokens[2], 16))
        {
            secondInst = true;
        }

        if (firstInst && secondInst)
        {
            return true;
        }

        return false;
    }
    else if (!strcmp(instruction->tokens[0], "cbnz"))
    {
        if (instruction->numTokens != 3)
        {
            return false;
        }

        for (int i = 0; i < NUM_REGISTERS; i++)
        {
            if (!strcmp(instruction->tokens[1], VALID_REGISTERS[i]))
            {
                firstInst = true;
            }
        }

        if (validImmediate(instruction->tokens[2], 16))
        {
            secondInst = true;
        }

        if (firstInst && secondInst)
        {
            return true;
        }

        return false;
    }
    else if (!strcmp(instruction->tokens[0], "cbneg"))
    {
        if (instruction->numTokens != 3)
        {
            return false;
        }

        for (int i = 0; i < NUM_REGISTERS; i++)
        {
            if (!strcmp(instruction->tokens[1], VALID_REGISTERS[i]))
            {
                firstInst = true;
            }
        }

        if (validImmediate(instruction->tokens[2], 16))
        {
            secondInst = true;
        }

        if (firstInst && secondInst)
        {
            return true;
        }

        return false;
    }
    else if (!strcmp(instruction->tokens[0], "nop"))
    {
        if (instruction->numTokens != 1)
        {
            return false;
        }

        return true;
    }

    return false;
}

bool validImmediate(char *token, int bits)
{
    int value;
    char extra;

    if (token[0] != '#' || token[1] == '\0')
    {
        return false;
    }

    if (sscanf(token + 1, "%i%c", &value, &extra) != 1)
    {
        return false;
    }

    if (bits == 8)
    {
        if (value < -128 || value > 127)
        {
            return false;
        }
    }
    else if (bits == 16)
    {
        if (value < -32768 || value > 32767)
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    return true;
}
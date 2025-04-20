#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_SYMBOL_TABLE 50
#define MAX_LINE_LENGTH 100

// Structure for Symbol Table entry
typedef struct {
    char label[20];
    int address;
} SymbolTableEntry;

// Structure for Opcode Table entry
typedef struct {
    char opcode[10];
    char hexcode[3];
} OpcodeTableEntry;

// Global variables
SymbolTableEntry symbolTable[MAX_SYMBOL_TABLE];
OpcodeTableEntry opcodeTable[10] = {
    {"LDA", "03"},
    {"STA", "0F"},
    {"LDCH", "53"},
    {"STCH", "57"},
    {"END", "**"}
};
int programLength;
char progName[20];
int startAddress;
int programSize;

// Function to find opcode value
char* getOpcodeValue(char* opcode) {
    for (int i = 0; i < 5; i++) {
        if (strcmp(opcodeTable[i].opcode, opcode) == 0) {
            return opcodeTable[i].hexcode;
        }
    }
    return NULL;
}

// Function to find symbol address
int getSymbolAddress(char* symbol) {
    for (int i = 0; i < MAX_SYMBOL_TABLE; i++) {
        if (strcmp(symbolTable[i].label, symbol) == 0) {
            return symbolTable[i].address;
        }
    }
    return -1; // Symbol not found
}

// Function to parse Symbol Table
void parseSymbolTable() {
    strcpy(symbolTable[0].label, "ALPHA");
    symbolTable[0].address = 2012;
    
    strcpy(symbolTable[1].label, "FIVE");
    symbolTable[1].address = 2018;
    
    strcpy(symbolTable[2].label, "CHARZ");
    symbolTable[2].address = 2021;
    
    strcpy(symbolTable[3].label, "C1");
    symbolTable[3].address = 2022;
}

// Function to generate object code
void generateObjectCode(char* label, char* opcode, char* operand, int address, FILE* outFile) {
    char objectCode[10] = "";
    
    // Handle directives
    if (strcmp(opcode, "START") == 0) {
        startAddress = address;
        strcpy(progName, label);
        fprintf(outFile, "H^%s^%06X^%06X\n", progName, startAddress, programSize);
        // Write Text record header
        fprintf(outFile, "T^%06X^", startAddress);
        return;
    }
    
    if (strcmp(opcode, "END") == 0) {
        // Close the text record and write end record
        fprintf(outFile, "\nE^%06X\n", startAddress);
        return;
    }
    
    if (strcmp(opcode, "RESW") == 0 || strcmp(opcode, "RESB") == 0) {
        // Skip reservation directives in object code
        return;
    }
    
    if (strcmp(opcode, "WORD") == 0) {
        // Convert decimal to 6-digit hex
        sprintf(objectCode, "%06X", atoi(operand));
    } else if (strcmp(opcode, "BYTE") == 0) {
        if (operand[0] == 'C') {
            // Character constant - convert to hex
            int i = 2; // Skip C'
            while (operand[i] != '\'') {
                char hex[3];
                sprintf(hex, "%02X", operand[i]);
                strcat(objectCode, hex);
                i++;
            }
        } else if (operand[0] == 'X') {
            // Hex constant - copy directly
            int i = 2; // Skip X'
            while (operand[i] != '\'') {
                char hex[2] = {operand[i], '\0'};
                strcat(objectCode, hex);
                i++;
            }
        }
    } else {
        // Regular instruction
        char* opcodeValue = getOpcodeValue(opcode);
        if (opcodeValue != NULL) {
            strcpy(objectCode, opcodeValue);
            
            // Add operand address
            if (strcmp(operand, "") != 0) {
                int operandAddr = getSymbolAddress(operand);
                if (operandAddr != -1) {
                    char addrHex[5];
                    sprintf(addrHex, "%04X", operandAddr);
                    strcat(objectCode, addrHex);
                }
            }
        }
    }
    
    // Write object code to output file
    if (strcmp(objectCode, "") != 0) {
        fprintf(outFile, "^%s", objectCode);
    }
}

// Main function for second pass
void secondPass(FILE* inFile, FILE* outFile) {
    char line[MAX_LINE_LENGTH];
    char address[10], label[20], opcode[10], operand[20];
    int lineCount = 0;
    
    // Parse the Symbol Table
    parseSymbolTable();
    
    // Calculate program size (from last address - start address)
    programSize = 2023 - 2000;
    
    printf("Second Pass of Assembler:\n");
    printf("-------------------------\n");
    
    while (fgets(line, MAX_LINE_LENGTH, inFile) != NULL) {
        // Remove newline character
        line[strcspn(line, "\n")] = 0;
        
        // Skip empty lines
        if (strlen(line) == 0) continue;
        
        // Parse line
        sscanf(line, "%s %s %s %s", address, label, opcode, operand);
        
        // Handle special case for START and END
        if (strcmp(opcode, "START") == 0) {
            // Swap label and opcode for START instruction
            char temp[20];
            strcpy(temp, label);
            strcpy(label, address);
            strcpy(opcode, temp);
            strcpy(operand, label);
            strcpy(address, "");
        } else if (strcmp(label, "**") == 0) {
            // Handle lines with format "address ** opcode operand"
            strcpy(operand, opcode);
            strcpy(opcode, label);
            strcpy(label, "");
        }
        
        // Convert address from string to int
        int addr = strtol(address, NULL, 16);
        
        // Generate object code
        generateObjectCode(label, opcode, operand, addr, outFile);
        
        // Print intermediate and object code for debugging
        printf("Line %d: %s %s %s %s\n", lineCount++, address, label, opcode, operand);
    }
}

int main() {
    FILE *inFile, *outFile;
    
    // Open intermediate code file
    inFile = fopen("intermediate.txt", "w");
    if (inFile == NULL) {
        printf("Could not create intermediate.txt\n");
        return 1;
    }
    
    // Write example intermediate code to file
    fprintf(inFile, "** START 2000\n");
    fprintf(inFile, "2000 ** LDA FIVE\n");
    fprintf(inFile, "2003 ** STA ALPHA\n");
    fprintf(inFile, "2006 ** LDCH CHARZ\n");
    fprintf(inFile, "2009 ** STCH C1\n");
    fprintf(inFile, "2012 ALPHA RESW 2\n");
    fprintf(inFile, "2018 FIVE WORD 5\n");
    fprintf(inFile, "2021 CHARZ BYTE C'Z'\n");
    fprintf(inFile, "2022 C1 RESB 1\n");
    fprintf(inFile, "2023 ** END **\n");
    
    // Close and reopen the file for reading
    fclose(inFile);
    inFile = fopen("intermediate.txt", "r");
    if (inFile == NULL) {
        printf("Could not open intermediate.txt for reading\n");
        return 1;
    }
    
    // Open output file
    outFile = fopen("objectcode.txt", "w");
    if (outFile == NULL) {
        printf("Could not create objectcode.txt\n");
        fclose(inFile);
        return 1;
    }
    
    // Process second pass
    secondPass(inFile, outFile);
    
    // Display object code
    printf("\nGenerated Object Code:\n");
    printf("---------------------\n");
    
    // Close files
    fclose(inFile);
    fclose(outFile);
    
    // Reopen output file to display contents
    outFile = fopen("objectcode.txt", "r");
    if (outFile != NULL) {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), outFile) != NULL) {
            printf("%s", buffer);
        }
        fclose(outFile);
    }
    
    return 0;
}
# Compiler Design Lab Assignments

This repository contains implementations of various compiler design concepts including:
- Lexical Analyzers using Lex/Flex
- Parsers using YACC/Bison
- Custom C implementations for compiler components
- Macro processors and assemblers

## Table of Contents

1. [Lex Program: Even/Odd Integer Identifier](#1-lex-program-evenodd-integer-identifier)
2. [Lex Program: Vowel/Consonant Classifier](#2-lex-program-vowelconsonant-classifier)
3. [Lex Program: Relational Operators Identifier](#3-lex-program-relational-operators-identifier)
4. [Lex Program: File Content Copy](#4-lex-program-file-content-copy)
5. [YACC Calculator for Basic Arithmetic](#5-yacc-calculator-for-basic-arithmetic)
6. [C Program: Lexical Analyzer](#6-c-program-lexical-analyzer)
7. [C Program: Recursive Descent Parser](#7-c-program-recursive-descent-parser)
8. [C Program: Intermediate Code Generator](#8-c-program-intermediate-code-generator)
9. [Two-Pass Macro Processor](#9-two-pass-macro-processor)
10. [Second Pass of a Two-Pass Assembler](#10-second-pass-of-a-two-pass-assembler)

## 1. Lex Program: Even/Odd Integer Identifier

A Lex program that determines whether an input integer is even or odd.

### Usage

```bash
# Create even_odd.l with the provided Lex code
flex even_odd.l
gcc lex.yy.c -o even_odd -lfl
./even_odd
```

The program prompts for integer input and identifies if it's even or odd.

## 2. Lex Program: Vowel/Consonant Classifier

A Lex program that classifies input characters as vowels or consonants.

### Usage

```bash
# Create vowel_consonant.l with the provided Lex code
flex vowel_consonant.l
gcc lex.yy.c -o vowel_consonant -lfl
./vowel_consonant
```

Enter characters when prompted to check if they're vowels or consonants.

## 3. Lex Program: Relational Operators Identifier

A Lex program that identifies relational operators in input expressions.

### Usage

```bash
# Create relational_operators.l with the provided Lex code
flex relational_operators.l
gcc lex.yy.c -o relational_operators -lfl
./relational_operators
```

Type expressions with relational operators (e.g., `a < b` or `x >= y`) to test.

## 4. Lex Program: File Content Copy

A Lex program that reads content from a file and copies it to standard output.

### Setup

Create an input file named `input.txt` with sample content:

```
This is a test file.
It contains multiple lines.
The Lex program will copy this content to standard output.
```

### Usage

```bash
# Create file_copy.l with the provided Lex code
flex file_copy.l
gcc lex.yy.c -o file_copy -lfl
./file_copy
```

The program reads from `input.txt` and outputs the content to the terminal.

## 5. YACC Calculator for Basic Arithmetic

A calculator implementation using Lex and YACC that can perform basic arithmetic operations.

### Usage

```bash
# Create calculator.l and calculator.y with the provided code
bison -d calculator.y
flex calculator.l
gcc lex.yy.c y.tab.c -o calculator -lfl
./calculator
```

Enter arithmetic expressions like `2+3*4` when prompted.

## 6. C Program: Lexical Analyzer

A custom C implementation of a lexical analyzer that identifies tokens in source code.

### Usage

```bash
# Create lexical_analyzer.c with the provided C code
gcc lexical_analyzer.c -o lexical_analyzer
./lexical_analyzer
```

The program analyzes a hard-coded sample. To analyze different code, modify the `sample_code` variable in the source code.

## 7. C Program: Recursive Descent Parser

A recursive descent parser implementation in C for parsing arithmetic expressions.

### Usage

```bash
# Create recursive_descent_parser.c with the provided C code
gcc recursive_descent_parser.c -o parser
./parser
```

When prompted, enter an arithmetic expression like `(3+4)*5`.

## 8. C Program: Intermediate Code Generator

A C program that generates intermediate code for assignment statements.

### Usage

```bash
# Create intermediate_code_generator.c with the provided C code
gcc intermediate_code_generator.c -o icg
./icg
```

Enter assignment statements when prompted:
```
a = b + c;
x = y * z;
```

End input with an empty line (just press Enter).

## 9. Two-Pass Macro Processor

A C implementation of a two-pass macro processor.

### Setup

Create an input file named `macro_input.txt` with the following content:

```
EX1 MACRO &A,&B
LDA &A
STA &B
MEND
SAMPLE START 1000
EX1 N1,N2
N1 RESW 1
N2 RESW 1
END
```

### Usage

```bash
# Create macro_processor.c with the provided C code
gcc macro_processor.c -o macro_processor
./macro_processor
```

The program reads from `macro_input.txt` and generates output files showing the macro expansion.

## 10. Second Pass of a Two-Pass Assembler

A C implementation of the second pass of a two-pass assembler.

### Usage

```bash
# Create second_pass.c with the provided C code
gcc second_pass.c -o second_pass
./second_pass
```

The program creates and processes an intermediate file internally and generates an object code file named `objectcode.txt` with the final output.

## Requirements

To compile and run these programs, you'll need:

- GCC (GNU Compiler Collection)
- Flex (Fast Lexical Analyzer Generator)
- Bison (GNU Parser Generator)
- A Unix-like environment (Linux, macOS, or Windows with WSL)
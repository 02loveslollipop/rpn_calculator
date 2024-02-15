# RPN C calculator
> A simple RPN calculator written in C language.

## Introduction
Reverse Polish Notation (RPN) is a mathematical notation in which every operator follows all of its operands. It does not need any parentheses as long as each operator has a fixed number of operands. To implement this calculator, a Stack data structure is used to store the operands and intermediate results of the calculation. But the user has random access to the stack, so the values to be operated can be modified at any time, or additional values can be inserted at any position. The calculator also supportts file I/O, so the user can input a file with a list of number to be operated. Also the user can save the stack to a file.

## Requirements
- GCC compiler
- lncurses library
- ltinfo library

## Usage
- Compile the program using the following command on the path of the source code:
```bash
gcc -o main main.c -lncurses -ltinfo -lm
```

- Run the program using the following command:
```bash
./main
```

- the `=>` arrow indicates the position where the value will be inserted in the stack. The user can move the arrow using the arrow keys. The user can also insert a value in the stack by pressing Enter. then insert the value and press Enter again. if no value is inserted it will be 0.
to perform an operation, the user can press the operation key. the key for each operation is shown in the bottom of the screen. The user can also save the stack to a file by pressing the `s` key, and load a file by pressing the `l` key. The user can also exit the program by pressing `del` key.

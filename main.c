#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>



//Calculadora notación polaca inversa con stack
float stack[8];

int point = 0; //posicion actual del cursor en el stack

void printScreen(bool using_buffer, char *buffer) {
    //imprime parte superior del tamaño actual de la pantalla
    int i = 0;
    
    printw("==============RPN Calculator==============\n\n");


    if(!using_buffer){
        for (i = 7; i >= 0; i--) {
            if (i == point) {
                printw("=> ");
            } else {
                printw("   ");
            }
            printw("%d: %f\n", i, stack[i]);
        }
    }else{
        for (i = 7; i >= 0; i--) {
            if (i == point) {
                printw("=> ");
                printw("%d: %s\n", i, buffer);
            } else {
                printw("   ");
                printw("%d: %f\n", i, stack[i]);
            }

        } 
    }
    
    printw("\n");
    printw("[+] Sum [*] Mul [^] Pow [s] Sin  [r]  Sqrt [l] load \n");
    printw("[-] Sub [/] Div [c] Cos [t] Tan [del] Exit [w] write\n");
    if (using_buffer) {
        printw("Enter the value and press Enter\n");
    }
    

}

void loadStack(void) {
    echo();
    keypad(stdscr, FALSE);
    nocbreak();
    clear();
    printw("Enter path to file: ");
    char path[128];
    getstr(path);
    FILE *file = fopen(path, "r");
    //each line is a number
    for (int i = 0; i < 8; i++) {
        fscanf(file, "%f", &stack[i]);
    }
    fclose(file);	
    noecho();
    keypad(stdscr, TRUE);
    cbreak();
}

void saveStack(void) {
    echo();
    keypad(stdscr, FALSE);
    nocbreak();
    clear();
    printw("Enter path to file: ");
    char path[128];
    getstr(path);
    FILE *file = fopen(path, "w");
    for (int i = 0; i < 8; i++) {
        fprintf(file, "%f\n", stack[i]);
    }
    fclose(file);
    noecho();
    keypad(stdscr, TRUE);
    cbreak();
}

float pop(void) {
    float value = stack[0];
    for (int i = 0; i < 7; i++) {
        stack[i] = stack[i + 1];
    }
    return value;
}

void push(float value) {
    for (int i = 7; i > 0; i--) {
        stack[i] = stack[i - 1];
    }
    stack[0] = value;
}

void sum(void) {
    push(pop() + pop());
}

void sub(void) {
    float x = pop();
    float y = pop();
    push(y - x);
}

void mult(void) {
    push(pop() * pop());
}

void divs(void) {
    float x = pop();
    float y = pop();
    if (x == 0) {
        push(0);
        printf("Math Error\n");
    }
    push(y / x);
}

void power(void) {
    float x = pop();
    float y = pop();
    push(pow(y, x));
}

void cosine(void) {
    push(cos(pop()));
}

void sine(void) {
    push(sin(pop()));
}

void tangent(void) {
    push(tan(pop()));
}

void square_root(void) {
    float x = pop();
    if (x < 0) {
        push(0);
        printf("Math Error\n");
    }
    push(sqrt(x));
}

int main() {

    bool running = true;
    char buffer[128];

    initscr(); // Inicializar la pantalla
    cbreak(); // Deshabilitar el búfer de entrada
    noecho(); // No mostrar las pulsaciones de teclas
    keypad(stdscr, TRUE); // Habilitar las teclas de función y las teclas de flecha

    int ch;
    printScreen(false,NULL);

    while ((ch = getch()) != KEY_DC) {
        switch (ch) {
            case KEY_UP:
                if (point < 7) {
                    point += 1;
                }
                break;
            case KEY_DOWN:
                if (point > 0) {
                    point -= 1;
                }
                break;
            case '+':
                sum();
                break;
            case '-':
                sub();
                break;
            
            case '*':
                mult();
                break;
            case '/':
                divs();
                break;

            case '^':
                power();
                break;
            case 'c':
                cosine();
                break;
            case 's':
                sine();
                break;
            case 't':
                tangent();
                break;
            case 'r':
                square_root();
                break;

            case 'l':
                loadStack();
                break;
            
            case 'w':
                saveStack();
                break;

            case 10:
                clear();
                printScreen(true,buffer);
                refresh();
                
                while ((ch = getch()) != 10) {
                    if (ch == KEY_BACKSPACE) {
                        if (strlen(buffer) > 0) {
                            memset(buffer, 0, sizeof(buffer));
                        }
                    } else {
                        buffer[strlen(buffer)] = ch;
                    }
                    clear();
                    printScreen(true,buffer);
                    refresh();
                }
                stack[point] = atof(buffer);
                memset(buffer, 0, sizeof(buffer));
                break;
                
        }
        clear();
        printScreen(false,NULL);
        refresh();
    }
    endwin();
    return 0;    

}
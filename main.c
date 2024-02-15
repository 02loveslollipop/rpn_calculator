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
    
    printw("======RPN Calculator======\n\n");

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
    printw("[+] Sum [*] Mul [^] Pow [s] Sin  [r]  Sqrt \n");
    printw("[-] Sub [/] Div [c] Cos [t] Tan [del] Exit\n");
    if (using_buffer) {
        printw("Enter the value and press Enter\n");
    }
    

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
                //TODO: Implementar la operación de suma
                break;
            case '-':
                //TODO: Implementar la operación de resta
                break;
            
            case '*':
                //TODO: Implementar la operación de multiplicación
                break;
            case '/':
                //TODO: Implementar la operación de división
                break;

            case '^':
                //TODO: Implementar la operación de potencia
                break;
            case 'c': //cosine
                //TODO: Implementar la operación de coseno
                break;
            case 's': //sine
                //TODO: Implementar la operación de seno
                break;
            case 't': //tangent
                //TODO: Implementar la operación de tangente
                break;
            case 'r': //square root
                //TODO: Implementar la operación de raíz cuadrada
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
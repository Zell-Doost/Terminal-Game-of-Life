#include <stdio.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>
#include "ruleEnforcement.h"
#include "dataStruct.h"


#define DEFAULT_WIDTH 190
#define DEFAULT_HEIGHT 60

bool handle_input(int* cRow, int* cCol, bool* isGameRun, BitVect* gameState,
        int height, int width)
{
    char letter = '\0';
    letter = getch();

    switch (letter) {
    case 'w':
        if (*cRow > 1)
            (*cRow)--;
        break;
    case 'a':
        if (*cCol > 1)
            (*cCol)--;
        break;
    case 's':
        if (*cRow < height)
            (*cRow)++;
        break;
    case 'd':
        if (*cCol < width)
            (*cCol)++;
        break;
    case 'j':
        break;
    case 'k':
        break;
    case 'l':
        *isGameRun = !(*isGameRun);
        break;
    default:
        return false;
    }
    return true;
}

int main(int argc, char* argv[])
{
    int width = DEFAULT_WIDTH;
    int height = DEFAULT_HEIGHT;
    bool isGameRun = false;
    //char* gameState = malloc(sizeof(char) * width * height + 1);
    BitVect gameState;
    bit_vect_init(&gameState, width * height);
    //memset(gameState, ' ', width * height);
    //gameState[width * height] = '\0';

    //gameState[POS(10, 10)] = '#';
    //gameState[POS(10, 11)] = '#';
    //gameState[POS(10, 12)] = '#';
    //gameState[POS(11, 9)] = '#';
    //gameState[POS(11, 10)] = '#';
    //gameState[POS(11, 11)] = '#';

    //TOAD
    //bit_vect_set(&gameState, POS(10, 10), true);
    //bit_vect_set(&gameState, POS(10, 11), true);
    //bit_vect_set(&gameState, POS(10, 12), true);
    //bit_vect_set(&gameState, POS(11, 9), true);
    //bit_vect_set(&gameState, POS(11, 10), true);
    //bit_vect_set(&gameState, POS(11, 11), true);
    
    //GLIDER
    bit_vect_set(&gameState, POS(2, 3), true);
    bit_vect_set(&gameState, POS(3, 4), true);
    bit_vect_set(&gameState, POS(4, 2), true);
    bit_vect_set(&gameState, POS(4, 3), true);
    bit_vect_set(&gameState, POS(4, 4), true);



    initscr();
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    nodelay(stdscr, true);
    cbreak();
    curs_set(0);
    noecho();

    wmove(stdscr, 0, 0);
    refresh();

    bool isChange = true;

    int cRow = 0;
    int cCol = 0;

    for (;;) {

        if (isChange) {
            clear();
            for (int i = 0; i < height; i++) {
                char line[width + 2];
                move(i, 0);
                //strncpy(line, gameState + (width * i), width);
                for (int j = 0; j < width; j++) {
                    int curPos = i * width + j;
                    if (bit_vect_get(&gameState, curPos))
                        line[j] = '#';
                    else
                        line[j] = ' ';
                }
                line[width] = '\n';
                line[width + 1] = '\0';
                printw("%s", line);
            }
            char cursor = (bit_vect_get(&gameState, POS(cRow, cCol))) ? '\"' : '\'';
            move(cRow, cCol);
            printw("%c", cursor);
            refresh();
            isChange = false;
        }


        isChange = handle_input(&cRow, &cCol, &isGameRun, &gameState, height, width);

        if (isGameRun) {
            next_state(&gameState, width, height);
            isChange = true;
        }


	//usleep(48000);
	usleep(60000);
        //sleep(1);
    }

    bit_vect_free(&gameState);
    endwin();
    return 0;
}

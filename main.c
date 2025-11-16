#include <stdio.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>
#include "ruleEnforcement.h"


#define DEFAULT_WIDTH 100
#define DEFAULT_HEIGHT 100

int main(int argc, char* argv[])
{
    int width = DEFAULT_WIDTH;
    int height = DEFAULT_HEIGHT;
    char* gameState = malloc(sizeof(char) * width * height + 1);
    memset(gameState, ' ', width * height);
    gameState[width * height] = '\0';

    gameState[POS(10, 10)] = '#';
    gameState[POS(10, 11)] = '#';
    gameState[POS(10, 12)] = '#';
    gameState[POS(11, 9)] = '#';
    gameState[POS(11, 10)] = '#';
    gameState[POS(11, 11)] = '#';

    initscr();
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    nodelay(stdscr, true);
    cbreak();
    curs_set(0);

    wmove(stdscr, 0, 0);
    refresh();

    for (;;) {
	clear();

	for (int i = 0; i < height; i++) {
	    char line[width + 2];
	    move(i, 0);
	    strncpy(line, gameState + (width * i), width);
	    line[width] = '\n';
	    line[width + 1] = '\0';
	    printw("%s", line);
	}

	refresh();
        next_state(gameState, width, height);


	//usleep(48000);
	usleep(250000);
        //sleep(1);
    }

    free(gameState);
    endwin();
    return 0;
}

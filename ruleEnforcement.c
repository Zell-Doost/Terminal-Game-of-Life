#include "ruleEnforcement.h"

#include <stdio.h>

#define GRID_CHECK_SIZE 3


void next_state_tile(char* gameState, int width, int height, int row, int col, 
        bool marked[])
{
    int numNeighbours = 0;
    //int curPos = POS(row, col);
    int curPos = row * width + col;
    bool isAlive = (gameState[curPos] != ' ') ? true : false; //check if alive
    for (int i = row - 1; i <= row + 1; i++) {
        if (i < 0 || i >= height)
            continue;
        for (int j = col - 1; j <= col + 1; j++) {
            if (j < 0 || j >= width)
                continue;
            if (i == row && j == col)
                continue;
            //int checkPos = POS(i, j);
            int checkPos = i * width + j;
            if (gameState[checkPos] != ' ') //check if alive, might have to change
                numNeighbours++;

        }
    }
    //fprintf(stderr, "curPos: %d\n", curPos);
    if (isAlive) {
        move(curPos - 40, 30);
        printw("pos %d: %d", curPos, numNeighbours);
        if (numNeighbours < 2 || numNeighbours > 3)
            marked[curPos] = true;
            //gameState[curPos] = ' ';
    } else {
        if (numNeighbours == 3)
            marked[curPos] = true;
            //gameState[curPos] = '#';
    }
}

void next_state(char* gameState, int width, int height)
{
    bool marked[width * height];
    memset(marked, false, width * height);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            next_state_tile(gameState, width, height, i, j, marked);
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int curPos = i * width + j;
            if (marked[curPos]) 
                gameState[curPos] = (gameState[curPos] != ' ') ? ' ' : '#';
        }
    }
}


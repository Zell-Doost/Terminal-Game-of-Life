#pragma once

#include <stdbool.h>
#include <ncurses.h>
#include <string.h>

#define POS(r, c) ((r * width) + c)

void next_state(char* gameState, int width, int height);

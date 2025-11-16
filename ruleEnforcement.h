#pragma once

#include <stdbool.h>
#include <ncurses.h>
#include <string.h>
#include "dataStruct.h"

#define POS(r, c) ((r * width) + c)

void next_state(BitVect* gameState, int width, int height);

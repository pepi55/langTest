#pragma once

#define TETRIS_H

#include <stdbool.h>
#include <SDL2/SDL.h>

bool menu();
bool options();
bool game();
bool quit();

bool (*stateOfGamePtr)();

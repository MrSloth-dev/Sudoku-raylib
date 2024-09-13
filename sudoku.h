#include <raylib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define DEBUG 0
#define SCREEN_HEIGHT 1000
#define SCREEN_WIDTH 1000
#define MARGIN 100
#define LINES RAYWHITE
#define BACKGROUND BLACK

void    DrawBoard(float square_side);

int Possible(int array[9][9], int number, int x, int y);
int Solve(int array[9][9]);

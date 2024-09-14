#ifndef _SUDOKU_H_
#define _SUDOKU_H_
# include <time.h>
# include <raylib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# define EASY 1
# define MEDIUM 2
# define HARD 3
# define EASY_H 42
# define MEDIUM_H 30
# define HARD_H 21
# define SCREEN_HEIGHT 1000
# define SCREEN_WIDTH 1000
# define MARGIN 100
# define LINES RAYWHITE
# define BACKGROUND BLACK

void    DrawBoard(float square_side);

int Possible(int array[9][9], int number, int x, int y);
int Solve(int array[9][9]);
#endif //_SUDOKU_H_

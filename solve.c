#include "sudoku.h"
#include <stdio.h>

static int CheckHorizontally(int array[9][9], int number, int x, int y) {
  for (int xi = 0; xi < 9; xi++)
    if (array[xi][y] == number && xi != x)
      return (0);
  return (1);
}

static int CheckVertically(int array[9][9], int number, int x, int y) {
  for (int yi = 0; yi < 9; yi++)
    if (array[x][yi] == number && yi != y)
      return (0);
  return (1);
}

static int CheckSquare(int array[9][9], int number, int x, int y) {
  int startRow = (x / 3) * 3;
  int startCol = (y / 3) * 3;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if ((startRow + i != x || startCol + j != y) &&
          array[startRow + i][startCol + j] == number) {
        return (0);
      }
    }
  }
  return (1);
}

int Possible(int array[9][9], int number, int x, int y) {
  if (CheckHorizontally(array, number, x, y) &&
      CheckVertically(array, number, x, y) && CheckSquare(array, number, x, y))
    return (1);
  return (0);
}

int Solve(int array[9][9]) {
  for (int yi = 0; yi < 9; yi++)
    for (int xi = 0; xi < 9; xi++)
      if (array[xi][yi] == 0) {
        for (int num = 1; num <= 9; num++) {
          if (Possible(array, num, xi, yi)) {
            array[xi][yi] = num;
            if (Solve(array))
                return (1);
            array[xi][yi] = 0;
          }
        }
          return (0);
      }
  return (1);
}

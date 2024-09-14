#include "sudoku.h"
#include <raylib.h>

void PrintArray(int array[9][9]) {
  float square_side = SCREEN_WIDTH - MARGIN * 2;
  float cell_side = square_side / 9;
  for (int y = 0; y < 9; y++)
    for (int x = 0; x < 9; x++)
      if (array[x][y] > 0 && array[x][y] <= 9) {
        if (Possible(array, array[x][y], x, y))
          DrawText(TextFormat("%d", array[x][y]),
                   MARGIN + cell_side * x + cell_side / 3,
                   MARGIN + cell_side * y + cell_side / 4, cell_side / 2,
                   GREEN);
        else {
          DrawText(TextFormat("%d", array[x][y]),
                   MARGIN + cell_side * x + cell_side / 3,
                   MARGIN + cell_side * y + cell_side / 4, cell_side / 2, RED);
          array[x][y] = 0;
        }
      }
}

int DrawNumber(int array[9][9], int *x, int *y) {
  float square_side = SCREEN_WIDTH - MARGIN * 2;
  int number;
  number = GetKeyPressed();
  if (number >= KEY_ONE && number <= KEY_NINE) {
    number = number - KEY_ZERO;
    if (Possible(array, number, *x, *y))
      array[*x][*y] = number;
    else {
      DrawText(TextFormat("Can't put down %d in that cell", number), 10, 10, 20,
               RED);
      usleep(100000);
      PrintArray(array);
    }
  }
  if (number == KEY_BACKSPACE)
    array[*x][*y] = 0;
  if (number == -1)
    return (1);
  PrintArray(array);
  return (0);
}
void DrawSelection(int *selected_x, int *selected_y) {
  float square_side = SCREEN_WIDTH - MARGIN * 2;
  float cell_side = square_side / 9;
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    if (GetMouseX() < SCREEN_WIDTH - MARGIN && GetMouseY() < SCREEN_HEIGHT - MARGIN) {
      *selected_x = ((GetMouseX() - MARGIN) / cell_side);
      *selected_y = ((GetMouseY() - MARGIN) / cell_side);
    }
  }
  if (IsKeyPressed(KEY_D) && *selected_x < 8)
    *selected_x = *selected_x + 1;
  else if (IsKeyPressed(KEY_A) && *selected_x > 0)
    *selected_x = *selected_x - 1;
  else if (IsKeyPressed(KEY_W) && *selected_y > 0)
    *selected_y = *selected_y - 1;
  else if (IsKeyPressed(KEY_S) && *selected_y < 8)
    *selected_y = *selected_y + 1;
  DrawRectangle(MARGIN + cell_side * (*selected_x),
                MARGIN + cell_side * (*selected_y), cell_side, cell_side,
                ColorAlpha(LIME, 0.7f));
}

void InitBoard(int array[9][9], int max_holes) {
  srand(time(NULL));
  int x = 0;
  int y = 0;
  int holes = 0;

  Solve(array);
  while (holes < max_holes) {
    x = rand() % 9;
    y = rand() % 9;
    if (array[x][y] != 0) {
      array[x][y] = 0;
      holes++;
    }
  }
}

int MainScreen(bool *main, bool *start) {
  int max_holes = 0;
  int font_size = 30;
  DrawText("Welcome to a simple Sudoku", SCREEN_WIDTH / 8, SCREEN_HEIGHT / 8,
           50, RAYWHITE);
  DrawText("by MrSloth-dev", SCREEN_WIDTH - SCREEN_WIDTH / 2.95f, SCREEN_HEIGHT / 8 + 60,
           20, RAYWHITE);
  DrawText("Start", SCREEN_WIDTH / 8, SCREEN_HEIGHT / 8 + 150, 30, RAYWHITE);
  Vector2 StartPos = {(float)SCREEN_WIDTH / 8, (float)SCREEN_HEIGHT / 8 + 150};
  int StartLen = MeasureText("Start", 30);
  Rectangle StartBounds = {StartPos.x, StartPos.y, StartLen, 30};
  if (CheckCollisionPointRec(GetMousePosition(), StartBounds) &&
    IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    *start = true;
  }
  if (*start == true) {
    DrawText("Start", SCREEN_WIDTH / 8, SCREEN_HEIGHT / 8 + 150, 30, ColorAlpha(GRAY, 0.5f));
    DrawText("Choose Dificulty : ", SCREEN_WIDTH / 8, SCREEN_HEIGHT / 8 + 200,
             30, RAYWHITE);


    DrawText("Easy", SCREEN_WIDTH / 8, SCREEN_HEIGHT / 8 + 250, 30, GREEN);
    Vector2 EasyPos = {(float)SCREEN_WIDTH / 8, (float)SCREEN_HEIGHT / 8 + 250};
    int EasyLen = MeasureText("Easy", 30);
    Rectangle EasyBounds = {EasyPos.x, EasyPos.y, EasyLen, 30};

    DrawText("Medium", SCREEN_WIDTH / 8 + 150, SCREEN_HEIGHT / 8 + 250, 30,
             YELLOW);
    Vector2 MediumPos = {(float)SCREEN_WIDTH / 8 + 150,
      (float)SCREEN_HEIGHT / 8 + 250};
    int MediumLen = MeasureText("Medium", 30);
    Rectangle MediumBounds = {MediumPos.x, MediumPos.y, MediumLen, 30};

    DrawText("Hard", SCREEN_WIDTH / 8 + 300, SCREEN_HEIGHT / 8 + 250, 30, RED);
    Vector2 HardPos = {(float)SCREEN_WIDTH / 8 + 300,
      (float)SCREEN_HEIGHT / 8 + 250};
    int HardLen = MeasureText("Hard", 30);
    Rectangle HardBounds = {HardPos.x, HardPos.y, HardLen, 30};

    if (CheckCollisionPointRec(GetMousePosition(), EasyBounds) &&
      IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      max_holes = EASY_H;
      *main = false;
    }
    if (CheckCollisionPointRec(GetMousePosition(), MediumBounds) &&
      IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      max_holes = MEDIUM_H;
      *main = false;
    }
    if (CheckCollisionPointRec(GetMousePosition(), HardBounds) &&
      IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      max_holes = HARD_H;
      *main = false;
    }
  }

  DrawText("Close Window", SCREEN_WIDTH / 8, SCREEN_HEIGHT / 8 + 300, 30,
           RAYWHITE);
  Vector2 ClosePos = {(float)SCREEN_WIDTH / 8, (float)SCREEN_HEIGHT / 8 + 300};
  int CloseLen = MeasureText("Close Window", 30);
  Rectangle CloseBounds = {ClosePos.x, ClosePos.y, CloseLen, 30};

  if (CheckCollisionPointRec(GetMousePosition(), CloseBounds) &&
    IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    exit(0);
  return (max_holes);
}

int main() {
  int array[9][9] = {};
  bool main = true;
  bool start = false;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "A simple Sudoku by MrSloth-dev");
  SetTargetFPS(10);
  int selected_x = 0, selected_y = 0, max_holes = 0;
  float square_side = SCREEN_WIDTH - MARGIN * 2;

  while (!WindowShouldClose()) {
    BeginDrawing();
    if (main) {
      if (max_holes == 0)
        max_holes = MainScreen(&main, &start);
      MainScreen(&main, &start);
      InitBoard(array, max_holes);
    } else {
      ClearBackground(BACKGROUND);
      DrawSelection(&selected_x, &selected_y);
      DrawNumber(array, &selected_x, &selected_y);
      DrawBoard(square_side);
      if (IsKeyPressed(KEY_ENTER))
        Solve(array);
    }
    EndDrawing();
  }
  CloseWindow();
  return 0;
}

void DrawBoard(float square_side) {
  for (int i = 0; i <= 9; i++)
    DrawLine(MARGIN + square_side / 9 * i, MARGIN, MARGIN + square_side / 9 * i,
             SCREEN_HEIGHT - MARGIN, LINES);
  for (int i = 0; i <= 9; i++)
    DrawLine(MARGIN, MARGIN + square_side / 9 * i, SCREEN_WIDTH - MARGIN,
             MARGIN + square_side / 9 * i, LINES);
  for (int i = 1; i < 3; i++)
    DrawLineEx((Vector2){MARGIN + square_side / 3 * i, MARGIN},
               (Vector2){MARGIN + square_side / 3 * i, SCREEN_HEIGHT - MARGIN},
               5, LINES);
  for (int i = 1; i < 3; i++)
    DrawLineEx((Vector2){MARGIN, MARGIN + square_side / 3 * i},
               (Vector2){SCREEN_WIDTH - MARGIN, MARGIN + square_side / 3 * i},
               5, LINES);
  DrawText("Sudoku by MrSloth-dev", SCREEN_WIDTH - 300, 10, 20, RAYWHITE);
}

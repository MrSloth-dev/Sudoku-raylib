#include <raylib.h>
#include "sudoku.h"


int DrawNumber(int array[9][9], int *x, int *y)
{
    float square_side = SCREEN_WIDTH - MARGIN * 2;
    int number;
    number = GetKeyPressed();
    if (number >= KEY_ONE && number <= KEY_NINE) {
        number = number - KEY_ZERO;
        if (Possible(array, number, *x, *y))
            array[*x][*y] = number;
        else
            DrawText("Can't put down that number!", 10, 10, 20, RED);
    }
    if (number == KEY_BACKSPACE)
        array[*x][*y] = 0;
    if (number == -1)
        return (1);
    return (0);
}
void    PrintArray(int array[9][9])
{
    float square_side = SCREEN_WIDTH - MARGIN * 2;
    float cell_side = square_side / 9;
    for (int y = 0; y < 9; y++)
        for (int x = 0; x < 9; x++)
            if (array[x][y] > 0 && array[x][y] <= 9)
            {
                if (Possible(array, array[x][y], x, y))
                    DrawText(TextFormat("%d", array[x][y]), MARGIN + cell_side * x + cell_side / 3, MARGIN + cell_side * y + cell_side / 4 , cell_side / 2, GREEN);
            }
}

void    DrawSelection(int *selected_x, int *selected_y)
{
    float square_side = SCREEN_WIDTH - MARGIN * 2;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        *selected_x = ((GetMouseX() - MARGIN) / (square_side / 9));
        *selected_y = ((GetMouseY() - MARGIN) / (square_side / 9));
    }
    if (IsKeyPressed(KEY_D) && *selected_x < 8)
        *selected_x = *selected_x + 1;
    else if (IsKeyPressed(KEY_A) && *selected_x > 0)
        *selected_x = *selected_x - 1;
    else if (IsKeyPressed(KEY_W) && *selected_y > 0)
        *selected_y = *selected_y - 1;
    else if (IsKeyPressed(KEY_S) && *selected_y < 8)
        *selected_y = *selected_y + 1;
        DrawRectangle(MARGIN + (square_side / 9) * (*selected_x), MARGIN + (square_side / 9) * (*selected_y), (square_side / 9), (square_side / 9), ColorAlpha(LIME, 0.7f));

}

int	main()
{
    int array[9][9] = {};
    for (int y = 0; y < 9; y++)
        for (int x = 0; x < 9; x++)
            array[x][y] = 0;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sudoku");
    SetTargetFPS(10);
    int selected_x = 0, selected_y = 0, number = -1;
    float square_side = SCREEN_WIDTH - MARGIN * 2;

    while (!WindowShouldClose())
    {
        DrawSelection(&selected_x, &selected_y);
        DrawNumber(array, &selected_x, &selected_y);
        BeginDrawing();
        PrintArray(array);
        ClearBackground(BACKGROUND);
        DrawBoard(square_side);
        EndDrawing();
        if (IsKeyPressed(KEY_ENTER))
            Solve(array);
        if (IsKeyPressed(KEY_M) && DEBUG) {
            for (int y = 0; y < 9; y++){
                for (int x = 0; x < 9; x++)
                    printf("%d ", array[x][y]);
                printf("\n");
            }
        printf("\n");
        }
    }
    CloseWindow();
    return 0;
}

void    DrawBoard(float square_side)
{
        DrawRectangleLines(MARGIN, MARGIN, square_side, square_side, LINES);
        for (int i = 1; i < 9; i++)
            DrawLine(MARGIN + square_side / 9 * i, MARGIN, MARGIN + square_side / 9 * i, SCREEN_HEIGHT - MARGIN, LINES);
        for (int i = 1; i < 9; i++)
            DrawLine(MARGIN , MARGIN + square_side / 9 * i, SCREEN_WIDTH - MARGIN, MARGIN + square_side / 9 * i, LINES);
        for (int i = 1; i < 3; i++)
            DrawLineEx((Vector2){MARGIN + square_side / 3 * i, MARGIN}, (Vector2) {MARGIN + square_side / 3 * i, SCREEN_HEIGHT - MARGIN}, 5, LINES);
        for (int i = 1; i < 3; i++)
            DrawLineEx((Vector2){MARGIN, MARGIN + square_side / 3 * i}, (Vector2) {SCREEN_WIDTH - MARGIN, MARGIN + square_side / 3 * i}, 5, LINES);
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>

#include "snake.h"

int main() {

    initGame();

    InitWindow(SCREENW,SCREENH,"Snake");
    SetTargetFPS(30);
    
    while(!WindowShouldClose()){

        BeginDrawing();
            ClearBackground(WHITE);
            drawSnake();
            drawWalls();
            drawFruit(fruit);
        EndDrawing();

        isFruitEaten();
        isSnakeBigger();
        checkDir();
        moveSnake();

        if(IsKeyPressed(KEY_R)){
            initGame();
        }
    }

    CloseWindow();
    
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>

#include "snake.h"

int main() {

    Snake* head = loadSnake();
    Fruit fruit = loadFruit();

    InitWindow(SCREENW,SCREENH,"Snake");
    SetTargetFPS(30);
    
    while(!WindowShouldClose()){

        BeginDrawing();
            ClearBackground(WHITE);
            drawSnake();
            drawWalls();
            drawFruit(fruit);
        EndDrawing();

        if(IsKeyPressed(KEY_P)){
            head -> len += 1;
        }
        if(CheckCollisionRecs(head -> rec,fruit.rec)){
            fruit = loadFruit();
            head -> len += 1;
        }

        isSnakeBigger(head);
        checkDir();
        moveSnake();
    }

    CloseWindow();
    
    return 0;
}

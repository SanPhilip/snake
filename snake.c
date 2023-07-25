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
            drawWalls();
            drawSnake();
            drawFruit(fruit);
        EndDrawing();

        checkDir(head);
        moveSnake();

        if(CheckCollisionRecs(head -> rec,fruit.rec)){
            fruit = loadFruit();
            head -> len += 1;
        }

        isSnakeBigger(head);
    }

    CloseWindow();
    
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>

#include "snake.h"

#define SCREENW 800
#define SCREENH 450

int main() {

    Rectangle winFrame = {0,0,SCREENW,SCREENH};
    Fruit fruit = loadFruit();
    
    InitWindow(SCREENW,SCREENH,"Snake");
    SetTargetFPS(30);
    
    while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(WHITE);
            DrawRectangleLinesEx(winFrame,PIXEL_SIZE,BLACK);
            drawFruit(fruit);
            fruit = loadFruit();
        EndDrawing();
    }

    CloseWindow();
    
    return 0;
}

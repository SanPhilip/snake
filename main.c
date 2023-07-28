#include <stdio.h>
#include <raylib.h>
#include "snake.h"

int main() {

    bool isGameOver = false;
    bool isGamePaused = false;

    Snake head;
    int prevSize = 0;

    Body* bodyPart[54*30];
    int bodyCount = 0;

    Fruit fruit;

    initGame(&head,&prevSize,&fruit,bodyPart,&bodyCount);

    InitWindow(BOARDW,BOARDH,"Snake");
    SetTargetFPS(30);

    while(!WindowShouldClose()){

        BeginDrawing();
            ClearBackground(GRAY);
            drawSnake(head,bodyPart,bodyCount);
            drawFruit(fruit);
        EndDrawing();

        if(!isGameOver && !isGamePaused){
            isFruitEaten(&head,&fruit);
            isSnakeBigger(head,&prevSize,bodyPart,&bodyCount);
            checkDir(&head);
            moveSnake(&head,bodyPart,bodyCount);


            if(checkCollision(head,bodyPart,bodyCount)){
                isGameOver = true;
            }
        }

        if(IsKeyPressed(KEY_P)){
            if(isGamePaused){
                isGamePaused = false;
            } else {
                isGamePaused = true;
            }
        }

        if(IsKeyPressed(KEY_R)){
            initGame(&head,&prevSize,&fruit,bodyPart,&bodyCount);
            isGameOver = false;
            isGamePaused = false;
        }
    }

    CloseWindow();

    return 0;
}

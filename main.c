#include <stdio.h>
#include <raylib.h>
#include "snake.h"

int main() {

    Snake head;
    int prevSize = 0;

    Body* bodyPart[79*43];
    int bodyCount = 0;

    Fruit fruit;

    initGame(&head,&prevSize,&fruit,bodyPart,&bodyCount);

    InitWindow(BOARDW,BOARDH,"Snake");
    SetTargetFPS(30);

    while(!WindowShouldClose()){

        BeginDrawing();
            ClearBackground(GRAY);
            drawSnake(head,bodyPart,bodyCount);
            /* drawWalls(); */
            drawFruit(fruit);
        EndDrawing();

        isFruitEaten(&head,&fruit);
        isSnakeBigger(head,&prevSize,bodyPart,&bodyCount);
        checkDir(&head);
        moveSnake(&head,bodyPart,bodyCount);

        if(IsKeyPressed(KEY_R)){
            initGame(&head,&prevSize,&fruit,bodyPart,&bodyCount);
        }
    }

    CloseWindow();

    return 0;
}

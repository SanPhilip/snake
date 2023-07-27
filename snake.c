#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>
#include "snake.h"

void testLib() {
    printf("snake.h");
}

int randNum(int min, int max) {
    srand(time(NULL));
    return rand() % (max + 1 - min) + min;
}


void loadSnake(Snake* head) {

    int x = (BOARDW - PIXEL_SIZE)/20*PIXEL_SIZE;
    int y = (BOARDH - PIXEL_SIZE)/20*PIXEL_SIZE;

    head->rec = (Rectangle){.x = x, .y = y,
                            .width = PIXEL_SIZE,
                            .height = PIXEL_SIZE};
    head->len = 0;
    head->dir = 0;
}

void drawSnake(Snake head, Body* bodyPart[], int bodyCount) {

    for(int i = 0; i < bodyCount; i++){
        DrawRectangleRec(bodyPart[i]->rec,GREEN);
    }
    DrawRectangleRec(head.rec,YELLOW);
}

void checkDir(Snake* head) {

    int key = GetKeyPressed();
    if(key == KEY_UP || key == KEY_RIGHT || key == KEY_DOWN || key == KEY_LEFT){
        head->dir = key;
    }
}

void moveSnake(Snake* head, Body* bodyPart[], int bodyCount) {

    Vector2 toMove = {head->rec.x, head->rec.y};
    Vector2 prevPos;

    for(int i = 0; i < bodyCount; i++){
        prevPos = (Vector2){.x = bodyPart[i]->rec.x,
                            .y = bodyPart[i]->rec.y};
        bodyPart[i]->rec.x = toMove.x;
        bodyPart[i]->rec.y = toMove.y;
        toMove = prevPos;
    }
    
    switch(head->dir) {
    case KEY_UP: head->rec.y -= PIXEL_SIZE;
        break;
    case KEY_RIGHT: head->rec.x += PIXEL_SIZE;
        break;
    case KEY_DOWN: head->rec.y += PIXEL_SIZE;
        break;
    case KEY_LEFT: head->rec.x -= PIXEL_SIZE;
        break;
    }
}

void isSnakeBigger(Snake head, int* prevSize, Body* bodyPart[], int* bodyCount) {

    if(head.len > *prevSize){
        *prevSize = head.len;

        Body* body = (Body*)malloc(sizeof(Body));
        *body = (Body){{0,0,PIXEL_SIZE,PIXEL_SIZE}};

        bodyPart[*bodyCount] = body;
        ++(*bodyCount);
    }
}


void loadFruit(Fruit* fruit) {

    int x = randNum(1,79) * PIXEL_SIZE;
    int y = randNum(1,43) * PIXEL_SIZE;
    *fruit = (Fruit){.rec = {x,y,PIXEL_SIZE,PIXEL_SIZE}};
}

void drawFruit(Fruit fruit) {
    DrawRectangleRec(fruit.rec,RED);
}

void isFruitEaten(Snake* head, Fruit* fruit) {

    if(CheckCollisionRecs(head->rec,fruit->rec)){
        loadFruit(fruit);
        head->len += 1;
    }
}


bool checkCollision(Snake head, Body* bodyPart[], int bodyCount) {

    for(int i = 0; i < bodyCount; i++){
        if(CheckCollisionRecs(head.rec,bodyPart[i]->rec)){
            return true;
        }
    }
    return false;
}


void initGame(Snake* head, int* prevSize, Fruit* fruit, Body* bodyPart[], int* bodyCount) {

    for(int i = 0; i < *bodyCount; i++){
        free(bodyPart[i]);
    }

    *bodyCount = 0;
    *prevSize = 0;
    loadSnake(head);
    loadFruit(fruit);
}

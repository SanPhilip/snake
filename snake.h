#include <stdlib.h>
#include <time.h>
#include <raylib.h>

#define SCREENW 810
#define SCREENH 450
#define PIXEL_SIZE 10

#define UP 265
#define RIGHT 262
#define DOWN 264
#define LEFT 263

int randNum(int min, int max) {
    srand(time(NULL));
    return rand() % (max + 1 - min) + min;
}

typedef struct Snake {
    Rectangle rec;
    int len;
    int dir;
} Snake;

Snake* snake[79*43];
int bodyCount = 0;
int prevSize = 0;

Snake* loadSnake() {
    int x = (SCREENW - 10)/20*PIXEL_SIZE;
    int y = (SCREENH - 10)/20*PIXEL_SIZE;

    Snake* head = (Snake*)malloc(sizeof(Snake));
    head -> rec = (Rectangle){.x = x, .y = y,
                              .width = PIXEL_SIZE, .height = PIXEL_SIZE};
    head -> len = 0;
    head -> dir = 0;
    snake[bodyCount] = head;
    ++bodyCount;
    return head;
}

void checkDir(Snake* snake) {
    int key = GetKeyPressed();
    switch(key) {
        case UP: snake -> dir = UP;
            break;
        case RIGHT: snake -> dir = RIGHT;
            break;
        case DOWN: snake -> dir = DOWN;
            break;
        case LEFT: snake -> dir = LEFT;
            break;
    }
}

void moveSnake() {
    for(int i = 0; i < bodyCount; i++){
        switch(snake[i] -> dir) {
        case UP: snake[i] -> rec.y -= PIXEL_SIZE;
            break;
        case RIGHT: snake[i] -> rec.x += PIXEL_SIZE;
            break;
        case DOWN: snake[i] -> rec.y += PIXEL_SIZE;
            break;
        case LEFT: snake[i] -> rec.x -= PIXEL_SIZE;
            break;
        }
    }
}

typedef struct Fruit {
    Rectangle rec;
} Fruit;

Fruit loadFruit() {
    int x = randNum(1,78) * PIXEL_SIZE;
    int y = randNum(1,43) * PIXEL_SIZE;

    Fruit fruit = {{x,y,PIXEL_SIZE,PIXEL_SIZE}};
    return fruit;
}


void drawFruit(Fruit fruit) {
    DrawRectangleRec(fruit.rec,RED);
}

void drawSnake() {
    Snake bodyPart;
    for(int i = 0; i < bodyCount; i++){
        bodyPart = *snake[i];
        DrawRectangleRec(bodyPart.rec,GREEN);
    }
}

void drawWalls() {
    DrawRectangle(0,0,SCREENW,PIXEL_SIZE,BLACK);
    DrawRectangle(0,SCREENH - PIXEL_SIZE,SCREENW,PIXEL_SIZE,BLACK);
    DrawRectangle(0,0,PIXEL_SIZE,SCREENH,BLACK);
    DrawRectangle(SCREENW - PIXEL_SIZE,0,PIXEL_SIZE,SCREENH,BLACK);
}

void isSnakeBigger(Snake* head) {
    if(head -> len > prevSize){
        prevSize = head -> len;
        Snake tail = *snake[bodyCount-1];
        Rectangle bodyPos;
        switch(tail.dir){
        case UP:
            bodyPos.y = tail.rec.y + PIXEL_SIZE;
            bodyPos.x = tail.rec.x;
            break;
        case RIGHT:
            bodyPos.x = tail.rec.x - PIXEL_SIZE;
            bodyPos.y = tail.rec.y;
            break;
        case DOWN:
            bodyPos.y = tail.rec.y - PIXEL_SIZE;
            bodyPos.x = tail.rec.x;
            break;
        case LEFT:
            bodyPos.x = tail.rec.x + PIXEL_SIZE;
            bodyPos.y = tail.rec.y;
            break;
        }

        bodyPos.width = PIXEL_SIZE;
        bodyPos.height = PIXEL_SIZE;

        Snake* body = (Snake*)malloc(sizeof(Snake));
        *body = (Snake){.rec = bodyPos, .len = 0, .dir = tail.dir};

        snake[bodyCount] = body;
        ++bodyCount;
    }
}

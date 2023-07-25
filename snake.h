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

void checkDir() {
    int key = GetKeyPressed();
    if(key == UP || key == RIGHT || key == DOWN || key == LEFT){
        snake[0] -> dir = key;
    }
}

void moveSnake() {
    Vector2 toMove = {snake[0] -> rec.x, snake[0] -> rec.y};
    Vector2 prevPos;
    for(int i = 1; i < bodyCount; i++){
        prevPos = (Vector2){.x = snake[i] -> rec.x, .y = snake[i] -> rec.y};
        snake[i] -> rec = (Rectangle){.x = toMove.x, .y = toMove.y,
                                      .width = PIXEL_SIZE, .height = PIXEL_SIZE};
        toMove = prevPos;
    }
    switch(snake[0] -> dir) {
    case UP: snake[0] -> rec.y -= PIXEL_SIZE;
        break;
    case RIGHT: snake[0] -> rec.x += PIXEL_SIZE;
        break;
    case DOWN: snake[0] -> rec.y += PIXEL_SIZE;
        break;
    case LEFT: snake[0] -> rec.x -= PIXEL_SIZE;
        break;
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
        Rectangle bodyPos = {0,0,PIXEL_SIZE,PIXEL_SIZE};

        Snake* body = (Snake*)malloc(sizeof(Snake));
        *body = (Snake){.rec = bodyPos, .len = 0, .dir = 0};

        snake[bodyCount] = body;
        ++bodyCount;
    }
}

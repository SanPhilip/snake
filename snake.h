#include <stdlib.h>
#include <time.h>
#include <raylib.h>

#define PIXEL_SIZE 10

int randNum(int min, int max){
    srand(time(NULL));
    return rand() % (max + 1 - min) + min;
}

typedef struct Snake {
    int x;
    int y;
    int len;
} Snake;

typedef struct Fruit {
    int x;
    int y;
} Fruit;

Fruit loadFruit(){
    int x = randNum(1,78) * PIXEL_SIZE;
    int y = randNum(1,43) * PIXEL_SIZE;

    Fruit fruit = {x,y};
    return fruit;
}

void drawFruit(Fruit fruit){
    Vector2 position = {fruit.x,fruit.y};
    Vector2 size = {PIXEL_SIZE,PIXEL_SIZE};

    DrawRectangleV(position,size,RED);
}

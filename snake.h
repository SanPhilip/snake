#ifndef SNAKE_H_
#define SNAKE_H_

#include <raylib.h>

#define BOARDW 810
#define BOARDH 450
#define PIXEL_SIZE 10

typedef struct Snake {
    Rectangle rec;
    int len;
    int dir;
} Snake;

typedef struct Body {
    Rectangle rec;
} Body;


typedef struct Fruit {
    Rectangle rec;
} Fruit;

void testLib();

int randNum(int min, int max);

void loadSnake(Snake* head);
void drawSnake(Snake head, Body* bodyPart[], int bodyCount);
void checkDir(Snake* head);
void moveSnake(Snake* head, Body* bodyPart[], int bodyCount);
void isSnakeBigger(Snake head, int* prevSize, Body* bodyPart[], int* bodyCount);

void loadFruit(Fruit* fruit);
void drawFruit(Fruit fruit);
void isFruitEaten(Snake* head, Fruit* fruit);

void initGame(Snake* head, int* prevSize, Fruit* fruit, Body* bodyPart[], int* bodyCount);

#endif

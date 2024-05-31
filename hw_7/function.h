#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_X 30
#define MAX_Y 15
#define MAX_FOOD_SIZE 3
#define Delay 50
#define DEBUG fprintf(stderr, "debug in %d line\n", __LINE__)

enum
{
    UP = 1,
    LEFT,
    DOWN,
    RIGHT
};

typedef struct tail_t
{
    int x;
    int y;
} tail_t;

typedef struct snake_t
{
    int lvlSnake;
    double speedSnake;
    int x;
    int y;
    int direction;
    char headSymbol;
    char tailSymbol;
    struct tail_t *tail;
    size_t tsize;
} snake_t;

typedef struct food
{
    int x;
    int y;
    time_t put_time;
    char foodSymbol;
    uint8_t enable;
} food[MAX_FOOD_SIZE];

struct snake_t initSnake(int x, int y, size_t tsize, char headSymbol, char tailSymbol);

_Bool haveEat(struct snake_t snake, struct food f[]);

snake_t movementLogic(snake_t snake, struct food *food[]);

int movement(snake_t snake);

void input(snake_t *snake, snake_t *snake2);

int distance(const snake_t snake, const struct food food);

void generateSnakeDirection(snake_t *snake, struct food food[]);

void initFood(struct food f[], size_t size, char foodSymbol);

void createFood(struct food f[], size_t size);

void printSnake(snake_t snake[], struct food f[]);

void addTail(struct snake_t *snake, struct food food[]);

void printGameOver(int gameOver);

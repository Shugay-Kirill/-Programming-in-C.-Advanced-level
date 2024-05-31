#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdint.h>
#include "function.h"

// snake initialization
struct snake_t initSnake(int x, int y, size_t tsize, char headSymbol, char tailSymbol)
{
    struct snake_t snake;
    snake.x = x;
    snake.y = y;
    snake.headSymbol = headSymbol;
    snake.tailSymbol = tailSymbol;
    snake.tsize = tsize;
    snake.lvlSnake = 1;
    snake.speedSnake = Delay;
    snake.direction = LEFT;
    snake.tail = (tail_t *)malloc(sizeof(tail_t) * 100);
    for (int i = 0; i < tsize; i++)
    {
        snake.tail[i].x = x + i + 1;
        snake.tail[i].y = y;
    }
    return snake;
}

// food initialization
void initFood(struct food f[], size_t size, char foodSymbol)
{

    struct food init = {0, 0, 0, 0, 1};
    for (int i = 0; i < size; i++)
    {
        f[i] = init;
        f[i].foodSymbol = foodSymbol;
        f[i].x = rand() % (MAX_X - 2) + 1;
        f[i].y = rand() % (MAX_Y - 2) + 1;
    }
}

// create food
void createFood(struct food f[], size_t size/*, snake_t snake[]*/)
{
    for (int i = 0; i < size; i++)
    {
        if (f[i].enable == 0)
        {
            f[i].x = rand() % (MAX_X - 2) + 1;
            f[i].y = rand() % (MAX_Y - 2) + 1;
            f[i].enable = 1;
        }
    }
}

// binge eating
void addTail(struct snake_t *snake, struct food food[])
{
    for (int i = 0; i < MAX_FOOD_SIZE; i++)
    {
        if ((snake->x == food[i].x) && (snake->y == food[i].y))
        {
            snake->tsize++;
            snake->lvlSnake++;
            // snake->speedSnake = (snake->speedSnake > 100) ? (snake->speedSnake - Delay / 2) : (snake->speedSnake = 100);
            snake->tail[snake->tsize - 1].x = snake->tail[snake->tsize - 2].x + (snake->direction == LEFT) - (snake->direction == RIGHT);
            snake->tail[snake->tsize - 1].y = snake->tail[snake->tsize - 2].y + (snake->direction == UP) - (snake->direction == DOWN);
        }
    }
}
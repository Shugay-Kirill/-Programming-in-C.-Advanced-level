#include "function.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdint.h>

int distance(const snake_t snake, const struct food food)
{
    return (abs(snake.x - food.x) + abs(snake.y - food.y));
}

void generateSnakeDirection(snake_t *snake, struct food food[])
{
    int pointer = 0;
    _Bool snakeLeft = 1;
    _Bool snakeUP = 1;
    _Bool snakeDOWN = 1;
    _Bool snakeRIGHT = 1;

    // prohibition on reversing
    if (snake->direction == UP)
        snakeDOWN = 0;
    else if (snake->direction == LEFT)
        snakeRIGHT = 0;
    else if (snake->direction == DOWN)
        snakeUP = 0;
    else if (snake->direction == RIGHT)
        snakeLeft = 0;

    if (snake->y - 1 == 0)
        snakeUP = 0;
    else if (snake->x - 1 == 0)
        snakeLeft = 0;
    else if (snake->y + 1 == MAX_Y)
        snakeDOWN = 0;
    else if (snake->x + 1 == MAX_X)
        snakeRIGHT = 0;

    // forbid movement if there's a body around
    for (int i = 0; i < snake->tsize; i++)
    {
        if (((snake->x + snakeRIGHT) == snake->tail[i].x) && (snake->y == snake->tail[i].y))
            snakeRIGHT = 0;
        else if (((snake->x - snakeLeft) == snake->tail[i].x) && (snake->y == snake->tail[i].y))
            snakeLeft = 0;
        else if (((snake->y + snakeDOWN) == snake->tail[i].y) && (snake->x == snake->tail[i].x))
            snakeDOWN = 0;
        else if (((snake->y - snakeUP) == snake->tail[i].y) && (snake->x == snake->tail[i].x))
            snakeUP = 0;
    }

    // minimum eating distance
    for (int i = 0; i < MAX_FOOD_SIZE; i++)
        pointer = (distance(*snake, food[i]) < distance(*snake, food[pointer])) ? i : pointer;

    // minimum distance travel
    if ((snake->y != food[pointer].y) || (snake->x != food[pointer].x))
    {
        if ((food[pointer].y > snake->y))
            snake->direction = DOWN;
        else if ((food[pointer].y < snake->y))
            snake->direction = UP;
        else if ((food[pointer].x > snake->x))
            snake->direction = RIGHT;
        else if ((food[pointer].x < snake->x))
            snake->direction = LEFT;
    }

    // check for possible and prohibited directions of travel
    if (snake->direction == UP && !snakeUP)
    {
        if (snakeLeft)
            snake->direction = LEFT;
        else if (snakeDOWN)
            snake->direction = DOWN;
        else if (snakeRIGHT)
            snake->direction = RIGHT;
    }
    if (snake->direction == LEFT && !snakeLeft)
    {
        if (snakeUP)
            snake->direction = UP;
        else if (snakeDOWN)
            snake->direction = DOWN;
        else if (snakeRIGHT)
            snake->direction = RIGHT;
    }
    if (snake->direction == DOWN && !snakeDOWN)
    {
        if (snakeUP)
            snake->direction = UP;
        else if (snakeLeft)
            snake->direction = LEFT;
        else if (snakeRIGHT)
            snake->direction = RIGHT;
    }
    if (snake->direction == RIGHT && !snakeRIGHT)
    {
        if (snakeUP)
            snake->direction = UP;
        else if (snakeLeft)
            snake->direction = LEFT;
        else if (snakeDOWN)
            snake->direction = DOWN;
    }
}
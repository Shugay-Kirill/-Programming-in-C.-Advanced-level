#include "function.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdint.h>

extern int gameOver;

// Eating test
_Bool haveEat(struct snake_t snake, struct food f[])
{
    for (int i = 0; i < MAX_FOOD_SIZE; i++)
        if (f[i].enable && snake.x == f[i].x && snake.y == f[i].y)
        {
            f[i].enable = 0;
            return 1;
        }
    return 0;
}

//movement behavior
snake_t movementLogic(snake_t snake, struct food *food[])
{
    for (int i = snake.tsize - 1; i > 0; i--)
    {
        snake.tail[i] = snake.tail[i - 1];
    }
    snake.tail[0].x = snake.x;
    snake.tail[0].y = snake.y;
    snake.x += (snake.direction == RIGHT) - (snake.direction == LEFT);
    snake.y += (snake.direction == DOWN) - (snake.direction == UP);

    if (snake.x == MAX_X || snake.x < 0 || snake.y == MAX_Y || snake.y < 0)
        gameOver = 2;

    for (int i = 1; i < snake.tsize; i++)
    {
        if (snake.x == snake.tail[i].x && snake.y == snake.tail[i].y)
        {
            gameOver = 1;
        }
    }
    if (haveEat(snake, food))
    {
        addTail(&snake, food);
        createFood(food, MAX_FOOD_SIZE);
    }
    return snake;
}

//dispatcher-guided movement 
int movement(snake_t snake)
{
    if (_kbhit())
    {
        switch (tolower(getch()))
        {
        case 'w':
            if (snake.direction != DOWN)
                return UP;
            break;
        case 'a':
            if (snake.direction != RIGHT)
                return LEFT;
            break;
        case 's':
            if (snake.direction != UP)
                return DOWN;
            break;
        case 'd':
            if (snake.direction != LEFT)
                return RIGHT;
            break;
        case 'p':
            do
            {
                printf("Pause: to continue, press P\n");
            } while (tolower(getch()) != 'p');
            break;
        }
    }
    return snake.direction;
}

//movement under the direction of two dispatchers 
void input(snake_t *snake, snake_t *snake2)
{
    if (_kbhit())
    {
        switch (tolower(getch()))
        {
        case 'w':
            if (snake->direction != DOWN)
                snake->direction = UP;
            break;
        case 'a':
            if (snake->direction != RIGHT)
                snake->direction = LEFT;
            break;
        case 's':
            if (snake->direction != UP)
                snake->direction = DOWN;
            break;
        case 'd':
            if (snake->direction != LEFT)
                snake->direction = RIGHT;
            break;
        case 'i':
            if (snake2->direction != DOWN)
                snake2->direction = UP;
            break;
        case 'k':
            if (snake2->direction != UP)
                snake2->direction = DOWN;
            break;
        case 'j':
            if (snake2->direction != RIGHT)
                snake2->direction = LEFT;
            break;
        case 'l':
            if (snake2->direction != LEFT)
                snake2->direction = RIGHT;
            break;
        case 'p':
            do
            {
                printf("Pause: to continue, press P\n");
            } while (tolower(getch()) != 'p');
            break;
        }
    }
}
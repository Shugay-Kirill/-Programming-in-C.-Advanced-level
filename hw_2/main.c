#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_X 30
#define MAX_Y 15
int gameOver = 0;

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
    int x;
    int y;
    int direction;
    struct tail_t *tail;
    size_t tsize;
} snake_t;

struct snake_t initSnake(int x, int y, size_t tsize)
{
    struct snake_t snake;
    snake.x = x;
    snake.y = y;
    snake.tsize = tsize;
    snake.direction = LEFT;
    snake.tail = (tail_t *)malloc(sizeof(tail_t) * 100);
    for (int i = 0; i < tsize; i++)
    {
        snake.tail[i].x = x + i + 1;
        snake.tail[i].y = y;
    }
    return snake;
}

void printSnake(struct snake_t snake)
{
    char matrix[MAX_X][MAX_Y];
    for (int i = 0; i < MAX_X; i++)
    {
        for (int j = 0; j < MAX_Y; j++)
        {
            matrix[i][j] = ' ';
            //game boundaries
            // if (i == MAX_X-1 || j == MAX_Y-1 || i == 0 || j == 0)
            // {
            //     matrix[i][j] = '#';
            // }
        }
    }

    matrix[snake.x][snake.y] = '@';
    for (int i = 0; i < snake.tsize; i++)
    {
        matrix[snake.tail[i].x][snake.tail[i].y] = '*';
    }

    for (int j = 0; j < MAX_Y; j++)
    {
        for (int i = 0; i < MAX_X; i++)
        {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
    sleep(1);
    system("cls");
}

snake_t movementLogic(snake_t snake)
{
    for (int i = snake.tsize - 1; i > 0; i--)
    {
        snake.tail[i] = snake.tail[i-1];
    }
    snake.tail[0].x = snake.x;
    snake.tail[0].y = snake.y;
    snake.x += (snake.direction == RIGHT) - (snake.direction == LEFT);
    snake.y += (snake.direction == DOWN) - (snake.direction == UP);

    for (int i = 1; i < snake.tsize; i++)
    {
        if (snake.x == snake.tail[i].x && snake.y == snake.tail[i].y)
        {
            gameOver = 1;
        }
    }
    return snake;
}

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
        }
    }
    return snake.direction;
}

int main()
{
    struct snake_t snake = initSnake(10, 5, 4);
    printSnake(snake);
    while (!gameOver)
    {
        snake.direction = movement(snake);
        snake = movementLogic(snake);
        printSnake(snake);
    }
    printf("Game over");
    printSnake(snake);
    return 0;
}
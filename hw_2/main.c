#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_X 30
#define MAX_Y 15
#define MAX_FOOD_SIZE 2
#define Delay 100
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
    int lvlSnake;
    double speedSnake;
    int x;
    int y;
    int direction;
    struct tail_t *tail;
    size_t tsize;
} snake_t;

struct food
{
    int x;
    int y;
    time_t put_time;
    char point;
    uint8_t enable;
} food[MAX_FOOD_SIZE];

struct snake_t initSnake(int x, int y, size_t tsize)
{
    struct snake_t snake;
    snake.x = x;
    snake.y = y;
    snake.tsize = tsize;
    snake.lvlSnake = 1;
    snake.speedSnake = 1000;
    snake.direction = LEFT;
    snake.tail = (tail_t *)malloc(sizeof(tail_t) * 100);
    for (int i = 0; i < tsize; i++)
    {
        snake.tail[i].x = x + i + 1;
        snake.tail[i].y = y;
    }
    return snake;
}

void initFood(struct food f[], size_t size)
{
    struct food init = {0, 0, 0, '*', 1};
    for (int i = 0; i < size; i++)
    {
        f[i] = init;
        f[i].x = rand() % MAX_X;
        f[i].y = rand() % MAX_Y;
    }
}

void createFood(struct food f[], size_t size, struct snake_t snake)
{
    for (int i = 0; i < size; i++)
    {
        if (f[i].enable == 0)
        {
            f[i].x = rand() % MAX_X;
            f[i].y = rand() % MAX_Y;
            f[i].enable = 1;
        }
        while (1)
        {
            if (f[i].x == snake.x && f[i].y == snake.y)
            {
                f[i].x = rand() % MAX_X;
                f[i].y = rand() % MAX_Y;
            }
            else if (1)
            {
                for (int j = 0; j < snake.tsize; j++)
                {
                    if (f[i].x == snake.tail[j].x && f[i].y == snake.tail[j].y)
                    {
                        f[i].x = rand() % MAX_X;
                        f[i].y = rand() % MAX_Y;
                        break;
                    }
                }
                break;
            }
        }
    }
}

void printSnake(struct snake_t snake, struct food f[])
{
    char matrix[MAX_X][MAX_Y];
    for (int i = 0; i < MAX_X; i++)
    {
        for (int j = 0; j < MAX_Y; j++)
        {
            matrix[i][j] = ' ';
            // game boundaries
            //  if (i == MAX_X-1 || j == MAX_Y-1 || i == 0 || j == 0)
            //  {
            //      matrix[i][j] = '#';
            //  }
        }
    }
    matrix[snake.x][snake.y] = '@';
    for (int i = 0; i < snake.tsize; i++)
    {
        matrix[snake.tail[i].x][snake.tail[i].y] = 'o';
    }
    for (int i = 0; i < MAX_FOOD_SIZE; i++)
    {
        matrix[f[i].x][f[i].y] = '*';
    }
    for (int j = 0; j < MAX_Y; j++)
    {
        for (int i = 0; i < MAX_X; i++)
        {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
    printf("lvl Snake = %d\n", snake.lvlSnake);
    _sleep(snake.speedSnake);
    system("cls");
}

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

snake_t addTail(struct snake_t snake)
{
    snake.tsize++;
    snake.lvlSnake++;
    snake.speedSnake = (snake.speedSnake - Delay) * 0.9;
    snake.tail[snake.tsize - 1].x = snake.tail[snake.tsize - 2].x + (snake.direction == LEFT) - (snake.direction == RIGHT);
    snake.tail[snake.tsize - 1].y = snake.tail[snake.tsize - 2].y + (snake.direction == UP) - (snake.direction == DOWN);
    return snake;
}

snake_t movementLogic(snake_t snake)
{

    for (int i = snake.tsize - 1; i > 0; i--)
    {
        snake.tail[i] = snake.tail[i - 1];
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

int main()
{
    struct snake_t snake = initSnake(10, 5, 4);
    struct food food[MAX_FOOD_SIZE];
    initFood(food, MAX_FOOD_SIZE);
    createFood(food, MAX_FOOD_SIZE, snake);
    printSnake(snake, food);
    while (!gameOver)
    {
        snake.direction = movement(snake);
        snake = movementLogic(snake);
        if (haveEat(snake, food))
        {
            snake = addTail(snake);
            createFood(food, MAX_FOOD_SIZE, snake);
        }
        printSnake(snake, food);
    }
    printf("Game over\nlvlSnake = %d", snake.lvlSnake);
    return 0;
}
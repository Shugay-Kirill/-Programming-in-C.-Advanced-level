#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdint.h>
#include <conio.h>

#define MAX_X 30
#define MAX_Y 15
#define MAX_FOOD_SIZE 3
#define Delay 100
#define DEBUG fprintf(stderr, "debug in %d line\n", __LINE__)

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
    char headSymbol;
    char tailSymbol;
    struct tail_t *tail;
    size_t tsize;
} snake_t;

struct food
{
    int x;
    int y;
    time_t put_time;
    char foodSymbol;
    uint8_t enable;
} food[MAX_FOOD_SIZE];

struct snake_t initSnake(int x, int y, size_t tsize, char headSymbol, char tailSymbol)
{
    struct snake_t snake;
    snake.x = x;
    snake.y = y;
    snake.headSymbol = headSymbol;
    snake.tailSymbol = tailSymbol;
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

void initFood(struct food f[], size_t size, char foodSymbol)
{

    struct food init = {0, 0, 0, 0, 1};
    for (int i = 0; i < size; i++)
    {
        f[i] = init;
        f[i].foodSymbol = foodSymbol;
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

void printSnake(struct snake_t snake, struct snake_t snake2, struct food f[])
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
    matrix[snake.x][snake.y] = snake.headSymbol;
    matrix[snake2.x][snake2.y] = snake2.headSymbol;
    for (int i = 0; i < snake.tsize; i++)
    {
        matrix[snake.tail[i].x][snake.tail[i].y] = snake.tailSymbol;
    }
    for (int i = 0; i < snake2.tsize; ++i)
    {
        matrix[snake2.tail[i].x][snake2.tail[i].y] = snake2.tailSymbol;
    }
    for (int i = 0; i < MAX_FOOD_SIZE; i++)
    {
        matrix[f[i].x][f[i].y] = f[i].foodSymbol;
    }
    for (int j = 0; j < MAX_Y; j++)
    {
        for (int i = 0; i < MAX_X; i++)
        {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}

void addTail(struct snake_t *snake, struct food food[])
{
    for (int i = 0; i < MAX_FOOD_SIZE; i++)
    {
        if ((snake->x == food[i].x) && (snake->y == food[i].y))
        {
            snake->tsize++;
            snake->lvlSnake++;
            snake->speedSnake = (snake->speedSnake > 100) ? (snake->speedSnake - Delay / 2) : (snake->speedSnake = 100);
            snake->tail[snake->tsize - 1].x = snake->tail[snake->tsize - 2].x + (snake->direction == LEFT) - (snake->direction == RIGHT);
            snake->tail[snake->tsize - 1].y = snake->tail[snake->tsize - 2].y + (snake->direction == UP) - (snake->direction == DOWN);
        }
    }
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
    if (snake.x == MAX_X)
        snake.x = 0;
    else if (snake.x < 0)
        snake.x = MAX_X - 1;
    else if (snake.y == MAX_Y)
        snake.y = 0;
    else if (snake.y < 0)
        snake.y = MAX_Y - 1;

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
        createFood(food, MAX_FOOD_SIZE, snake);
    }
    return snake;
}

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
    if (snake->direction == UP)
    {
        snakeDOWN = 0;
    }
    else if (snake->direction == LEFT)
        snakeRIGHT = 0;
    else if (snake->direction == DOWN)
        snakeUP = 0;
    else if (snake->direction == RIGHT)
    {
        snakeLeft = 0;
    }
    for (int i = 0; i < snake->tsize; i++)
    {
        if (((snake->x + snakeRIGHT) == snake->tail[i].x) && (snake->y == snake->tail[i].y))
        {
            snakeRIGHT = 0;
        }
        else if (((snake->x - snakeLeft) == snake->tail[i].x) && (snake->y == snake->tail[i].y))
            snakeLeft = 0;
        else if (((snake->y + snakeDOWN) == snake->tail[i].y) && (snake->x == snake->tail[i].x))
            snakeDOWN = 0;
        else if (((snake->y - snakeUP) == snake->tail[i].y) && (snake->x == snake->tail[i].x))
        {
            snakeUP = 0;
        }
    }

    for (int i = 0; i < MAX_FOOD_SIZE; i++)
        pointer = (distance(*snake, food[i]) < distance(*snake, food[pointer])) ? i : pointer;
    if ((snake->direction == RIGHT || snake->direction == LEFT) && (snake->y != food[pointer].y))
    {
        if ((food[pointer].y > snake->y) && snakeDOWN)
            snake->direction = DOWN;
        else if ((food[pointer].y <= snake->y) && snakeUP)
            snake->direction = UP;
    }
    if ((snake->direction == DOWN || snake->direction == UP) && (snake->x != food[pointer].x))
    {
        if ((food[pointer].x > snake->x) && snakeRIGHT)
            snake->direction = RIGHT;
        else if ((food[pointer].x <= snake->x) && snakeLeft)
            snake->direction = LEFT;
    }
    else if (snake->direction == UP && !snakeUP)
    {
        if (snakeLeft)
            snake->direction = LEFT;
        else if (snakeDOWN)
            snake->direction = DOWN;
        else if (snakeRIGHT)
            snake->direction = RIGHT;
    }
    else if (snake->direction == LEFT && !snakeLeft)
    {
        if (snakeUP)
            snake->direction = UP;
        else if (snakeDOWN)
            snake->direction = DOWN;
        else if (snakeRIGHT)
            snake->direction = RIGHT;
    }
    else if (snake->direction == DOWN && !snakeDOWN)
    {
        if (snakeUP)
            snake->direction = UP;
        else if (snakeLeft)
            snake->direction = LEFT;
        else if (snakeRIGHT)
            snake->direction = RIGHT;
    }
    else if (snake->direction == RIGHT && !snakeRIGHT)
    {
        if (snakeUP)
            snake->direction = UP;
        else if (snakeLeft)
            snake->direction = LEFT;
        else if (snakeDOWN)
            snake->direction = DOWN;
    }
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

int main()
{
    printf("\
1.Player\n\
2.Player vs bot\n\
3.Bot\n\
4.Bot vs Bot\n\
5.Player vs Player \n");
    struct snake_t snake;
    struct snake_t snake2;
    struct food food[MAX_FOOD_SIZE];
    initFood(food, MAX_FOOD_SIZE, '$');
    createFood(food, MAX_FOOD_SIZE, snake);
    while (!gameOver)
    {
        if (_kbhit())
        {
            switch (getch())
            {
            case '1':
                snake = initSnake(10, 10, 2, '@', 'o');
                snake2 = initSnake(3, 3, 0, ' ', '*');
                printSnake(snake, snake2, food);
                while (!gameOver)
                {
                    snake.direction = movement(snake);
                    snake = movementLogic(snake, food);
                    printSnake(snake, snake2, food);
                    printf("lvl Snake = %d\n", snake.lvlSnake);
                    _sleep(snake.speedSnake);
                    system("cls");
                }
                printf("Game over\nlvl Snake = %d\n", snake.lvlSnake);
                break;
            case '2':
                snake = initSnake(10, 10, 2, '@', 'o');
                snake2 = initSnake(3, 3, 2, '%', '*');
                printSnake(snake, snake2, food);
                while (!gameOver)
                {
                    snake.direction = movement(snake);
                    snake = movementLogic(snake, food);
                    generateSnakeDirection(&snake2, food);
                    snake2 = movementLogic(snake2, food);
                    printSnake(snake, snake2, food);
                    printf("lvl Snake = %d\n", snake.lvlSnake);
                    printf("lvl snakeBot = %d\n", snake2.lvlSnake);
                    _sleep(snake.speedSnake);
                    system("cls");
                }
                printf("Game over\nlvl Snake = %d", snake.lvlSnake);
                printf("Game over\nlvl Snake Bot = %d", snake2.lvlSnake);
                break;
            case '3':
                snake = initSnake(10, 10, 0, ' ', 'о');
                snake2 = initSnake(3, 3, 2, '%', '*');
                while (!gameOver)
                {
                    generateSnakeDirection(&snake2, food);
                    snake2 = movementLogic(snake2, food);
                    printSnake(snake, snake2, food);
                    printf("lvl snakeBot = %d\n", snake2.lvlSnake);
                    _sleep(snake2.speedSnake);
                    system("cls");
                }
                printf("Game over\nlvl Snake Bot = %d", snake2.lvlSnake);
                break;
            case '4':
                snake = initSnake(10, 10, 2, '@', 'o');
                snake2 = initSnake(3, 3, 2, '%', '*');
                while (!gameOver)
                {
                    generateSnakeDirection(&snake, food);
                    snake = movementLogic(snake, food);
                    generateSnakeDirection(&snake2, food);
                    snake2 = movementLogic(snake2, food);
                    printSnake(snake, snake2, food);
                    printf("lvl snakeBot1 = %d\n", snake.lvlSnake);
                    printf("lvl snakeBot2 = %d\n", snake2.lvlSnake);
                    _sleep(500);
                    system("cls");
                }
                printf("Game over\nlvl Snake 1 = %d", snake.lvlSnake);
                printf("Game over\nlvl Snake 2 = %d", snake2.lvlSnake);
                break;
            case '5':
                snake = initSnake(10, 10, 2, '@', 'o');
                snake2 = initSnake(3, 3, 2, '%', '*');
                printSnake(snake, snake2, food);
                while (!gameOver)
                {
                    input(&snake, &snake2);
                    snake = movementLogic(snake, food);
                    snake2 = movementLogic(snake2, food);
                    printSnake(snake, snake2, food);
                    printf("lvl Snake = %d\n", snake.lvlSnake);
                    printf("lvl snakeBot = %d\n", snake2.lvlSnake);
                    _sleep(snake.speedSnake);
                    system("cls");
                }
                printf("Game over\nlvl Snake = %d", snake.lvlSnake);
                printf("Game over\nlvl Snake Bot = %d", snake2.lvlSnake);
                break;
            }
        }
    }
    return 0;
}
#include "function.h"

// print snake and food
void printSnake(snake_t snake[], struct food f[])
{
    char matrix[MAX_X][MAX_Y];
    for (int i = 0; i < MAX_X; i++)
    {
        for (int j = 0; j < MAX_Y; j++)
        {
            matrix[i][j] = ' ';
            // game boundaries
            if (i == MAX_X - 1 || j == MAX_Y - 1 || i == 0 || j == 0)
            {
                matrix[i][j] = '#';
            }
        }
    }
    for (int i = 0; i < 5; i++)
    {
        matrix[snake[i].x][snake[i].y] = snake[i].headSymbol;

        for (int j = 0; j < snake[i].tsize; j++)
        {
            matrix[snake[i].tail[j].x][snake[i].tail[j].y] = snake[i].tailSymbol;
        }
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

void minu()
{
    printf("\
1.Player\n\
2.Player and  bot\n\
3.One Bot\n\
4.Two Bots\n\
5.Two Player\n\
6.Three Bots\n\
7.Four Bots\n\
8.Five Bots\n");
}

void printGameOver(int gameOver)
{
    if (gameOver == 1)
        printf("Whoa, whoa, whoa, I crashed =(\n");
    if (gameOver == 2)
        printf("overstepped its bounds\n");
}
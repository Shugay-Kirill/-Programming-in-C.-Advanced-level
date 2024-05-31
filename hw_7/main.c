#include "function.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdint.h>

int gameOver = 0;
int main(int argc, char const *argv[])
{
    minu();
    snake_t arraySnake[5];
    for (int i = 0; i < 5; i++)
        arraySnake[i] = initSnake(3, 3, 2, '@', 'o');

    struct food food[MAX_FOOD_SIZE];
    initFood(food, MAX_FOOD_SIZE, '$');
    createFood(food, MAX_FOOD_SIZE);
    while (!gameOver)
    {
        if (_kbhit())
        {
            switch (getch())
            {
            case '1':
                for (int i = 1; i < 5; i++)
                {
                    arraySnake[i].tsize = 0;
                    arraySnake[i].headSymbol = ' ';
                }
                while (!gameOver)
                {
                    arraySnake[0].direction = movement(arraySnake[0]);
                    arraySnake[0] = movementLogic(arraySnake[0], food);
                    printSnake(arraySnake, food);
                    printf("lvl Snake = %d\n", arraySnake[0].lvlSnake);
                    _sleep(arraySnake[0].speedSnake);
                    system("cls");
                }
                printGameOver(gameOver);
                printf("Game over\nlvl Snake = %d\n", arraySnake[0].lvlSnake);
                break;
            case '2':
                for (int i = 2; i < 5; i++)
                {
                    arraySnake[i].tsize = 0;
                    arraySnake[i].headSymbol = ' ';
                }
                while (!gameOver)
                {
                    arraySnake[0].direction = movement(arraySnake[0]);
                    arraySnake[0] = movementLogic(arraySnake[0], food);
                    generateSnakeDirection(&arraySnake[1], food);
                    arraySnake[1] = movementLogic(arraySnake[1], food);
                    printSnake(arraySnake, food);
                    printf("lvl Snake = %d\n", arraySnake[0].lvlSnake);
                    printf("lvl snakeBot = %d\n", arraySnake[1].lvlSnake);
                    _sleep(arraySnake[0].speedSnake);
                    system("cls");
                }
                printGameOver(gameOver);
                printf("Game over\nlvl Snake = %d\n", arraySnake[0].lvlSnake);
                printf("\nlvl Snake Bot = %d\n", arraySnake[1].lvlSnake);
                break;
            case '3':
                for (int i = 1; i < 5; i++)
                {
                    arraySnake[i].tsize = 0;
                    arraySnake[i].headSymbol = ' ';
                }
                arraySnake[1].x = 10;
                arraySnake[1].y = 10;
                while (!gameOver)
                {
                    generateSnakeDirection(&arraySnake[0], food);
                    arraySnake[0] = movementLogic(arraySnake[0], food);
                    printSnake(arraySnake, food);
                    printf("lvl snakeBot = %d\n", arraySnake[0].lvlSnake);
                    _sleep(arraySnake[0].speedSnake);
                    system("cls");
                }
                printGameOver(gameOver);
                printf("Game over\nlvl Snake Bot = %d", arraySnake[0].lvlSnake);
                break;
            case '4':
                for (int i = 2; i < 5; i++)
                {
                    arraySnake[i].tsize = 0;
                    arraySnake[i].headSymbol = ' ';
                }
                arraySnake[1].x = 10;
                arraySnake[1].y = 10;
                while (!gameOver)
                {
                    generateSnakeDirection(&arraySnake[0], food);
                    arraySnake[0] = movementLogic(arraySnake[0], food);
                    generateSnakeDirection(&arraySnake[1], food);
                    arraySnake[1] = movementLogic(arraySnake[1], food);
                    printSnake(arraySnake, food);
                    printf("lvl snakeBot1 = %d\n", arraySnake[0].lvlSnake);
                    printf("lvl snakeBot2 = %d\n", arraySnake[1].lvlSnake);
                    _sleep(arraySnake[0].speedSnake);
                    system("cls");
                }
                printGameOver(gameOver);
                printf("Game over\nlvl Snake 1 = %d\n", arraySnake[0].lvlSnake);
                printf("lvl Snake 2 = %d", arraySnake[1].lvlSnake);
                break;
            case '5':
                for (int i = 2; i < 5; i++)
                {
                    arraySnake[i].tsize = 0;
                    arraySnake[i].headSymbol = ' ';
                }
                arraySnake[1].x = 10;
                arraySnake[1].y = 10;
                while (!gameOver)
                {
                    input(&arraySnake[0], &arraySnake[1]);
                    arraySnake[0] = movementLogic(arraySnake[0], food);
                    arraySnake[1] = movementLogic(arraySnake[1], food);
                    printSnake(arraySnake, food);
                    printf("lvl Snake = %d\n", arraySnake[0].lvlSnake);
                    printf("lvl snakeBot = %d\n", arraySnake[1].lvlSnake);
                    _sleep(arraySnake[0].speedSnake);
                    system("cls");
                }
                printGameOver(gameOver);
                printf("Game over\nlvl Snake = %d", arraySnake[0].lvlSnake);
                printf("\nlvl Snake Bot = %d", arraySnake[1].lvlSnake);
                break;
            case '6':
                for (int i = 3; i < 5; i++)
                {
                    arraySnake[i].tsize = 0;
                    arraySnake[i].headSymbol = ' ';
                }
                arraySnake[1].x = 10;
                arraySnake[1].y = 10;
                arraySnake[2].x = 5;
                arraySnake[2].y = 5;
                while (!gameOver)
                {
                    generateSnakeDirection(&arraySnake[0], food);
                    arraySnake[0] = movementLogic(arraySnake[0], food);
                    generateSnakeDirection(&arraySnake[1], food);
                    arraySnake[1] = movementLogic(arraySnake[1], food);
                    generateSnakeDirection(&arraySnake[2], food);
                    arraySnake[2] = movementLogic(arraySnake[2], food);
                    printSnake(arraySnake, food);
                    printf("lvl snakeBot1 = %d\n", arraySnake[0].lvlSnake);
                    printf("lvl snakeBot2 = %d\n", arraySnake[1].lvlSnake);
                    printf("lvl snakeBot3 = %d\n", arraySnake[2].lvlSnake);
                    _sleep(arraySnake[0].speedSnake);
                    system("cls");
                }
                printGameOver(gameOver);
                printf("Game over\nlvl Snake 1 = %d", arraySnake[0].lvlSnake);
                printf("\nlvl Snake 2 = %d", arraySnake[1].lvlSnake);
                printf("\nlvl Snake 3 = %d", arraySnake[2].lvlSnake);
                break;
            case '7':
                for (int i = 4; i < 5; i++)
                {
                    arraySnake[i].tsize = 0;
                    arraySnake[i].headSymbol = ' ';
                }
                arraySnake[1].x = 10;
                arraySnake[1].y = 10;
                arraySnake[2].x = 5;
                arraySnake[2].y = 5;
                arraySnake[3].x = 7;
                arraySnake[3].y = 7;
                while (!gameOver)
                {
                    generateSnakeDirection(&arraySnake[0], food);
                    arraySnake[0] = movementLogic(arraySnake[0], food);
                    generateSnakeDirection(&arraySnake[1], food);
                    arraySnake[1] = movementLogic(arraySnake[1], food);
                    generateSnakeDirection(&arraySnake[2], food);
                    arraySnake[2] = movementLogic(arraySnake[2], food);
                    generateSnakeDirection(&arraySnake[3], food);
                    arraySnake[3] = movementLogic(arraySnake[3], food);
                    printSnake(arraySnake, food);
                    printf("lvl snakeBot1 = %d\n", arraySnake[0].lvlSnake);
                    printf("lvl snakeBot2 = %d\n", arraySnake[1].lvlSnake);
                    printf("lvl snakeBot3 = %d\n", arraySnake[2].lvlSnake);
                    printf("lvl snakeBot4 = %d\n", arraySnake[3].lvlSnake);
                    _sleep(arraySnake[0].speedSnake);
                    system("cls");
                }
                printGameOver(gameOver);
                printf("Game over\nlvl Snake 1 = %d", arraySnake[0].lvlSnake);
                printf("\nlvl Snake 2 = %d", arraySnake[1].lvlSnake);
                printf("\nlvl Snake 3 = %d", arraySnake[2].lvlSnake);
                printf("\nlvl Snake 4 = %d", arraySnake[3].lvlSnake);
                break;
            case '8':
                arraySnake[1].x = 10;
                arraySnake[1].y = 10;
                arraySnake[2].x = 5;
                arraySnake[2].y = 5;
                arraySnake[3].x = 7;
                arraySnake[3].y = 7;
                arraySnake[4].x = 9;
                arraySnake[4].y = 9;
                while (!gameOver)
                {
                    generateSnakeDirection(&arraySnake[0], food);
                    arraySnake[0] = movementLogic(arraySnake[0], food);
                    generateSnakeDirection(&arraySnake[1], food);
                    arraySnake[1] = movementLogic(arraySnake[1], food);
                    generateSnakeDirection(&arraySnake[2], food);
                    arraySnake[2] = movementLogic(arraySnake[2], food);
                    generateSnakeDirection(&arraySnake[3], food);
                    arraySnake[3] = movementLogic(arraySnake[3], food);
                    generateSnakeDirection(&arraySnake[4], food);
                    arraySnake[4] = movementLogic(arraySnake[4], food);
                    printSnake(arraySnake, food);
                    printf("lvl snakeBot1 = %d\n", arraySnake[0].lvlSnake);
                    printf("lvl snakeBot2 = %d\n", arraySnake[1].lvlSnake);
                    printf("lvl snakeBot3 = %d\n", arraySnake[2].lvlSnake);
                    printf("lvl snakeBot4 = %d\n", arraySnake[3].lvlSnake);
                    printf("lvl snakeBot5 = %d\n", arraySnake[4].lvlSnake);
                    _sleep(arraySnake[0].speedSnake);
                    system("cls");
                }
                printGameOver(gameOver);
                printf("Game over\nlvl Snake 1 = %d", arraySnake[0].lvlSnake);
                printf("\nlvl Snake 2 = %d", arraySnake[1].lvlSnake);
                printf("\nlvl Snake 3 = %d", arraySnake[2].lvlSnake);
                printf("\nlvl Snake 4 = %d", arraySnake[3].lvlSnake);
                printf("\nlvl Snake 5 = %d", arraySnake[4].lvlSnake);
                break;
            }
        }
    }
    return 0;
}

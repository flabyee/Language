﻿#include <iostream>
#include <time.h>

#include "Console.h"

using namespace std;

#define MAP_X   4
#define MAP_Y   2

#define KEY_DIRECTION       224
#define KEY_LEFT            75
#define KEY_RIGHT           77
#define KEY_UP              72
#define KEY_DOWN            80

int board[4][4] = {
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
};

bool bGameover;

void setConsoleView();

void initData();

void initDraw();    // 처음에 한번만 틀
void drawGame();    // 계속 변하는 내용

void createNumber();

void getKey();
bool moveNumber(int sX, int sY, int tX, int tY);

void checkGameover();

int main()
{
    srand((unsigned)time(NULL));

    setNoCursor();
    setConsoleView();

    initData();
    initDraw();

    createNumber();
    createNumber();
    createNumber();
    createNumber();
    createNumber();
    createNumber();
    createNumber();
    createNumber();
    createNumber();
    createNumber();
    createNumber();
    createNumber();
    createNumber();
    createNumber();

    while (true)
    {
        getKey();
        checkGameover();
    }

    return 0;
}

void setConsoleView()
{
    system("mode con:cols=32 lines=26");
    system("title 2048 GAME");
}

void initData()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            board[i][j] = 0;
        }
    }

    bGameover = false;
}

void initDraw()
{
    setTextColor(15);

    gotoXY(MAP_X - 2, MAP_Y - 1);
    cout << "|----------------------|";  

    for (int i = 0; i < 12; i++)
    {
        gotoXY(MAP_X - 2, MAP_Y + i);
        cout << "|                      |";
    }

    gotoXY(MAP_X - 2, MAP_Y + 12);
    cout << "|----------------------|";

    gotoXY(MAP_X , MAP_Y + 14);
    cout << "→, ←, ↑, ↓ : 이동";
}

void drawGame()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == 0)
            {
                setTextColor(8);
                gotoXY(MAP_X + j * 5, MAP_Y + i * 3);
                cout << "     ";
                gotoXY(MAP_X + j * 5, MAP_Y + i * 3 + 1);
                cout << "  +  ";
                gotoXY(MAP_X + j * 5, MAP_Y + i * 3 + 2);
                cout << "     ";
            }
            else
            {
                int num = board[i][j] > 10000 ? board[i][j] - 10000 : board[i][j];

                if (bGameover) 
                {
                    setTextColor(8);
                }
                else
                {
                    int sum = 1;
                    for (int k = 0; k < 12; k++)
                    {
                        sum *= 2;
                        if (sum == num)
                        {
                            setTextColor(k + 1);
                            break;
                        }
                    }
                }

                gotoXY(MAP_X + j * 5, MAP_Y + i * 3);
                cout << "|---|";
                gotoXY(MAP_X + j * 5, MAP_Y + i * 3 + 1);
                printf("%4d ", num);
                gotoXY(MAP_X + j * 5, MAP_Y + i * 3 + 2);
                cout << "|---|";

                if (bGameover)Sleep(200);
            }
        }
    }

    Sleep(10);
}

void createNumber()
{
    int* empty[16] = { 0, };
    int count = 0;  // 빈 곳의 갯수

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == 0)
            {
                empty[count] = &board[i][j];
                count++;
            }
        }
    }

    int random = rand() % count;
    int number = rand() % 100 < 20 ? 4 : 2;

    *empty[random] = number;
    drawGame();
    *empty[random] = 0;
    drawGame();
    *empty[random] = number;
    drawGame();
}

bool moveNumber(int sX, int sY, int tX, int tY) // source, target
{
    if (board[sY][sX] == 0 || board[sY][sX] > 10000) return false;
    if (board[tY][tX] != 0 && board[tY][tX] != board[sY][sX]) return false;

    if (board[tY][tX] == 0)
    {
        board[tY][tX] = board[sY][sX];
    }
    else if (board[tY][tX] == board[sY][sX])
    {
        board[tY][tX] *= 2;
        board[tY][tX] += 10000;
    }

    board[sY][sX] = 0;

    return true;
}

void getKey()
{
    bool bMove = false;
    bool bChange = false;

    int key = _getch();
    if (key == KEY_DIRECTION)
    {
        key = _getch();
        
        if (key == KEY_LEFT) {
            do {
                bMove = false;
                for (int i = 0; i < 4; i++){
                    for (int j = 1; j < 4; j++){
                        if (moveNumber(j, i, j - 1, i)){
                            bMove = true;
                            bChange = true;
                        }
                    }
                }

                if (bMove)drawGame();
                
            } while (bMove);
        }
        else if (key == KEY_RIGHT) {
            do {
                bMove = false;
                for (int i = 0; i < 4; i++) {
                    for (int j = 2; j >= 0; j--) {
                        if (moveNumber(j, i, j + 1, i)) {
                            bMove = true;
                            bChange = true;
                        }
                    }
                }

                if (bMove)drawGame();

            } while (bMove);
        }
        else if (key == KEY_UP) {
            do {
                bMove = false;
                for (int i = 1; i < 4; i++) {
                    for (int j = 0; j < 4; j++) {
                        if (moveNumber(j, i, j, i - 1)) {
                            bMove = true;
                            bChange = true;
                        }
                    }
                }

                if (bMove)drawGame();

            } while (bMove);
        }
        else if (key == KEY_DOWN) {
            do {
                bMove = false;
                for (int i = 2; i >= 0; i--) {
                    for (int j = 0; j < 4; j++) {
                        if (moveNumber(j, i, j, i + 1)) {
                            bMove = true;
                            bChange = true;
                        }
                    }
                }

                if (bMove)drawGame();

            } while (bMove);
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] > 10000)
            {
                board[i][j] -= 10000;
            }
        }
    }

    if (bChange)
    {
        createNumber();
    }
}

void checkGameover()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == 0)return;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == board[i][j + 1] || board[i][j] == board[i + 1][j])return;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        if (board[i][3] == board[i + 1][3])return;
    }

    for (int j = 0; j < 3; j++)
    {
        if (board[3][j] == board[3][j + 1])return;
    }


    setTextColor(15);

    gotoXY(MAP_X + 6, MAP_Y + 21);
    cout << "GAME OVER!";
    gotoXY(MAP_X + 4, MAP_Y + 22);
    cout << "x를 눌러서 종료";

    bGameover = true;

    drawGame();
    
    while (true)
    {
        setTextColor(rand() % 15);
        gotoXY(MAP_X + 6, MAP_Y + 21);
        cout << "GAME OVER!";

        if (getKeyDown() == 'x')
        {
            exit(0);
        }

        Sleep(50);
    }
}


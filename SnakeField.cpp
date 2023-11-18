#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <iostream>
#include "Snake game.h"
#include "framework.h"
#define NUM_PENS 5
void add_apple(int field[71][71], int size);

void DrawMap(HDC hdc, int arr[71][71], int size)
{
    HPEN pens[NUM_PENS];
    HBRUSH brushes[NUM_PENS];
    
    pens[0] = CreatePen(PS_SOLID, 1, RGB(12, 87, 5));
    brushes[0] = CreateSolidBrush(RGB(12, 87, 5));

    pens[1] = CreatePen(PS_SOLID, 1, RGB(0, 26, 0));
    brushes[1] = CreateSolidBrush(RGB(0, 128, 0));

    pens[2] = CreatePen(PS_SOLID, 3, RGB(54, 32, 19));
    brushes[2] = CreateSolidBrush(RGB(128, 75, 45));

    pens[3] = CreatePen(PS_SOLID, 2, RGB(128, 22, 23));
    brushes[3] = CreateHatchBrush(HS_DIAGCROSS, RGB(100, 107, 99));

    pens[4] = CreatePen(PS_SOLID, 2, RGB(143, 0, 24));
    brushes[4] = CreateSolidBrush(RGB(128, 0, 0));


    HPEN hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
    HBRUSH hBrush = CreateSolidBrush(RGB(12, 87, 5));
    SelectObject(hdc, hPen);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, 19, 19, 1001, 1001);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (arr[i][j] == 0)
            {
                continue;
            }
            SelectObject(hdc, pens[arr[i][j]]);
            SelectObject(hdc, brushes[arr[i][j]]);
            Rectangle(hdc, 20 + i * (980 / size), 20 + j * (980 / size), 20 + i * (980 / size) + (980 / size), 20 + j * (980 / size) + (980 / size));
        }
    }
    for (int i = 0; i < NUM_PENS; i++)
    {
        DeleteObject(pens[i]);
        DeleteObject(brushes[i]);
    }
}



void CreateField(int pa[71][71], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            pa[i][j] = 0;
        }
    }
}

void fiel_update(int parrfield[71][71], int parrsnake[5000][2], int size, int napr[2], int* snakesize)
{
    int flagapple = 0;
    if (parrfield[parrsnake[*snakesize + 3 - 1][0] + napr[0]][parrsnake[*snakesize + 3- 1][1] + napr[1]] == 4)
    {
        flagapple++;
    }
    parrfield[parrsnake[0][0]][parrsnake[0][1]] = 0;
    // Проверка выхода за границу поля 
    if (((parrsnake[*snakesize + 3 - 1][0] + napr[0]) >= size) or ((parrsnake[*snakesize + 3 - 1][1] + napr[1]) >= size) or ((parrsnake[*snakesize + 3 - 1][1] + napr[1]) < 0) or ((parrsnake[*snakesize + 3 - 1][0] + napr[0]) < 0))
    {
        keybd_event(0x52, 0x52, 0 | 0, 0);
        return;
    }
    // Проверка напозания на что либо
    if ((parrfield[parrsnake[*snakesize + 3 - 1][0] + napr[0]][parrsnake[*snakesize + 3 - 1][1] + napr[1]] != 0) and (parrfield[parrsnake[*snakesize + 3 - 1][0] + napr[0]][parrsnake[*snakesize + 3 - 1][1] + napr[1]] != 4))
    {
        keybd_event(0x52, 0x52, 0 | 0, 0);
        return;
    }


    // Движение змейки
    switch (flagapple)
    {
    case 0:
        for (int i = 0; i < *snakesize + 3; i++)
        {
            parrsnake[i][0] = parrsnake[i + 1][0];
            parrsnake[i][1] = parrsnake[i + 1][1];
        }
        parrsnake[*snakesize + 3- 1][0] = parrsnake[*snakesize + 3 - 2][0] + napr[0];
        parrsnake[*snakesize + 3 - 1][1] = parrsnake[*snakesize + 3 - 2][1] + napr[1];
        break;
    case 1:
        parrsnake[*snakesize + 3][0] = parrsnake[*snakesize + 3- 1][0] + napr[0];
        parrsnake[*snakesize + 3][1] = parrsnake[*snakesize + 3- 1][1] + napr[1];
        break;
    default:
        break;
    }
    *snakesize += flagapple;
    //
    parrfield[parrsnake[0][0]][parrsnake[0][1]] = 1;
    parrfield[parrsnake[*snakesize + 3 - 1][0]][parrsnake[*snakesize + 3 - 1][1]] = 2;
    parrfield[parrsnake[*snakesize + 3- 2][0]][parrsnake[*snakesize + 3 - 2][1]] = 1;
}


void add_apple(int field[71][71], int apple_cord[2], int size)
{
    srand(time(NULL));
    int y = 1 + rand() % (size - 2) , x = 1 + rand() % (size - 2);
    if (field[y][x] == 0)
    {
        field[y][x] = 4;
    }
    apple_cord[0] = y;
    apple_cord[1] = x;
}

void restart_game(int arrfield[71][71], int arrsnake[5000][2], int *score)
{
    for (int i = 0; i < 71; i++)
    {
        for (int j = 0; j < 71; j++)
        {
            arrfield[i][j] = 0;
        }
    }
    for (int i = 0; i < 5000; i++)
    {
        arrsnake[i][0] = 0;
        arrsnake[i][1] = 0;
    }
    *score = 0;
    // устанавливаем новую змейку
    arrfield[1][1] = 1;
    arrfield[1][2] = 1;
    arrfield[1][3] = 2;

    arrsnake[0][0] = 1;
    arrsnake[0][1] = 1;

    arrsnake[1][0] = 1;
    arrsnake[1][1] = 2;

    arrsnake[2][0] = 1;
    arrsnake[2][1] = 3;
}
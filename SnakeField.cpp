#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include "Snake game.h"
#include "framework.h"
#define NUM_PENS 4

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
    HPEN hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
    HBRUSH hBrush = CreateSolidBrush(NULL);
    SelectObject(hdc, hPen);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, 19, 19, 1001, 1001);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {

            SelectObject(hdc, pens[arr[i][j]]);
            SelectObject(hdc, brushes[arr[i][j]]);
            Rectangle(hdc, 20 + i * (980 / size), 20 + j * (980 / size), 20 + i * (980 / size) + (980 / size), 20 + j * (980 / size) + (980 / size));
        }
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

    
}
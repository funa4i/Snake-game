#pragma once

//void CreateField(int** pa, int size);
void DrawMap(HDC hdc, int pa[71][71], int size);
void CreateField(int pa[71][71], int size);
void fiel_update(int parrfield[71][71], int parrsnake[5000][2], int size, int napr[2], int* snakesize);
void add_apple(int field[71][71], int apple_cord[2], int size);
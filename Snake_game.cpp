// Snake game.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Snake game.h"
#include <stdio.h>
#include <stdlib.h>
#include "SnakeField.h"
#include <wchar.h>
#define FIELDSIZE 71
#define MAXSNAKESIZE 5000

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int field[FIELDSIZE][FIELDSIZE];
int allowFsize[6]{10, 14, 20, 28, 35, 49};
int selectsize = 0;
int snakearr[MAXSNAKESIZE][2]{ {1, 1}, {1, 2}, {1, 3} };
int fsize = 10;
int apple_cord[2]{-1, -1};
int score = 0;
int napr[2]{ 0, 1 };
int *pscore = &score;

HFONT hFont = CreateFont(
    94,                 // Размер шрифта (в пунктах)
    0,                  // Ширина шрифта (0 - автоматически)
    0,                  // Угол наклона (0 - наклон отсутствует)
    0,                  // Угол поворота (0 - поворот отсутствует)
    FW_NORMAL,           // Толщина шрифта (FW_NORMAL - нормальная толщина)
    FALSE,              // Курсив (FALSE - не курсив)
    FALSE,              // Подчеркивание (FALSE - не подчеркивать)
    FALSE,              // Зачеркивание (FALSE - не зачеркивать)
    DEFAULT_CHARSET,    // Набор символов (DEFAULT_CHARSET - системный набор)
    OUT_OUTLINE_PRECIS, // Точность вывода шрифта
    CLIP_DEFAULT_PRECIS, // Точность ограничения
    ANTIALIASED_QUALITY, // Качество рендеринга
    FF_DONTCARE | DEFAULT_PITCH, // Семейство шрифта и шаг
    L"Arial"            // Имя шрифта
);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.
    field[1][1] = 1;
    field[1][2] = 1;
    field[1][3] = 2;

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SNAKEGAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SNAKEGAME));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    
    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SNAKEGAME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+2);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SNAKEGAME);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        add_apple(field, apple_cord, fsize);
        SetTimer(hWnd, 1, 100, 0);
        break;
    case WM_TIMER:
        UpdateWindow(hWnd);
        if (field[apple_cord[0]][apple_cord[1]] != 4)
        {
            add_apple(field, apple_cord, fsize);
        }
        fiel_update(field, snakearr, fsize, napr, pscore);
        InvalidateRect(hWnd, NULL, TRUE);
        
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {

            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case 0x45:
            selectsize = (selectsize + 1) % 6;
            keybd_event(0x52, 0x52, 0 | 0, 0);
            break;
        case 0x51:
            if (selectsize - 1 < 0)
            {
                selectsize = 5;
            }
            else
            {
                selectsize--;
            }
            keybd_event(0x52, 0x52, 0 | 0, 0);
            break;
        case 0x50:
            KillTimer(hWnd, 1);
            break;
        case 0x52:
            fsize = allowFsize[selectsize];
            KillTimer(hWnd, 1);
            restart_game(field, snakearr, pscore);
            napr[0] = 0;
            napr[1] = 1;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case 0x53:
            SetTimer(hWnd, 1, 100, 0);
            break;
        case VK_LEFT:
            napr[0] = -1;
            napr[1] = 0;
            break;
        case VK_RIGHT:
            napr[0] = 1;
            napr[1] = 0;
            break;
        case VK_UP:
            napr[0] = 0;
            napr[1] = -1;
            break;
        case VK_DOWN:
            napr[0] = 0;
            napr[1] = 1;
        default:
            break;
        }
    case WM_PAINT:
        {
            wchar_t text[20]{}, textfields[30]{};
            swprintf(textfields, 30, L"%d x %d", allowFsize[selectsize], allowFsize[selectsize]);
            swprintf(text, 20, L"SCORE: %d", score);
            field[30][30] = 0;
            SetWindowPos(hWnd, NULL, 0, 0, 1920, 1080, NULL);
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC..
            HPEN hPen = CreatePen(PS_INSIDEFRAME, 1, RGB(255, 255, 255));
            HBRUSH hBrush = CreateSolidBrush(RGB(0, 26, 0));
            SelectObject(hdc, hBrush);
            SelectObject(hdc, hPen);
            SetTextColor(hdc, RGB(255, 255, 255));
            SetBkMode(hdc, NULL);
            TextOut(hdc, 1100, 20, text, 12);
            TextOut(hdc, 1100, 120, textfields, 12);
            DrawMap(hdc, field, fsize);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

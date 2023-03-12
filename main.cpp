#include <Windows.h>
#include<iostream>
#include "resource.h"


/*1. MainWindow должно запускаться ровно посередине экрана. Для этого нужно определить размер экрана (разрешение экрана),
   вычислить размер окна и вычислить начальную позицию окна. Все эти свойства нужно передать функции CreateWindowEx().
   Для того чтобы определить разрешение экрана используется функция GetSystemMetrics();
2. При изменении размера окна и его положения на экране все эти параметры должны отображаться в заголовке окна.
   Для того чтобы установить заголовок окна нужно послать окну сообщение WM_SETTEXT.
   При перемещении окна и изменении его размеров, окну неявно посылаются сообщения WM_MOVE и MW_SIZE;
3. При закрытии окна должно выдаваться сообщение "Вы действительно хотите закрыть окно?" "Да", "Нет";*/


CONST CHAR g_sz_ClassName[] = "MySandwichClass";
INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) Регистрация класса окна
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize = sizeof(wc);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.style = 0;
	/*wc.hIcon = (HICON)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hIconSm = (HICON)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));*/
	//альтернатива
	wc.hIcon = (HICON)LoadImage(hInstance, "beer.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hIconSm = (HICON)LoadImage(hInstance, "sandwich.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//
	wc.hCursor = (HCURSOR)LoadImage(hInstance, "Sandwich.cur", IMAGE_CURSOR, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hInstance = hInstance;//задаем экзмепляр *exe файла
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_sz_ClassName;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed.", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//2) Создание окна
	int h = 300, w = 600;
	RECT rc;
	rc.right = w;
	rc.bottom = h;
	rc.left = 0;
	rc.top = 0;
	int win_w = rc.right - rc.left;
	int win_h = rc.bottom - rc.top;
	int screen_w = GetSystemMetrics(SM_CXSCREEN);
	int screen_h = GetSystemMetrics(SM_CYSCREEN);
	int win_x = (screen_w / 2) - (win_w / 2);
	int win_y = (screen_h / 2) - (win_h / 2);
	HWND hwnd = CreateWindowEx
	(
		NULL,//exStyle- расширенный стиль окна
		g_sz_ClassName,//имя класса окна
		"",//заголов окна
		WS_OVERLAPPEDWINDOW,//стиль окна (обычное, диалоговое,кнопка,текстовое и тд)
		win_x, win_y, //начальные координаты окна(лев верх)
		win_w, win_h,//размер окна
		//начальные координаты и размер окна всегда задаются в пикселах
		NULL,//роидетльское окна как всегда у WS_OVERLAPPEDWINDOW
		NULL,//меню отсутствует
		hInstance,
		NULL
	);

	if (hwnd == 0)
	{
		MessageBox(NULL, "Window creation failed.", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);//задаем режим отображения окна (свернуто в окно, развернуто на весь экран, свернуто на панель задач итд)
	UpdateWindow(hwnd);//прорисовывает содержимое окна

	//3) Запуск цикла сообщений
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		break;
	case WM_CREATE:
		break;
	case WM_COMMAND:
		break;
	case WM_MOVE:
	{
		CONST INT SIZE = 256;
		CHAR sz_buffer[SIZE] = {};
		RECT rect = { NULL };
		GetWindowRect(hwnd, &rect);
		int x = rect.left;
		int y = rect.top;
		sprintf_s(sz_buffer, SIZE, "%d, %d", x, y);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
	}
	break;
	case WM_SIZE:
	{
		CONST INT SIZE = 256;
		CHAR sz_buffer[SIZE] = {};
		RECT rect = { NULL };
		GetWindowRect(hwnd, &rect);
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;
		sprintf_s(sz_buffer, SIZE, "%d, %d", width, height);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
	}
	break;
	case WM_DESTROY:PostQuitMessage(0);
		break;
	case WM_CLOSE:
	{
		int message = MessageBox(hwnd, "Выйти?", "Info", MB_YESNO | MB_ICONINFORMATION);
		switch (message)
		{
		case IDYES: DestroyWindow(hwnd); break;
		case IDNO:break;
		}
	}
	break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;

}

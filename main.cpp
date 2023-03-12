#include <Windows.h>
#include<iostream>
#include "resource.h"


/*1. MainWindow ������ ����������� ����� ���������� ������. ��� ����� ����� ���������� ������ ������ (���������� ������),
   ��������� ������ ���� � ��������� ��������� ������� ����. ��� ��� �������� ����� �������� ������� CreateWindowEx().
   ��� ���� ����� ���������� ���������� ������ ������������ ������� GetSystemMetrics();
2. ��� ��������� ������� ���� � ��� ��������� �� ������ ��� ��� ��������� ������ ������������ � ��������� ����.
   ��� ���� ����� ���������� ��������� ���� ����� ������� ���� ��������� WM_SETTEXT.
   ��� ����������� ���� � ��������� ��� ��������, ���� ������ ���������� ��������� WM_MOVE � MW_SIZE;
3. ��� �������� ���� ������ ���������� ��������� "�� ������������� ������ ������� ����?" "��", "���";*/


CONST CHAR g_sz_ClassName[] = "MySandwichClass";
INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) ����������� ������ ����
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize = sizeof(wc);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.style = 0;
	/*wc.hIcon = (HICON)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hIconSm = (HICON)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));*/
	//������������
	wc.hIcon = (HICON)LoadImage(hInstance, "beer.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hIconSm = (HICON)LoadImage(hInstance, "sandwich.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//
	wc.hCursor = (HCURSOR)LoadImage(hInstance, "Sandwich.cur", IMAGE_CURSOR, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hInstance = hInstance;//������ ��������� *exe �����
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_sz_ClassName;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed.", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//2) �������� ����
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
		NULL,//exStyle- ����������� ����� ����
		g_sz_ClassName,//��� ������ ����
		"",//������� ����
		WS_OVERLAPPEDWINDOW,//����� ���� (�������, ����������,������,��������� � ��)
		win_x, win_y, //��������� ���������� ����(��� ����)
		win_w, win_h,//������ ����
		//��������� ���������� � ������ ���� ������ �������� � ��������
		NULL,//������������ ���� ��� ������ � WS_OVERLAPPEDWINDOW
		NULL,//���� �����������
		hInstance,
		NULL
	);

	if (hwnd == 0)
	{
		MessageBox(NULL, "Window creation failed.", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);//������ ����� ����������� ���� (�������� � ����, ���������� �� ���� �����, �������� �� ������ ����� ���)
	UpdateWindow(hwnd);//������������� ���������� ����

	//3) ������ ����� ���������
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

//void GetWindowPos(int* x, int* y) 
//{
//	RECT rect = { NULL };
//	if (GetWindowRect(hwnd, &rect)) 
//	{
//		*x = rect.left;
//		*y = rect.top;
//	}
//}
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
		//MessageBox(hwnd, "���������", "Info", MB_YESNO | MB_ICONINFORMATION);
		/*CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE] = {};
				HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
				SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
				if (strcmp(sz_buffer, gsz_DEFAULT_LOGIN_MESSAGE) == 0)
					SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)"");*/
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
		int message = MessageBox(hwnd, "�����?", "Info", MB_YESNO | MB_ICONINFORMATION);
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

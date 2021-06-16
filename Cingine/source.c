
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <math.h>

const int SCREEN_WIDTH = 50;
const int SCREEN_HEIGHT = 50;
int IIndex = 0;

int main()
{
	float calc = 0;
    time_t begin = time(NULL);
	
    for (long i = 0; i < 15000000; i++)
    {
	    if(calc > 5)
	    {
            calc = sinf((float)i);
	    }
        else
        {
            calc = cosf((float)i);
        }
    }
    printf_s("cout %f\n", calc);

	
    time_t end = time(NULL);

    double d = difftime(end, begin);

	float fl = 0.0025f;
    printf("for loop used %f seconds to complete the " \
        "execution\n", difftime(end, begin));

    system("pause");
    return 0;
}
int mains()
{
	//Allocating resources
    wchar_t* screen = (wchar_t*)malloc((size_t)SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(wchar_t));
    DWORD  word = 0;
    const COORD c = { 0,0 };
    HANDLE handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	//Initializing resources
	if(screen == NULL) return 0;
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_WIDTH; i++)
    {
        screen[i] = '-';
    }
	SetConsoleActiveScreenBuffer(handle);

 
	


	

    int i = 5000;
	while(1)
	{
        screen[IIndex] = 'i';
		
        WriteConsoleOutputCharacter(handle, screen, SCREEN_WIDTH * SCREEN_HEIGHT, c, &word);

        screen[IIndex] = '-';

        if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
            IIndex++;

        IIndex = IIndex >= (SCREEN_WIDTH * SCREEN_WIDTH) ? 0 : IIndex;
		
	}
	
}

/*
LRESULT CALLBACK event(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{


    switch (msg)
    {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASS wndClass;
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hInstance = hInstance;
    wndClass.lpszMenuName = NULL;
    wndClass.lpfnWndProc = event;
    wndClass.lpszClassName = L"ME";
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.style = CS_HREDRAW | CS_VREDRAW;

    int err = RegisterClass(&wndClass);
    if (err < 0)
    {
        MessageBox(NULL, L"Can not register window class!", L"Error", 0);
        return -1;
    }
    HWND hwnd;
    hwnd = CreateWindow(L"ME",
        L"Test",
        WS_OVERLAPPEDWINDOW,
        100,
        100,
        300,
        300,
        NULL,
        NULL,
        hInstance,
        NULL);
    if (hwnd == NULL)
    {
        MessageBox(NULL, L"Can not create window!", L"Error", 0);
        return -1;
    }
    ShowWindow(hwnd, SW_NORMAL);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}*/
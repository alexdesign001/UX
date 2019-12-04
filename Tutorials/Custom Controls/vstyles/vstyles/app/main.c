/* File main.c
 * (application doing actually nothing but creating a main window and
 *  the custom control as its only child)
 */

#include <tchar.h>
#include <windows.h>
#include <commctrl.h>

#include "../dll/custom.h"


static HINSTANCE hInstance;


// Main window procedure. It just creates the custom control and a button for visual comparision.
static LRESULT CALLBACK
MainProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg) {
        case WM_CREATE:
            CreateWindow(_T("BUTTON"), _T("Button"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                         10, 10, 70, 30, hwnd, (HMENU) 101, hInstance, NULL);
            CreateWindow(CUSTOM_WC, _T("Custom"), WS_CHILD | WS_VISIBLE,
                         10, 45, 70, 30, hwnd, (HMENU) 100, hInstance, NULL);
            break;

        case WM_CLOSE:
            PostQuitMessage(0);
            break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int APIENTRY
_tWinMain(HINSTANCE hInst, HINSTANCE hInstPrev, TCHAR* lpszCmdLine, int iCmdShow)
{
    WNDCLASS wc = { 0 };
    HWND hwnd;
    MSG msg;

    hInstance = hInst;

	// Make sure linker does not omit COMCTL32.DLL:
	InitCommonControls();

	// Register the custom control class:
    CustomRegister();

	// Register main window class:
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = MainProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wc.lpszClassName = _T("MainWindow");
    RegisterClass(&wc);

	// Create the main window:
    hwnd = CreateWindow(_T("MainWindow"), _T("App Name"), WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, 350, 250, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, iCmdShow);

	// Normal message loop:
    while(GetMessage(&msg, NULL, 0, 0)) {
        if(IsDialogMessage(hwnd, &msg))
            continue;

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    CustomUnregister();

    return (int)msg.wParam;
}

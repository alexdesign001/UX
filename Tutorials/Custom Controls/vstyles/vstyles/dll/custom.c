/* File custom.c
 * (custom control implementation)
 */

#include "custom.h"

#include <windows.h>
#include <wingdi.h>
#include <shlwapi.h>   // DLLVERSIONINFO
#include <vsstyle.h>   // part and state constants
#include <uxtheme.h>   // main UXTHEME header


// The theming class we use for painting of this control:
#define CUSTOM_THEME_CLASS    L"BUTTON"


// Pointers to the few UXTHEME.DLL functions we use. If we decide to not use UXTHEME.DLL
// we just make fn_OpenThemeData to point to our dummy implementation, returning NULL.
// This consrquently guarantees we never attempt to call the other UXTHEME functions:
static HMODULE hDllUxTheme = NULL;
static HTHEME  (WINAPI* fn_OpenThemeData)(HWND,const WCHAR*) = NULL;
static HTHEME  (WINAPI* fn_CloseThemeData)(HTHEME) = NULL;
static HRESULT (WINAPI* fn_DrawThemeBackground)(HTHEME,HDC,int,int,const RECT*,const RECT*) = NULL;
static HRESULT (WINAPI* fn_DrawThemeParentBackground)(HWND,HDC,RECT*) = NULL;
static BOOL    (WINAPI* fn_IsThemeBackgroundPartiallyTransparent)(HTHEME,int,int) = NULL;


// Custom control's data
typedef struct CustomData {
	HWND hwnd;
	HTHEME hTheme;   // The theme handle, or NULL when not themed.
	DWORD style;
} CustomData;

static void
CustomPaint(CustomData* pData, HDC hDC, RECT* rcDirty, BOOL bErase)
{
	TCHAR szBuffer[64];
	RECT rect;

	GetClientRect(pData->hwnd, &rect);

	// We paint just (non-interactive) button, for illustrative purposes:
	if(pData->hTheme) {
		// Theme paint code path.
		int part = BP_PUSHBUTTON;
		int state = PBS_NORMAL;

		if(fn_IsThemeBackgroundPartiallyTransparent(pData->hTheme, part, state))
			fn_DrawThemeParentBackground(pData->hwnd, hDC, &rect);
		fn_DrawThemeBackground(pData->hTheme, hDC, part, state, &rect, &rect);
	} else {
		// Fallback to the old paint methods:
		DrawFrameControl(hDC, &rect, DFC_BUTTON, DFCS_BUTTONPUSH);
	}

	GetWindowText(pData->hwnd, szBuffer, sizeof(szBuffer) / sizeof(TCHAR));
	SetBkMode(hDC, TRANSPARENT);
	DrawText(hDC, szBuffer, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

static void
CustomDoubleBuffer(CustomData* pData, PAINTSTRUCT* pPaintStruct)
{
    int cx = pPaintStruct->rcPaint.right - pPaintStruct->rcPaint.left;
    int cy = pPaintStruct->rcPaint.bottom - pPaintStruct->rcPaint.top;
    HDC hMemDC;
    HBITMAP hBmp;
    HBITMAP hOldBmp;
    POINT ptOldOrigin;

    // Create new bitmap-back device context, large as the dirty rectangle.
    hMemDC = CreateCompatibleDC(pPaintStruct->hdc);
    hBmp = CreateCompatibleBitmap(pPaintStruct->hdc, cx, cy);
    hOldBmp = SelectObject(hMemDC, hBmp);

    // Do the painting into the memory bitmap.
    OffsetViewportOrgEx(hMemDC, -(pPaintStruct->rcPaint.left),
                        -(pPaintStruct->rcPaint.top), &ptOldOrigin);
    CustomPaint(pData, hMemDC, &pPaintStruct->rcPaint, TRUE);
    SetViewportOrgEx(hMemDC, ptOldOrigin.x, ptOldOrigin.y, NULL);

    // Blit the bitmap into the screen. This is really fast operation and altough
    // the CustomPaint() can be complex and slow there will be no flicker any more.
    BitBlt(pPaintStruct->hdc, pPaintStruct->rcPaint.left, pPaintStruct->rcPaint.top,
           cx, cy, hMemDC, 0, 0, SRCCOPY);

    // Clean up.
    SelectObject(hMemDC, hOldBmp);
    DeleteObject(hBmp);
    DeleteDC(hMemDC);
}

static LRESULT CALLBACK
CustomProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CustomData* pData = (CustomData*) GetWindowLongPtr(hwnd, 0);

    switch(uMsg) {
        case WM_ERASEBKGND:
            return FALSE;  // Defer erasing into WM_PAINT

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
			// We let application to choose whether to use double buffering
			// or not by using the style CCS_DOUBLEBUFFER.
            if(pData->style & XXS_DOUBLEBUFFER)
                CustomDoubleBuffer(pData, &ps);
            else
                CustomPaint(pData, ps.hdc, &ps.rcPaint, ps.fErase);
            EndPaint(hwnd, &ps);
            return 0;
		}

		case WM_PRINTCLIENT:
        {
            RECT rc;
            GetClientRect(hwnd, &rc);
            CustomPaint(pData, (HDC) wParam, &rc, TRUE);
            return 0;
        }

		case WM_STYLECHANGED:
			if(wParam == GWL_STYLE)
				pData->style = lParam;
			break;

		case WM_THEMECHANGED:
			// Reopen the theme handle:
			if(pData->hTheme)
				fn_CloseThemeData(pData->hTheme);
			pData->hTheme = fn_OpenThemeData(hwnd, CUSTOM_THEME_CLASS);
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;				

		case WM_CREATE:
			DefWindowProc(hwnd, uMsg, wParam, lParam);
			// Open the theme handle:
			pData->hTheme = fn_OpenThemeData(hwnd, CUSTOM_THEME_CLASS);
			return 0;

		case WM_DESTROY:
			if(pData->hTheme) {
				fn_CloseThemeData(pData->hTheme);
				pData->hTheme = NULL;
			}
			break;

		case WM_NCCREATE:
			DefWindowProc(hwnd, uMsg, wParam, lParam);
			pData = (CustomData*) malloc(sizeof(CustomData));
			if(pData == NULL)
				return FALSE;
			SetWindowLongPtr(hwnd, 0, (LONG_PTR)pData);
			pData->hwnd = hwnd;
			pData->hTheme = NULL;
			pData->style = ((CREATESTRUCT*)lParam)->style;
			return TRUE;

		case WM_NCDESTROY:
			if(pData != NULL) {
				free(pData);
			}
			break;
    }
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Function checking whether the app we are hosted in expects this DLL
// to play with UXTHEME or not.
static BOOL ShouldUseUxThemeDll(void) 
{
	HMODULE hDll;
	DWORD dwMajorVersion = 0;

    hDll = LoadLibrary(_T("COMCTL32.DLL"));
	if(hDll != NULL) {
		DLLGETVERSIONPROC fn_DllGetVersion;
		DLLVERSIONINFO vi;

		fn_DllGetVersion = (DLLGETVERSIONPROC) GetProcAddress(hDll, "DllGetVersion");
		if(fn_DllGetVersion != NULL) {
			vi.cbSize = sizeof(DLLVERSIONINFO);
			fn_DllGetVersion(&vi);
			dwMajorVersion = vi.dwMajorVersion;
		}
		FreeLibrary(hDll);
	}

	return (dwMajorVersion >= 6);
}

// Dummy OpenThemeData() replacemnt. Always returns NULL theme handle, so
// when used, the painting code always chooses the untheme code path.
static HTHEME WINAPI dummy_OpenThemeData(HWND hwnd, const WCHAR* pswzClassName)
{
	return NULL;
}

static void
LoadUxThemeDll(void)
{
	fn_OpenThemeData = NULL;

	// Load UXTHEME.DLL only if we decide application wants to use it:
	if(ShouldUseUxThemeDll())
		hDllUxTheme = LoadLibrary(_T("UXTHEME.DLL"));
	else
		hDllUxTheme = NULL;

	// Get pointers to functions we need from it:
	if(hDllUxTheme) {
		fn_OpenThemeData = (HTHEME (WINAPI*)(HWND,const WCHAR*))
					GetProcAddress(hDllUxTheme, "OpenThemeData");
		fn_CloseThemeData = (HTHEME (WINAPI*)(HTHEME)) 
					GetProcAddress(hDllUxTheme, "CloseThemeData");
		fn_DrawThemeBackground = (HRESULT (WINAPI*)(HTHEME,HDC,int,int,const RECT*,const RECT*))
					GetProcAddress(hDllUxTheme, "DrawThemeBackground");
		fn_DrawThemeParentBackground = (HRESULT (WINAPI*)(HWND,HDC,RECT*))
					GetProcAddress(hDllUxTheme, "DrawThemeParentBackground");
		fn_IsThemeBackgroundPartiallyTransparent = (BOOL (WINAPI*)(HTHEME,int,int))
					GetProcAddress(hDllUxTheme, "IsThemeBackgroundPartiallyTransparent");

		if(fn_OpenThemeData == NULL || fn_CloseThemeData == NULL ||  
		   fn_DrawThemeBackground == NULL || fn_DrawThemeParentBackground == NULL ||
		   fn_IsThemeBackgroundPartiallyTransparent == NULL) 
		{
			// Some function missing???
			// Behave as if the library is not available at all.
			FreeLibrary(hDllUxTheme);
			hDllUxTheme = NULL;
		}
	}

	// If (for any reason) UXTHEME.DLL is not loaded, use our own dummy 
	// replacement of OpenThemeData(), which always returns NULL.
	if(hDllUxTheme == NULL)
		fn_OpenThemeData = dummy_OpenThemeData;
}

void WINAPI
CustomRegister(void)
{
    WNDCLASS wc = { 0 };

	// Load UXTHEME.DLL and get needed symbols:
	LoadUxThemeDll();

	// Register control's window class:
    wc.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = CustomProc;
	wc.cbWndExtra = sizeof(CustomData*);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = CUSTOM_WC;
    RegisterClass(&wc);
}

void WINAPI
CustomUnregister(void)
{
    UnregisterClass(CUSTOM_WC, NULL);
	if(hDllUxTheme != NULL) {
		FreeLibrary(hDllUxTheme);
		hDllUxTheme = NULL;
	}
}

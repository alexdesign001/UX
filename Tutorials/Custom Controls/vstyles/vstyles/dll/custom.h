/* File custom.h
 * (custom control interface)
 */

#ifndef CUSTOM_H
#define CUSTOM_H

#include <tchar.h>
#include <windows.h>


/* Window class */
#define CUSTOM_WC              _T("CustomControl")

/* Style to request using double buffering. */
#define XXS_DOUBLEBUFFER         (0x0001)

/* Register/unregister the window class */
void WINAPI CustomRegister(void);
void WINAPI CustomUnregister(void);


#endif  /* CUSTOM_H */

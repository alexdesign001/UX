namespace ThemeBrowser.Native
{
    using System.Runtime.InteropServices;

    internal static class NativeMethods
    {
        [DllImport("user32")]
        public static extern int GetSysColor(SysColor nIndex);
    }

    internal enum SysColor
    {
        COLOR_SCROLLBAR = 0,
        COLOR_BACKGROUND = 1,
        COLOR_ACTIVECAPTION = 2,
        COLOR_INACTIVECAPTION = 3,
        COLOR_MENU = 4,
        COLOR_WINDOW = 5,
        COLOR_WINDOWFRAME = 6,
        COLOR_MENUTEXT = 7,
        COLOR_WINDOWTEXT = 8,
        COLOR_CAPTIONTEXT = 9,
        COLOR_ACTIVEBORDER = 10,
        COLOR_INACTIVEBORDER = 11,
        COLOR_APPWORKSPACE = 12,
        COLOR_HIGHLIGHT = 13,
        COLOR_HIGHLIGHTTEXT = 14,
        COLOR_BTNFACE = 15,
        COLOR_BTNSHADOW = 16,
        COLOR_GRAYTEXT = 17,
        COLOR_BTNTEXT = 18,
        COLOR_INACTIVECAPTIONTEXT = 19,
        COLOR_BTNHIGHLIGHT = 20,
        COLOR_3DDKSHADOW = 21,
        COLOR_3DLIGHT = 22,
        COLOR_INFOTEXT = 23,
        COLOR_INFOBK = 24,
        COLOR_HOTLIGHT = 26,
        COLOR_GRADIENTACTIVECAPTION = 27,
        COLOR_GRADIENTINACTIVECAPTION = 28,
        COLOR_MENUHILIGHT = 29,
        COLOR_MENUBAR = 30,
        COLOR_DESKTOP = COLOR_BACKGROUND,
        COLOR_THREEDFACE = COLOR_BTNFACE,
        COLOR_3DSHADOW = COLOR_BTNSHADOW,
        COLOR_3DHIGHLIGHT = COLOR_BTNHIGHLIGHT,
        COLOR_3DHILIGHT = COLOR_BTNHIGHLIGHT,
        COLOR_BTNHILIGHT = COLOR_BTNHIGHLIGHT,
    }
}
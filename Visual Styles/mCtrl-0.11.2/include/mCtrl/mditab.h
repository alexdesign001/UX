/*
 * Copyright (c) 2008-2015 Martin Mitas
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef MCTRL_MDITAB_H
#define MCTRL_MDITAB_H

#include <mCtrl/_defs.h>
#include <mCtrl/_common.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @file
 * @brief MDI tab control (@c MC_WC_MDITAB).
 *
 * This control is a replacement for standard multiple document interface
 * (MDI), as that interface seems to be outdated, and does not reflect
 * modern GUI requirements.
 *
 * Instead this control provides user experience similar to the web browsers
 * with tabbing support. Actually the control was designed after the successful
 * user experience provide by modern browsers ("tabbed browsing").
 *
 * The control is very similar to the standard tab control from
 * @c COMCTL32.DLL, both visually and from developer's point of view.
 * There two main differences:
 * - @c MC_WC_MDITAB does not have the main body for contents of the tab;
 *   i.e. the contents of the tab is not really rendered in child window of
 *   the @c MC_WC_MDITAB control.
 * - The control also provides few auxiliary buttons on it. They might be
 *   invisible depending on the control style and internal state. There is
 *   a button to close the current tab, to show pop-up menu of all tabs
 *   and finally buttons scrolling the tabs to left or right if there are too
 *   many.
 *
 * Styles, messages and notifications the control supports mostly correspond
 * to subset of messages and styles of the standard tab control. They even
 * usually have the same names (differing only in prefix of the identifiers).
 *
 * So if you are familiar with the standard tab control, you should be able
 * to adopt @c MC_WC_MDITAB very quickly. However please note that the messages
 * and styles are not interchangeable: The constants of styles and messages
 * differ in their values.
 *
 *
 * @section mditab_mdi_migration Migration from MDI
 *
 * Although the purpose of the control is to provide a replacement for the MDI,
 * the programmatic interfaces substantially differs. If you want to migrate
 * your application from MDI to the MDI tab control, expect it will take some
 * time and even philosophy how the application should manage the opened
 * documents:
 *
 * - In MDI, the child MDI windows can be minimized or restored so they
 *   would not cover whole MDI client window. @c MC_WC_MDITAB control does
 *   not provide any replacement for this (anyway only very few users rarely
 *   used this feature of MDI). If your application needs to allow access
 *   to multiple documents simultaneously, you need to provide that in other
 *   way with the @c MC_WC_MDITAB (e.g. to allow having multiple top level
 *   windows, each with the @c MC_WC_MDITAB to manage the documents open in
 *   each particular window).
 *
 * - MDI absolutely expects that the application has its sub-menu Window, with
 *   all the commands like Tile horizontally or vertically, or too select
 *   another MDI document. @c MC_WC_MDITAB control does not expect that
 *   (still you are free to implement any menu you like ;-)
 *
 *
 * @section mditab_callbacks Item Callbacks
 *
 * The control can be told to ask parent instead of remembering some attributes
 * of item.
 *
 * To use the callbacks, you can set item texts to @ref MC_LPSTR_TEXTCALLBACK,
 * and/or images to @ref MC_I_IMAGECALLBACK.
 *
 * Whenever the control needs to paint the item, it then sends notification
 * @ref MC_MTN_GETDISPINFO with @c dwMask specifying what members of it the
 * application has to fill.
 *
 *
 * @section mditab_wdm MDI Tab Control and Desktop Window Manager
 *
 * Since Windows Vista, it is possible to extend window frame into window
 * client and in specific cases it can provide much nicer visual effect.
 *
 * @image html mditab.png
 *
 * To take use of this feature with the MDI tab control, use the style
 * @ref MC_MTS_EXTENDWINDOWFRAME. When the control has this style (and
 * DWM is available and DWM composition is enabled as of the function
 * @c DwmIsCompositionEnabled()), the control extends the top level window
 * frame so that the upper border of it reaches as far as the bottom of the
 * MDI tab control.
 *
 * However note that when using the style, the application should also call
 * function @ref mcMditab_DefWindowProc() from its main window procedure.
 *
 *
 * @section mditab_std_msgs Standard Messages
 *
 * These standard messages are handled by the control:
 * - @c WM_DWMCOMPOSITIONCHANGED (see @ref mditab_wdm)
 * - @c WM_GETFONT
 * - @c WM_SETFONT
 * - @c WM_SETREDRAW
 * - @c CCM_GETUNICODEFORMAT
 * - @c CCM_SETNOTIFYWINDOW
 * - @c CCM_SETUNICODEFORMAT
 * - @c CCM_SETWINDOWTHEME
 *
 * These standard notifications are sent by the control:
 * - @c NM_OUTOFMEMORY
 * - @c NM_RELEASEDCAPTURE
 */


/**
 * @name Initialization Functions
 */
/*@{*/

/**
 * Registers window class of the control.
 * @return @c TRUE on success, @c FALSE on failure.
 */
BOOL MCTRL_API mcMditab_Initialize(void);

/**
 * Unregisters window class of the control.
 */
void MCTRL_API mcMditab_Terminate(void);

/*@}*/


/**
 * @name Other Functions
 */
/*@{*/

/**
 * Application should call this message from its main window procedure when
 * it uses MDI tab control with the style @ref MC_MTS_EXTENDWINDOWFRAME.
 *
 * @param hwndMain Handle of the main window hosting the MDI tab control.
 * @param hwndMditab Handle of the MDI tab control.
 * @param uMsg Message code.
 * @param wParam Message @c WPARAM parameter.
 * @param lParam Message @c LPARAM parameter.
 * @param[out] plResult Result of the message processing the application should
 * return from the window procedure if the functions returns @c TRUE.
 * @returns @c TRUE if the function processed the message, @c FALSE if it did
 * not and the application should handle it on its own (or call @c DefWindowProc()).
 *
 * Thus the typical window procedure using this function looks like this
 * snippet of code:
 *
 * @code
 * LRESULT AppWndProc(HWND hwndMain, UINT uMsg, WPARAM wParam, LPARAM lParam)
 * {
 *     LRESULT lResult;
 *
 *     // Give mcMditab_DefWindowProc() the first chance to handle the message
 *     // and if it handles it, return the result of its processing.
 *     if(mcMditab_DefWindowProc(hwndMain, hwndMditab, uMsg, wParam, lParam, &lResult))
 *         return lResult;
 *
 *     switch(uMsg) {
 *         // Normal message handling as in ordinary window procedure.
 *         ...
 *
 *         // Pass unhandled messages to DefWindowProc().
 *         default:
 *             return DefWindowProc(hwndMain, uMsg, wParam, lParam);
 *     }
 *
 * }
 * @endcode
 */
BOOL MCTRL_API mcMditab_DefWindowProc(HWND hwndMain, HWND hwndMditab, UINT uMsg,
                WPARAM wParam, LPARAM lParam, LRESULT* plResult);

/*@}*/


/**
 * @name Window Class
 */
/*@{*/

/** Window class name (Unicode variant). */
#define MC_WC_MDITABW        L"mCtrl.mditab"
/** Window class name (ANSI variant). */
#define MC_WC_MDITABA         "mCtrl.mditab"

/*@}*/


/**
 * @name Control Styles
 */
/*@{*/

/** @brief Show close button on right side of the control. This is default. */
#define MC_MTS_CBONTOOLBAR           0x0000
/** @brief Not supported, reserved for future use. */
#define MC_MTS_CBONEACHTAB           0x0001
/** @brief Not supported, reserved for future use. */
#define MC_MTS_CBONACTIVETAB         0x0002
/** @brief Don't show close button */
#define MC_MTS_CBNONE                0x0003
/** @brief This is not valid style, its bit-mask of @c MC_MTS_CBxxx styles. */
#define MC_MTS_CBMASK                0x0003

/** @brief Popup tab list button is shown always. This is default. */
#define MC_MTS_TLBALWAYS             0x0000
/** @brief Popup tab list button is shown if scrolling is triggered on. */
#define MC_MTS_TLBONSCROLL           0x0004
/** @brief Popup tab list button is never displayed. */
#define MC_MTS_TLBNEVER              0x0008
/** @brief This is not valid style, but bit-mask of @c MC_NTS_TLBxxx styles. */
#define MC_MTS_TLBMASK               0x000C

/** @brief Always shows scrolling buttons. */
#define MC_MTS_SCROLLALWAYS          0x0010

/** @brief Middle click closes a tab. */
#define MC_MTS_CLOSEONMCLICK         0x0020

/** @brief Mouse button down gains focus. */
#define MC_MTS_FOCUSONBUTTONDOWN     0x0040
/** @brief Never gains focus */
#define MC_MTS_FOCUSNEVER            0x0080
/** @brief This is not valid style, but bit-mask of @c MC_NTS_FOCUSxxx styles. */
#define MC_MTS_FOCUSMASK             0x00C0

/** @brief Enable painting with double buffering.
 *  @details It prevents flickering when the control is being continuously
 *  resized. */
#define MC_MTS_DOUBLEBUFFER          0x0100

/**
 * @brief Allow animation.
 * @details Some operations, like scrolling to left or right and insertion
 * or removal of items, are animated when this style is set.
 */
#define MC_MTS_ANIMATE               0x0200

/**
 * @brief Extend top window frame down to the bottom of the tab control.
 *
 * @details Note this style is ignored on older Windows or when DWM composition
 * is disabled (when @c DwmIsCompositionEnabled() returns @c FALSE).
 *
 * @note When the style is used, the Application should forward the message
 * @c WM_DWMCOMPOSITIONCHANGED from top level window procedure to the control.
 */
#define MC_MTS_EXTENDWINDOWFRAME     0x0400

/**
 * @brief Disables a tooltip window.
 *
 * When having a tooltip window associated, the control uses the tooltip to
 * show additional information about the pointed item. By default the control
 * creates its own control when this style is not set.
 *
 * @sa MC_MTM_SETTOOLTIPS
 */
#define MC_MTS_NOTOOLTIPS            0x0800

/**
 * @brief Allow drag-and-drop reordering of control items.
 */
#define MC_MTS_DRAGDROP              0x1000

/*@}*/


/**
 * @anchor MC_MTIF_xxxx
 * @name MC_MTITEM::dwMask Bits
 */
/*@{*/

/** @brief @ref MC_MTITEMW::pszText or @ref MC_MTITEMA::pszText is valid. */
#define MC_MTIF_TEXT         (1 << 0)
/** @brief @ref MC_MTITEMW::iImage or @ref MC_MTITEMA::iImage is valid. */
#define MC_MTIF_IMAGE        (1 << 1)
/** @brief @ref MC_MTITEMW::lParam or @ref MC_MTITEMA::lParam is valid. */
#define MC_MTIF_PARAM        (1 << 2)

/*@}*/


/**
 * @anchor MC_MTHT_xxxx
 * @name MC_MTHITTESTINFO::flags bits
 */
/*@{*/

/** @brief The hit test coordinates are outside of any tabs. */
#define MC_MTHT_NOWHERE              (1 << 0)
/** @brief The coordinates hit the tab on its icon. */
#define MC_MTHT_ONITEMICON           (1 << 1)
/** @brief The coordinates hit the tab, but its icon or close button. */
#define MC_MTHT_ONITEMLABEL          (1 << 2)
/** @brief The coordinates hit the tab on its close button. */
#define MC_MTHT_ONITEMCLOSEBUTTON    (1 << 3)
/** @brief The coordinates hit the tab anywhere in its rectangle. */
#define MC_MTHT_ONITEM                                                        \
        (MC_MTHT_ONITEMICON | MC_MTHT_ONITEMLABEL | MC_MTHT_ONITEMCLOSEBUTTON)
/** @brief The coordinates hit the auxiliary button for scrolling to the left. */
#define MC_MTHT_ONLEFTSCROLLBUTTON   (1 << 4)
/** @brief The coordinates hit the auxiliary button for scrolling to the right. */
#define MC_MTHT_ONRIGHTSCROLLBUTTON  (1 << 5)
/** @brief The coordinates hit the auxiliary button for listing all items. */
#define MC_MTHT_ONLISTBUTTON         (1 << 6)
/** @brief The coordinates hit the auxiliary button for closing current item. */
#define MC_MTHT_ONCLOSEBUTTON        (1 << 7)
/** @brief The coordinates hit any auxiliary button. */
#define MC_MTHT_ONBUTTON                                                      \
        (MC_MTHT_ONLEFTSCROLLBUTTON | MC_MTHT_ONRIGHTSCROLLBUTTON |           \
         MC_MTHT_ONLISTBUTTON | MC_MTHT_ONCLOSEBUTTON)
/** @brief Above the client area. */
#define MC_MTHT_ABOVE                (1 << 8)
/** @brief Below the client area. */
#define MC_MTHT_BELOW                (1 << 9)
/** @brief To right of the client area. */
#define MC_MTHT_TORIGHT              (1 << 10)
/** @brief To left of the client area. */
#define MC_MTHT_TOLEFT               (1 << 11)

/*@}*/


/**
 * Structures
 */
/*@{*/

/**
 * @brief Structure for manipulating with the tab item (Unicode variant).
 * @sa MC_MTM_INSERTITEM MC_MTM_SETITEM MC_MTM_GETITEM
 */
typedef struct MC_MTITEMW_tag {
    /** Bit mask indicating which members of the structure are valid.
     *  See @ref MC_MTIF_xxxx. */
    DWORD dwMask;
    /** Text label of the tab. */
    LPWSTR pszText;
    /** Number of characters in @c pszText. Used only on output. */
    int cchTextMax;
    /** Index into control image list.
     *  Set to @ref MC_I_IMAGENONE if no image is associated with the item. */
    int iImage;
    /** User data. */
    LPARAM lParam;
} MC_MTITEMW;

/**
 * @brief Structure for manipulating with the tab item (ANSI variant).
 * @sa MC_MTM_INSERTITEM MC_MTM_SETITEM MC_MTM_GETITEM
 */
typedef struct MC_MTITEMA_tag {
    /** Bit mask indicating which members of the structure are valid.
     *  See @ref MC_MTIF_xxxx. */
    DWORD dwMask;
    /** Text label of the tab. */
    LPSTR pszText;
    /** Number of characters in @c psxText. Used only on output. */
    int cchTextMax;
    /** Index into control image list.
     *  Set to @ref MC_I_IMAGENONE if no image is associated with the item. */
    int iImage;
    /** User data. */
    LPARAM lParam;
} MC_MTITEMA;

/**
 * @brief Structure for messages @ref MC_MTM_SETITEMWIDTH and @ref MC_MTM_GETITEMWIDTH.
 *
 * The structure describes policy how the control manages width of the items.
 * Normally the width of the item is determined with the default width.
 *
 * However if there are too many items to be displayed, the control may
 * shrink the items in order to show more of them to minimize need for
 * scrolling. The minimal width specifies how much the items may be shrank.
 */
typedef struct MC_MTITEMWIDTH_tag {
    /** The default item width. If set to zero, default width of each item
     *  depends on its label and icon. If set to non-zero then all items have
     *  the same width, in pixels. */
    DWORD dwDefWidth;
    /** The minimal item width. If set to zero, the items are never shrank.
     *  If set to non-zero, the value specifies the minimal width of all
     *  items. */
    DWORD dwMinWidth;
} MC_MTITEMWIDTH;

/**
 * @brief Structure for message @ref MC_MTM_HITTEST.
 */
typedef struct MC_MTHITTESTINFO_tag {
    /** Coordinates to test. */
    POINT pt;
    /** On output, set to the result of the test. */
    UINT flags;
} MC_MTHITTESTINFO;

/**
 * @brief Structure for notification @ref MC_MTN_SELCHANGE.
 */
typedef struct MC_NMMTSELCHANGE_tag {
    /** Standard notification structure header. */
    NMHDR hdr;
    /** Index of previously selected tab. */
    int iItemOld;
    /** Data of previously selected tab, or zero. */
    LPARAM lParamOld;
    /** Index of newly selected tab */
    int iItemNew;
    /** Data of newly selected tab, or zero. */
    LPARAM lParamNew;
} MC_NMMTSELCHANGE;

/**
 * @brief Structure for notification @ref MC_MTN_DELETEITEM.
 */
typedef struct MC_NMMTDELETEITEM_tag {
    /** Standard notification structure header. */
    NMHDR hdr;
    /** Index of the item being deleted. */
    int iItem;
    /** User data of the item being deleted. */
    LPARAM lParam;
} MC_NMMTDELETEITEM;


/**
 * @brief Structure for notification @ref MC_MTN_CLOSEITEM.
 */
typedef struct MC_NMMTCLOSEITEM_tag {
    /** Standard notification structure header. */
    NMHDR hdr;
    /** Index of the item being closed. */
    int iItem;
    /** User data of the item being closed. */
    LPARAM lParam;
} MC_NMMTCLOSEITEM;

/**
 * @brief Structure used by notification @ref MC_MTN_GETDISPINFO
 * (Unicode variant).
 */
typedef struct MC_NMMTDISPINFOW_tag {
    /** Common notification structure header. */
    NMHDR hdr;
    /** Item index. */
    UINT iItem;
    /** Structure describing the contents of the cell. */
    MC_MTITEMW item;
} MC_NMMTDISPINFOW;

/**
 * @brief Structure used by notification @ref MC_MTN_GETDISPINFO
 * (ANSI variant).
 */
typedef struct MC_NMMTDISPINFOA_tag {
    /** Common notification structure header. */
    NMHDR hdr;
    /** Item index. */
    UINT iItem;
    /** Structure describing the contents of the cell. */
    MC_MTITEMA item;
} MC_NMMTDISPINFOA;

/*@}*/


/**
 * @name Control Messages
 */
/*@{*/

/**
 * @brief Gets count of tabs.
 * @param wParam Reserved, set to zero.
 * @param lParam Reserved, set to zero.
 * @return (@c int) Count of tabs.
 */
#define MC_MTM_GETITEMCOUNT       (MC_MTM_FIRST + 0)

/**
 * @brief Gets image-list.
 * @param wParam Reserved, set to zero.
 * @param lParam Reserved, set to zero.
 * @return (@c HIMAGELIST) The image list, or @c NULL.
 *
 * @sa MC_MTM_SETIMAGELIST
 */
#define MC_MTM_GETIMAGELIST       (MC_MTM_FIRST + 1)

/**
 * @brief Sets image-list.
 *
 * The tab items can refer to the images in the list with @c MC_MTITEM::iImage.
 * @param wParam Reserved, set to zero.
 * @param[in] lParam (@c HIMAGELIST) The image-list.
 * @return (@c HIMAGELIST) Old image list, or @c NULL.
 *
 * @sa MC_MTM_GETIMAGELIST
 */
#define MC_MTM_SETIMAGELIST       (MC_MTM_FIRST + 2)

/**
 * @brief Delete all tab items.
 *
 * The control sends @ref MC_MTN_DELETEALLITEMS notification.
 * Depending on the return value from the notifications, it may also send
 * notification @ref MC_MTN_DELETEITEM for each tab being deleted.
 * @param wParam Reserved, set to zero.
 * @param lParam Reserved, set to zero.
 * @return (@c BOOL) @c TRUE on success, @c FALSE otherwise.
 *
 * @sa MC_MTM_DELETEITEM
 */
#define MC_MTM_DELETEALLITEMS     (MC_MTM_FIRST + 3)

/**
 * @brief Inserts new tab into the tab control (Unicode variant).
 *
 * @param[in] wParam (@c int) Index of the new item.
 * @param[in] lParam (@ref MC_MTITEM*) Pointer to detailed data of the new
 * tab.
 * @return (@c int) index of the new tab, or @c -1 on failure.
 */
#define MC_MTM_INSERTITEMW        (MC_MTM_FIRST + 4)

/**
 * @brief Inserts new tab into the tab control (ANSI variant).
 * @param[in] wParam (@c int) Index of the new item.
 * @param[in] lParam (@ref MC_MTITEM*) Pointer to detailed data of the new
 * tab.
 * @return (@c int) index of the new tab, or @c -1 on failure.
 */
#define MC_MTM_INSERTITEMA        (MC_MTM_FIRST + 5)

/**
 * @brief Sets tab in the tab control (Unicode variant).
 * @param[in] wParam (@c int) Index of the item.
 * @param[in] lParam (@ref MC_MTITEMW*) Pointer to detailed data of the tab.
 * @return (@c BOOL) @c TRUE on success, @c FALSE otherwise.
 */
#define MC_MTM_SETITEMW           (MC_MTM_FIRST + 6)

/**
 * @brief Sets tab in the tab control (ANSI variant).
 * @param[in] wParam (@c int) Index of the item.
 * @param[in] lParam (@ref MC_MTITEMA*) Pointer to detailed data of the tab.
 * @return (@c BOOL) @c TRUE on success, @c FALSE otherwise.
 */
#define MC_MTM_SETITEMA           (MC_MTM_FIRST + 7)

/**
 * @brief Gets tab data from the tab control (Unicode variant).
 *
 * Application has to set @c MC_MTITEM::dwMask prior sending the message to
 * indicate what attributes of the item to retrieve. If the application uses
 * @c MC_MTIF_TEXT, then it also has to set @c MC_MTITEM::pszText to point
 * to a buffer where the text will be stored and set @c MC_MTITEM::cchTextMax
 * to specify size of the buffer.
 *
 * @param[in] wParam (@c int) Index of the item.
 * @param[out] lParam (@ref MC_MTITEMW*) Pointer to detailed data of the
 * tab, receiving the data according to @c MC_MTITEM::dwMask.
 * @return (@c BOOL) @c TRUE on success, @c FALSE otherwise.
 */
#define MC_MTM_GETITEMW           (MC_MTM_FIRST + 8)

/**
 * @brief Gets tab data from the tab control (ANSI variant).
 *
 * Application has to set @c MC_MTITEM::dwMask prior sending the message to
 * indicate what attributes of the item to retrieve. If the application uses
 * @c MC_MTIF_TEXT, then it also has to set @c MC_MTITEM::pszText to point
 * to a buffer where the text will be stored and set @c MC_MTITEM::cchTextMax
 * to specify size of the buffer.
 *
 * @param[in] wParam (@c int) Index of the item.
 * @param[in,out] lParam (@ref MC_MTITEMA*) Pointer to detailed data of the
 * tab, receiving the data according to @c MC_MTITEM::dwMask.
 * @return (@c BOOL) @c TRUE on success, @c FALSE otherwise.
 */
#define MC_MTM_GETITEMA           (MC_MTM_FIRST + 9)

/**
 * @brief Deletes the item.
 *
 * Sends @ref MC_MTN_DELETEITEM notification to parent window.
 * @param[in] wParam (@c int) Index of tab to be deleted.
 * @param lParam Reserved, set to zero.
 * @return (@c BOOL) @c TRUE on success, @c FALSE otherwise.
 */
#define MC_MTM_DELETEITEM         (MC_MTM_FIRST + 10)

/**
 * @brief Tests which tab (and its part) is placed on specified position.
 * @param wParam Reserved, set to zero.
 * @param[in,out] lParam (@ref MC_MTHITTESTINFO*) Pointer to a hit test
 * structure. Set @ref MC_MTHITTESTINFO::pt on input.
 * @return (@c int) Index of the hit tab, or -1.
 */
#define MC_MTM_HITTEST            (MC_MTM_FIRST + 11)

/**
 * @brief Selects a tab.
 * @param[in] wParam (@c int) Index of the tab to select.
 * @param lParam Reserved, set to zero.
 * @return (@c int) Index of previously selected tab, or @c -1.
 */
#define MC_MTM_SETCURSEL          (MC_MTM_FIRST + 12)

/**
 * @brief Gets index of selected tab.
 * @param wParam Reserved, set to zero.
 * @param lParam Reserved, set to zero.
 * @return (@c int) Index of selected tab, or @c -1.
 */
#define MC_MTM_GETCURSEL          (MC_MTM_FIRST + 13)

/**
 * @brief Asks to close item.
 *
 * It causes to send @ref MC_MTN_CLOSEITEM notification and depending on its
 * return value it then can cause deleting the item.
 * @param[in] wParam (@c int) Index of the item to be closed.
 * @param lParam Reserved, set to zero.
 * @return (@c BOOL) @c TRUE on success, @c FALSE otherwise.
 */
#define MC_MTM_CLOSEITEM          (MC_MTM_FIRST + 14)

/**
 * @brief Sets default and minimal width for each tab.
 *
 * If there is enough space, all tabs have the default width. When there are
 * too many widths, they are made narrower so more tabs fit into the visible
 * space area, but never narrower then the minimal width.
 * @param wParam Reserved, set to zero.
 * @param[in] lParam (@ref MC_MTITEMWIDTH*) Pointer to a structure specifying
 * the default and minimal widths. When @c NULL is passed, the values are
 * reset to built-in defaults.
 * @return (@c BOOL) @c TRUE on success, @c FALSE otherwise.
 * @sa MC_MTM_GETITEMWIDTH
 */
#define MC_MTM_SETITEMWIDTH       (MC_MTM_FIRST + 15)

/**
 * @brief Gets default and minimal width for each tab.
 * @param wParam Reserved, set to zero.
 * @param[out] lParam (@ref MC_MTITEMWIDTH*) Pointer to a structure where the
 * current widths will be set.
 * @return (@c BOOL) @c TRUE on success, @c FALSE otherwise.
 * @sa MC_MTM_SETITEMWIDTH
 */
#define MC_MTM_GETITEMWIDTH       (MC_MTM_FIRST + 16)

/**
 * @brief Preallocate enough memory for requested number of items.
 *
 * You may want to use this message before adding higher number of items
 * into the controls to speed it up by avoiding multiple reallocations.
 * @param[in] wParam (@c UINT) The number of items to add.
 * @param lParam Reserved, set to zero.
 * @return (@c BOOL) @c TRUE on success, @c FALSE otherwise.
 */
#define MC_MTM_INITSTORAGE        (MC_MTM_FIRST + 17)

/**
 * @brief Get item rectangle.
 * @details The shape of items is curved so the returned rectangle is only
 * approximation of its geometry.
 * @param[in] wParam (@c DWORD) Low word specifies index of the item. High word
 * specifies whether whole rectangle (non-zero) or only visible part (zero)
 * is requested.
 * @param[out] lParam (@c RECT*) Pointer to rectangle.
 * @return (@c BOOL) @c TRUE on success, @c FALSE otherwise.
 */
#define MC_MTM_GETITEMRECT        (MC_MTM_FIRST + 18)

/**
 * @brief Ensure the item is visible.
 * @details If not visible, the control scrolls to make it visible.
 * @param[in] wParam (@c int) Index of the item.
 * @param lParam Reserved, set to zero.
 * @return (@c BOOL) @c TRUE on success, @c FALSE otherwise.
 */
#define MC_MTM_ENSUREVISIBLE      (MC_MTM_FIRST + 19)

/**
 * @brief Associate a tooltip window with the control.
 * @param[in] wParam (@c HWND) Handle of the tooltip window.
 * @param lParam Reserved, set to zero.
 * @return (@c HWND) Handle of previous tooltip window or @c NULL if no tooltip
 * was associated with the control.
 * @sa MC_MTS_NOTOOLTIPS
 */
#define MC_MTM_SETTOOLTIPS        (MC_MTM_FIRST + 20)

/**
 * @brief Get tooltip associated with the control.
 * @param wParam Reserved, set to zero.
 * @param lParam Reserved, set to zero.
 * @return (@c HWND) Handle of the tooltip window or @c NULL if no tooltip
 * is associated with the control.
 */
#define MC_MTM_GETTOOLTIPS        (MC_MTM_FIRST + 21)

/**
 * @brief Cancel currently ongoing drag-and-drop operation.
 * @param wParam Reserved, set to zero.
 * @param lParam Reserved, set to zero.
 * @return (@c BOOL) @c TRUE on success, @c FALSE otherwise (e.g. if no
 * drag-and-drop operation is currently in progress).
 * @sa mditab_drag_and_drop
 */
#define MC_MTM_CANCELDRAGITEM     (MC_MTM_FIRST + 22)

/*@}*/


/**
 * @name Control Notifications
 */
/*@{*/

/**
 * @brief Fired when other tab has been selected.
 * @param[in] wParam (@c int) Id of the control sending the notification.
 * @param[in] lParam (@ref MC_NMMTSELCHANGE*) Pointer to a structure specifying
 * details about the selection change.
 * @return Application should return zero, if it processes the message.
 */
#define MC_MTN_SELCHANGE          (MC_MTN_FIRST + 0)

/**
 * @brief Fired when a tab is being deleted.
 * @param[in] wParam (@c int) Id of the control sending the notification.
 * @param[in] lParam (@ref MC_NMMTDELETEITEM*) Pointer to a structure
 * specifying details about the item being deleted.
 * @return Application should return zero if it processes the notification.
 */
#define MC_MTN_DELETEITEM         (MC_MTN_FIRST + 1)

/**
 * @brief Fired when control processes @ref MC_MTM_DELETEALLITEMS message or
 * when it is being destroyed.
 *
 * Depending on the value returned from the notification, calling
 * @ref MC_MTN_DELETEITEM notifications for all the items can be suppressed.
 * @param[in] wParam (@c int) Id of the control sending the notification.
 * @param[in] lParam (@c NMHDR*)
 * @return Application should return @c FALSE to receive subsequent
 * @ref MC_MTN_DELETEITEM for each item; or @c TRUE to suppress sending them.
 */
#define MC_MTN_DELETEALLITEMS     (MC_MTN_FIRST + 2)

/**
 * @brief Fired when user requests closing a tab item.
 * @param[in] wParam (@c int) Id of the control sending the notification.
 * @param[in] lParam (@ref MC_NMMTCLOSEITEM*) Pointer to a structure specifying
 * details about the item being closed.
 * @return Application should return @c FALSE to remove the tab (the tab is
 * then deleted and @ref MC_MTN_DELETEITEM notification is sent); or @c TRUE
 * to cancel the tab closure.
 */
#define MC_MTN_CLOSEITEM          (MC_MTN_FIRST + 3)

/**
 * @brief Fired when control needs to retrieve some item data, the parent holds
 * (Unicode variant).
 *
 * This may happen when @c MC_MTITEM::pszText was to to the magical value
 * @ref MC_LPSTR_TEXTCALLBACK, or @c MC_MTITEM::iImage was set to the magical
 * value @ref MC_I_IMAGECALLBACK.
 *
 * When sending the notification, the control sets @c MC_NMMTDISPINFO::iItem
 * to identify the desired item. The control also sets
 * @c MC_NMMTDISPINFO::item::lParam.
 *
 * The control specifies what members in @c MC_NMMTDISPINFO::item the
 * application should fill with the @c MC_NMMTDISPINFO::item::dwMask.
 *
 * @param[in] wParam (@c int) Id of the control sending the notification.
 * @param[in,out] lParam (@ref MC_NMMTDISPINFO*) Pointer to @ref MC_NMMTDISPINFO
 * structure.
 * @return None.
 */
#define MC_MTN_GETDISPINFOW       (MC_MTN_FIRST + 4)

/**
 * @brief Fired when control needs to retrieve some item data, the parent holds
 * (ANSI variant).
 *
 * This may happen when @c MC_MTITEM::pszText was to to the magical value
 * @ref MC_LPSTR_TEXTCALLBACK, or @c MC_MTITEM::iImage was set to the magical
 * value @ref MC_I_IMAGECALLBACK.
 *
 * When sending the notification, the control sets @c MC_NMMTDISPINFO::iItem
 * to identify the desired item. The control also sets
 * @c MC_NMMTDISPINFO::item::lParam.
 *
 * The control specifies what members in @c MC_NMMTDISPINFO::item the
 * application should fill with the @c MC_NMMTDISPINFO::item::dwMask.
 *
 * @param[in] wParam (@c int) Id of the control sending the notification.
 * @param[in,out] lParam (@ref MC_NMMTDISPINFO*) Pointer to @ref MC_NMMTDISPINFO
 * structure.
 * @return None.
 */
#define MC_MTN_GETDISPINFOA       (MC_MTN_FIRST + 5)

/*@}*/


/**
 * @name Unicode Resolution
 */
/*@{*/

/** Unicode-resolution alias. @sa MC_WC_MDITABW MC_WC_MDITABA */
#define MC_WC_MDITAB          MCTRL_NAME_AW(MC_WC_MDITAB)
/** Unicode-resolution alias. @sa MC_MTITEMW MC_MTITEMA */
#define MC_MTITEM             MCTRL_NAME_AW(MC_MTITEM)
/** Unicode-resolution alias. @sa MC_MTM_INSERTITEMW MC_MTM_INSERTITEMA */
#define MC_MTM_INSERTITEM     MCTRL_NAME_AW(MC_MTM_INSERTITEM)
/** Unicode-resolution alias. @sa MC_MTM_SETITEMW MC_MTM_SETITEMA */
#define MC_MTM_SETITEM        MCTRL_NAME_AW(MC_MTM_SETITEM)
/** Unicode-resolution alias. @sa MC_MTM_GETITEMW MC_MTM_GETITEMA */
#define MC_MTM_GETITEM        MCTRL_NAME_AW(MC_MTM_GETITEM)
/** Unicode-resolution alias. @sa MC_MTN_GETDISPINFOW MC_MTN_GETDISPINFOA */
#define MC_MTN_GETDISPINFO    MCTRL_NAME_AW(MC_MTN_GETDISPINFO)
/** Unicode-resolution alias. @sa MC_NMMTDISPINFOW MC_NMMTDISPINFOA */
#define MC_NMMTDISPINFO       MCTRL_NAME_AW(MC_NMMTDISPINFO)

/*@}*/


#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif  /* MCTRL_MDITAB_H */

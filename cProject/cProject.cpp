// cProject.cpp : Defines the entry point for the application.
#include <windows.h>
#include <tchar.h>
#include <CommCtrl.h>
#include <mshtmhst.h>

#pragma comment (lib, "comctl32.lib")

/* The base address of the module in which the code is running. */
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
/* Instance handle of the current module. */
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)

// Submenu IDs constants
inline constexpr int SUBMENU1_ID[] = { 10001, 10002, 10003, 10004 };
inline constexpr int SUBMENU2_ID[] = { 10010, 10020, 10030, 10040 };
inline constexpr int SUBMENU3_ID[] = { 10100, 10200, 10300, 10400 };
inline constexpr int SUBMENU4_ID[] = { 11000, 12000, 13000, 14000 };

inline constexpr UINT_PTR ID_LISTBOX = 101;

/* Creating submenus function */
void submenuAppend(HMENU& submenu, const int SUBMENU_ID[], const wchar_t SUBMENU_NAME[4][10]);

/* Creating main menus function */
template <typename T>
void mainmenuAppend(HMENU& mainmenu, HMENU submenus[], T& separator);

/* Functions which handles different menu item IDs and invokes submenus item creations */
void switchID1(HWND& g_hSubMenuWindow, int menuItemID);
void switchID2(HWND& g_hSubMenuWindow, int menuItemID);
void switchID3(HWND& g_hSubMenuWindow, int menuItemID);
void switchID4(HWND& g_hSubMenuWindow, int menuItemID);

/* Submenu elements creation functions */
void case_2(HWND& g_hSubMenuWindow);
void case_3(HWND& g_hSubMenuWindow);
void case_4(HWND& g_hSubMenuWindow);

// Window Procedure callback function
static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Entry point for the Windows application
_Use_decl_annotations_ int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    // Window class registration
    const TCHAR* CLASS_NAME = _T("Application");
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    // Window creation
    HWND hwnd = CreateWindowEx(0, CLASS_NAME, _T("App"), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        nullptr, nullptr, hInstance, nullptr);

    if (!hwnd)
        return 0;

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}


static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {

            HMENU mainmenu = CreatePopupMenu();
            HMENU submenu1, submenu2, submenu3, submenu4;

            HMENU submenus[] = { submenu1 = CreatePopupMenu(),
                                 submenu2 = CreatePopupMenu(), 
                                 submenu3 = CreatePopupMenu(),
                                 submenu4 = CreatePopupMenu()
            };

            // Menu separator lambda
            auto separator = [&mainmenu] {
                return AppendMenu(mainmenu, MF_SEPARATOR, 0, nullptr);
            };

            const wchar_t SUBMENU_NAME[4][10] = {
                L"submenu 1",
                L"submenu 2",
                L"submenu 3",
                L"submenu 4"
            };

            // Submenus creation
            submenuAppend(submenus[0], SUBMENU1_ID, SUBMENU_NAME);
            submenuAppend(submenus[1], SUBMENU2_ID, SUBMENU_NAME);
            submenuAppend(submenus[2], SUBMENU3_ID, SUBMENU_NAME);
            submenuAppend(submenus[3], SUBMENU4_ID, SUBMENU_NAME);

            // Mainmenus creation
            mainmenuAppend(mainmenu, submenus, separator);

            // Cursor position
            POINT p;
            GetCursorPos(&p);
            TrackPopupMenu(mainmenu, TPM_LEFTBUTTON, p.x, p.y, 0, hwnd, 0);
            break;
        }
        case WM_COMMAND: {
            // Parental window handle
            HWND g_hSubMenuWindow = CreateWindowEx(0, _T("STATIC"), L"Default Menu",
                WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
                nullptr, nullptr, nullptr, nullptr);

            // IDs for the toolbar button
            constexpr int ID_FILE_NEW = 3000;
            constexpr int ID_FILE_OPEN = 3001;
            constexpr int ID_FILE_SAVE = 3002;
            constexpr int ID_EDIT_CUT = 3003;
            constexpr int ID_EDIT_COPY = 3004;
            constexpr int ID_EDIT_PASTE = 3005;
            constexpr int ID_FILE_PRINT = 3006;
            constexpr int ID_HELP_ABOUT = 3007;

            if (HIWORD(wParam) == 0 && lParam == 0) {
                int menuItemID = LOWORD(wParam);

            //     Check which submenu item is selected and create a new window accordingly
                if (menuItemID >= SUBMENU1_ID[0] && menuItemID <= SUBMENU1_ID[3])
                    switchID1(g_hSubMenuWindow, menuItemID);
                else if (menuItemID >= SUBMENU2_ID[0] && menuItemID <= SUBMENU2_ID[3])
                    switchID2(g_hSubMenuWindow, menuItemID);
                else if (menuItemID >= SUBMENU3_ID[0] && menuItemID <= SUBMENU3_ID[3])
                    switchID3(g_hSubMenuWindow, menuItemID);
                else if (menuItemID >= SUBMENU4_ID[0] && menuItemID <= SUBMENU4_ID[3])
                    switchID4(g_hSubMenuWindow, menuItemID);
            }

            constexpr TBBUTTON tbb[] = {
              { 0, ID_FILE_NEW,  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
              { 1, ID_FILE_OPEN, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
              { 2, ID_FILE_SAVE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
              { 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
              { 3, ID_EDIT_CUT,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
              { 4, ID_EDIT_COPY,  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
              { 5, ID_EDIT_PASTE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
              { 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
              { 6, ID_FILE_PRINT, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
              { 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
              { 7, ID_HELP_ABOUT, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0}
            };

            // Toolbar creation
            HWND g_Toolbar = CreateToolbarEx(g_hSubMenuWindow, WS_CHILD | WS_VISIBLE | CCS_TOP, 1,
                0, HINST_COMMCTRL, IDB_STD_SMALL_COLOR, tbb, 3, 0, 0, 0, 0, sizeof(TBBUTTON));

            ShowWindow(g_hSubMenuWindow, SW_SHOWNORMAL);
            break;
        }
        case WM_DESTROY: {
            // Quit the application
            PostQuitMessage(0);
            break;
        }
        default:
            // Default window procedure for other messages
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    return 0;
}

/* Creating submenus function */
void submenuAppend(HMENU& submenu, const int SUBMENU_ID[], const wchar_t SUBMENU_NAME[4][10]) {
    for (int i{}; i < 4; ++i) 
        AppendMenu(submenu, MF_STRING, SUBMENU_ID[i], SUBMENU_NAME[i]);
}

/* Creating main menus function */
template <typename T>
void mainmenuAppend(HMENU& mainmenu, HMENU submenus[], T& separator) {
    AppendMenu(mainmenu, MF_POPUP, (UINT_PTR)submenus[0], L"&menu1");
    separator();
    AppendMenu(mainmenu, MF_POPUP, (UINT_PTR)submenus[1], L"&menu2");
    separator();
    AppendMenu(mainmenu, MF_POPUP, (UINT_PTR)submenus[2], L"&menu3");
    separator();
    AppendMenu(mainmenu, MF_POPUP, (UINT_PTR)submenus[3], L"&menu4");
}

/* Functions which handles different menu item IDs and invokes submenus item creations */
void switchID1(HWND& g_hSubMenuWindow, int menuItemID) {
    switch (menuItemID) {
        case SUBMENU1_ID[0]: {
            HWND chckBox = CreateWindow(_T("BUTTON"), _T("Checkbox"), BS_AUTOCHECKBOX, CW_USEDEFAULT, CW_USEDEFAULT, 80, 50, g_hSubMenuWindow, nullptr, nullptr, nullptr);
            ShowWindow(chckBox, SW_SHOWNORMAL);
            break;
        }
        case SUBMENU1_ID[1]: {
            case_2(g_hSubMenuWindow);
            break;
        }
        case SUBMENU1_ID[2]: {
            case_3(g_hSubMenuWindow);
            break;
        }
        case SUBMENU1_ID[3]: {
            case_4(g_hSubMenuWindow);
            break;
        }
    }
}
void switchID2(HWND& g_hSubMenuWindow, int menuItemID) {
    switch (menuItemID) {
        case SUBMENU2_ID[0]: {
            HWND chckBox = CreateWindow(_T("BUTTON"), _T("Checkbox"), BS_AUTOCHECKBOX, CW_USEDEFAULT, CW_USEDEFAULT, 80, 50, g_hSubMenuWindow, nullptr, nullptr, nullptr);
            ShowWindow(chckBox, SW_SHOWNORMAL);
            break;
        }
        case SUBMENU2_ID[1]: {
            case_2(g_hSubMenuWindow);
            break;
        }
        case SUBMENU2_ID[2]: {
            case_3(g_hSubMenuWindow);
            break;
        }
        case SUBMENU2_ID[3]: {
            case_4(g_hSubMenuWindow);
            break;
        }
    }
}
void switchID3(HWND& g_hSubMenuWindow, int menuItemID) {
    switch (menuItemID) {
        case SUBMENU3_ID[0]: {
            HWND chckBox = CreateWindow(_T("BUTTON"), _T("Checkbox"), BS_AUTOCHECKBOX, CW_USEDEFAULT, CW_USEDEFAULT, 80, 50, g_hSubMenuWindow, nullptr, nullptr, nullptr);
            ShowWindow(chckBox, SW_SHOWNORMAL);
            break;
        }
        case SUBMENU3_ID[1]: {
            case_2(g_hSubMenuWindow);
            break;
        }
        case SUBMENU3_ID[2]: {
            case_3(g_hSubMenuWindow);
            break;
        }
        case SUBMENU3_ID[3]: {
            case_4(g_hSubMenuWindow);
            break;
        }
    }
}
void switchID4(HWND& g_hSubMenuWindow, int menuItemID) {
    switch (menuItemID) {
        case SUBMENU4_ID[0]: {
            HWND chckBox = CreateWindow(_T("BUTTON"), _T("Checkbox"), BS_AUTOCHECKBOX, CW_USEDEFAULT, CW_USEDEFAULT, 80, 50, g_hSubMenuWindow, nullptr, nullptr, nullptr);
            ShowWindow(chckBox, SW_SHOWNORMAL);
            break;
        }
        case SUBMENU4_ID[1]: {
            case_2(g_hSubMenuWindow);
            break;
        }
        case SUBMENU4_ID[2]: {
            case_3(g_hSubMenuWindow);
            break;
        }
        case SUBMENU4_ID[3]: {
            case_4(g_hSubMenuWindow);
            break;
        }
    }
}

/* Submenu elements creation functions */
void case_2(HWND& g_hSubMenuWindow) {
    constexpr int xpos = 100;            // Horizontal position of the window.
    constexpr int ypos = 100;            // Vertical position of the window.
    constexpr int nwidth = 200;          // Width of the window
    constexpr int nheight = 200;         // Height of the window

    HWND hWndComboBox = CreateWindow(WC_COMBOBOX, TEXT(""),
        CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
        xpos, ypos, nwidth, nheight, g_hSubMenuWindow, nullptr, HINST_THISCOMPONENT,
        nullptr);

    // load the combobox with item list.
    TCHAR Planets[9][10] = {
        TEXT("Mercury"), TEXT("Venus"), TEXT("Earth"), TEXT("Mars"),
        TEXT("Jupiter"), TEXT("Saturn"), TEXT("Uranus"), TEXT("Neptune"),
        TEXT("Pluto")
    };

    TCHAR A[16];
    memset(&A, 0, sizeof(A));
    for (int k{}; k <= 8; ++k) {
        wcscpy_s(A, sizeof(A) / sizeof(TCHAR), (TCHAR*)Planets[k]);
        // Add string to combobox.
        SendMessage(hWndComboBox, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)A);
    }

    // Send the CB_SETCURSEL message to display an initial item in the selection field
    SendMessage(hWndComboBox, CB_SETCURSEL, (WPARAM)2, (LPARAM)0);
}
void case_3(HWND& g_hSubMenuWindow) {
     HWND hList = CreateWindow(_T("ListBox"), _T(""), WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_BORDER | WS_VSCROLL, 40, 40, 250, 60, g_hSubMenuWindow, (HMENU)ID_LISTBOX, nullptr, nullptr);

     SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)"1");
     SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)"2");
     SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)"3");
     SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)"4");
     SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)"5");
}
void case_4(HWND& g_hSubMenuWindow) {
    HWND editCtlHandle = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 100, 200, 20, g_hSubMenuWindow, nullptr, nullptr, nullptr);
}

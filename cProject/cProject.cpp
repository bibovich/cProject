// cProject.cpp : Defines the entry point for the application.
//
#include <windows.h>
#include <tchar.h>
#include <CommCtrl.h>
#include <mshtmhst.h>

#pragma comment (lib, "comctl32.lib")

EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)

inline constexpr int ID_SELF_DESTROY_BUTTON = 100;
inline constexpr UINT_PTR ID_LISTBOX = 101;

inline constexpr int ID_FILE_NEW = 3000;
inline constexpr int ID_FILE_OPEN = 3001;
inline constexpr int ID_FILE_SAVE= 3002;
inline constexpr int ID_EDIT_CUT = 3003;
inline constexpr int ID_EDIT_COPY = 3004;
inline constexpr int ID_EDIT_PASTE = 3005;
inline constexpr int ID_FILE_PRINT = 3006;
inline constexpr int ID_HELP_ABOUT = 3007;


inline constexpr TBBUTTON tbb[] = {
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

template <typename T>
void mainmenuAppend(HMENU& mainmenu, HMENU submenus[], T& separator);

void switchID1(HWND& g_hSubMenuWindow, LPCWSTR& wstr, int menuItemID);
void switchID2(HWND& g_hSubMenuWindow, LPCWSTR& wstr, int menuItemID);
void switchID3(HWND& g_hSubMenuWindow, LPCWSTR& wstr, int menuItemID);
void switchID4(HWND& g_hSubMenuWindow, LPCWSTR& wstr, int menuItemID);


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
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL)
        return 0;

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}


static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE: {
        HMENU mainmenu = CreatePopupMenu();
        auto separator = [&mainmenu] {
            return AppendMenu(mainmenu, MF_SEPARATOR, 0, NULL);
        };

        HMENU submenu1 = CreatePopupMenu();
        AppendMenu(submenu1, MF_STRING, 10001, L"submenu 1");
        AppendMenu(submenu1, MF_STRING, 10002, L"submenu 2");
        AppendMenu(submenu1, MF_STRING, 10003, L"submenu 3");
        AppendMenu(submenu1, MF_STRING, 10004, L"submenu 4");

        HMENU submenu2 = CreatePopupMenu();
        AppendMenu(submenu2, MF_STRING, 10010, L"submenu 1");
        AppendMenu(submenu2, MF_STRING, 10020, L"submenu 2");
        AppendMenu(submenu2, MF_STRING, 10030, L"submenu 3");
        AppendMenu(submenu2, MF_STRING, 10040, L"submenu 4");

        HMENU submenu3 = CreatePopupMenu();
        AppendMenu(submenu3, MF_STRING, 10100, L"submenu 1");
        AppendMenu(submenu3, MF_STRING, 10200, L"submenu 2");
        AppendMenu(submenu3, MF_STRING, 10300, L"submenu 3");
        AppendMenu(submenu3, MF_STRING, 10400, L"submenu 4");

        HMENU submenu4 = CreatePopupMenu();
        AppendMenu(submenu4, MF_STRING, 11000, L"submenu 1");
        AppendMenu(submenu4, MF_STRING, 12000, L"submenu 2");
        AppendMenu(submenu4, MF_STRING, 13000, L"submenu 3");
        AppendMenu(submenu4, MF_STRING, 14000, L"submenu 4");

        HMENU submenus[] = {submenu1, submenu2, submenu3, submenu4};
        mainmenuAppend(mainmenu, submenus, separator);


        POINT p;
        GetCursorPos(&p);
        TrackPopupMenu(mainmenu, TPM_LEFTBUTTON, p.x, p.y, 0, hwnd, 0);
        break;
    }
    case WM_COMMAND: {
        LPCWSTR wstr = L"Default Menu";
        HWND g_hSubMenuWindow = CreateWindowEx(0, _T("STATIC"), wstr,
            WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
            NULL, NULL, NULL, NULL);
        if (HIWORD(wParam) == 0 && lParam == 0) {
            int menuItemID = LOWORD(wParam);

        //     Check which submenu item is selected and create a new window accordingly
            if (menuItemID >= 10001 && menuItemID <= 10004)
                switchID1(g_hSubMenuWindow, wstr, menuItemID);
            else if (menuItemID >= 10010 && menuItemID <= 10040)
                switchID2(g_hSubMenuWindow, wstr, menuItemID);
            else if (menuItemID >= 10100 && menuItemID <= 10400)
                switchID3(g_hSubMenuWindow, wstr, menuItemID);
            else if (menuItemID >= 11000 && menuItemID <= 14000)
                switchID4(g_hSubMenuWindow, wstr, menuItemID);
        }


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



void switchID1(HWND& g_hSubMenuWindow, LPCWSTR& wstr, int menuItemID) {
    switch (menuItemID) {
        case 10001: {
            wstr = L"Menu 1, Submenu 1 Window";
            HWND chckBox = CreateWindow(_T("BUTTON"), _T("Checkbox"), BS_AUTOCHECKBOX, CW_USEDEFAULT, CW_USEDEFAULT, 80, 50, g_hSubMenuWindow, NULL, NULL, NULL);
            ShowWindow(chckBox, SW_SHOWNORMAL);
            break;
        }
        case 10002: {
            wstr = L"Menu 1, Submenu 2 Window";
            case_2(g_hSubMenuWindow);
            break;
        }
        case 10003: {
            wstr = L"Menu 1, Submenu 3 Window";
            case_3(g_hSubMenuWindow);
            break;
        }
        case 10004: {
            wstr = L"Menu 1, Submenu 4 Window";
            case_4(g_hSubMenuWindow);
            break;
        }
    }
}
void switchID2(HWND& g_hSubMenuWindow, LPCWSTR& wstr, int menuItemID) {
    switch (menuItemID) {
        case 10010: {
            wstr = L"Menu 2, Submenu 1 Window";
            HWND chckBox = CreateWindow(_T("BUTTON"), _T("Checkbox"), BS_AUTOCHECKBOX, CW_USEDEFAULT, CW_USEDEFAULT, 80, 50, g_hSubMenuWindow, NULL, NULL, NULL);
            ShowWindow(chckBox, SW_SHOWNORMAL);
            break;
        }
        case 10020: {
            wstr = L"Menu 2, Submenu 2 Window";
            case_2(g_hSubMenuWindow);
            break;
        }
        case 10030: {
            wstr = L"Menu 2, Submenu 3 Window";
            case_3(g_hSubMenuWindow);
            break;
        }
        case 10040: {
            wstr = L"Menu 2, Submenu 4 Window";
            case_4(g_hSubMenuWindow);
            break;
        }
    }
}
void switchID3(HWND& g_hSubMenuWindow, LPCWSTR& wstr, int menuItemID) {
    switch (menuItemID) {
        case 10100: {
            wstr = L"Menu 3, Submenu 1 Window";
            HWND chckBox = CreateWindow(_T("BUTTON"), _T("Checkbox"), BS_AUTOCHECKBOX, CW_USEDEFAULT, CW_USEDEFAULT, 80, 50, g_hSubMenuWindow, NULL, NULL, NULL);
            ShowWindow(chckBox, SW_SHOWNORMAL);
            break;
        }
        case 10200: {
            wstr = L"Menu 3, Submenu 2 Window";
            case_2(g_hSubMenuWindow);
            break;
        }
        case 10300: {
            wstr = L"Menu 3, Submenu 3 Window";
            case_3(g_hSubMenuWindow);
            break;
        }
        case 10400: {
            wstr = L"Menu 3, Submenu 4 Window";
            case_4(g_hSubMenuWindow);
            break;
        }
    }
}
void switchID4(HWND& g_hSubMenuWindow, LPCWSTR& wstr, int menuItemID) {
    switch (menuItemID) {
        case 11000: {
            wstr = L"Menu 4, Submenu 1 Window";
            HWND chckBox = CreateWindow(_T("BUTTON"), _T("Checkbox"), BS_AUTOCHECKBOX, CW_USEDEFAULT, CW_USEDEFAULT, 80, 50, g_hSubMenuWindow, NULL, NULL, NULL);
            ShowWindow(chckBox, SW_SHOWNORMAL);
            break;
        }
        case 12000: {
            wstr = L"Menu 4, Submenu 2 Window";
            case_2(g_hSubMenuWindow);
            break;
        }
        case 13000: {
            wstr = L"Menu 4, Submenu 3 Window";
            case_3(g_hSubMenuWindow);
            break;
        }
        case 14000: {
            wstr = L"Menu 4, Submenu 4 Window";
            case_4(g_hSubMenuWindow);
            break;
        }
    }
}


void case_2(HWND& g_hSubMenuWindow) {
    constexpr int xpos = 100;            // Horizontal position of the window.
    constexpr int ypos = 100;            // Vertical position of the window.
    constexpr int nwidth = 200;          // Width of the window
    constexpr int nheight = 200;         // Height of the window

    HWND hWndComboBox = CreateWindow(WC_COMBOBOX, TEXT(""),
        CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
        xpos, ypos, nwidth, nheight, g_hSubMenuWindow, NULL, HINST_THISCOMPONENT,
        NULL);

    // load the combobox with item list.
    // Send a CB_ADDSTRING message to load each item
    TCHAR Planets[9][10] = {
        TEXT("Mercury"), TEXT("Venus"), TEXT("Terra"), TEXT("Mars"),
        TEXT("Jupiter"), TEXT("Saturn"), TEXT("Uranus"), TEXT("Neptune"),
        TEXT("Pluto??")
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
     HWND hList = CreateWindow(_T("ListBox"), _T(""), WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_BORDER | WS_VSCROLL, 40, 40, 250, 60, g_hSubMenuWindow, (HMENU)ID_LISTBOX, NULL, NULL);

     SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)"1");
     SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)"2");
     SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)"3");
}
void case_4(HWND& g_hSubMenuWindow) {
    HWND editCtlHandle = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 100, 200, 20, g_hSubMenuWindow, NULL, NULL, NULL);
    //WCHAR placeholderText[] = L"Enter here";
    SendMessage(editCtlHandle, EM_SETCUEBANNER, FALSE, NULL);
}

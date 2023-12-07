
#include <windows.h>
#include <tchar.h>
#include <CommCtrl.h>
#include <mshtmhst.h>



static HWND g_hSubMenuWindow = NULL;


void switchID1(LPCWSTR& wstr, int menuItemID);
void switchID2(LPCWSTR& wstr, int menuItemID);
void switchID3(LPCWSTR& wstr, int menuItemID);
void switchID4(LPCWSTR& wstr, int menuItemID);




// Window Procedure callback function
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
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


            AppendMenu(mainmenu, MF_POPUP, (UINT)submenu1, L"&menu1");
            separator();
            AppendMenu(mainmenu, MF_POPUP, (UINT)submenu2, L"&menu2");
            separator();
            AppendMenu(mainmenu, MF_POPUP, (UINT)submenu3, L"&menu3");
            separator();
            AppendMenu(mainmenu, MF_POPUP, (UINT)submenu4, L"&menu4");


            POINT p;
            GetCursorPos(&p);
            TrackPopupMenu(mainmenu, TPM_LEFTBUTTON, p.x, p.y, 0, hwnd, 0);
            //SetMenu(hwnd, mainmenu);
            break;
        }
        case WM_COMMAND: {
            LPCWSTR wstr = L"Default Menu";
            if (HIWORD(wParam) == 0 && lParam == 0) {
                int menuItemID = LOWORD(wParam);

                // Check which submenu item is selected and create a new window accordingly
                if (menuItemID >= 10001 && menuItemID <= 10004)
                    switchID1(wstr, menuItemID);
                else if (menuItemID >= 10010 && menuItemID <= 10040)
                    switchID2(wstr, menuItemID);
                else if (menuItemID >= 10100 && menuItemID <= 10400)
                    switchID3(wstr, menuItemID);
                else if (menuItemID >= 11000 && menuItemID <= 14000)
                    switchID4(wstr, menuItemID);
                }

            g_hSubMenuWindow = CreateWindowEx(0, _T("STATIC"), wstr,
                WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
                NULL, NULL, NULL, NULL);
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














void switchID1(LPCWSTR& wstr, int menuItemID) {
    switch (menuItemID) {
        case 10001: {
            wstr = L"Menu 1, Submenu 1 Window";
            break;
        }
        case 10002: {
            wstr = L"Menu 1, Submenu 2 Window";
            break;
        }
        case 10003: {
            wstr = L"Menu 1, Submenu 3 Window";
            break;
        }
        case 10004: {
            wstr = L"Menu 1, Submenu 4 Window";
            break;
        }
    }
}


void switchID2(LPCWSTR& wstr, int menuItemID) {
    switch (menuItemID) {
        case 10010: {
            wstr = L"Menu 2, Submenu 1 Window";
            break;
        }
        case 10020: {
            wstr = L"Menu 2, Submenu 2 Window";
            break;
        }
        case 10030: {
            wstr = L"Menu 2, Submenu 3 Window";
            break;
        }
        case 10040: {
            wstr = L"Menu 2, Submenu 4 Window";
            break;
        }
    }
}


void switchID3(LPCWSTR& wstr, int menuItemID) {
    switch (menuItemID) {
        case 10100: {
            wstr = L"Menu 3, Submenu 1 Window";
            break;
        }
        case 10200: {
            wstr = L"Menu 3, Submenu 2 Window";
            break;
        }
        case 10030: {
            wstr = L"Menu 3, Submenu 3 Window";
            break;
        }
        case 10400: {
            wstr = L"Menu 3, Submenu 4 Window";
            break;
        }
    }
}


void switchID4(LPCWSTR& wstr, int menuItemID) {
    switch (menuItemID) {
        case 11000: {
            wstr = L"Menu 4, Submenu 1 Window";
            break;
        }
        case 12000: {
            wstr = L"Menu 4, Submenu 2 Window";
            break;
        }
        case 13000: {
            wstr = L"Menu 4, Submenu 3 Window";
            break;
        }
        case 14000: {
            wstr = L"Menu 4, Submenu 4 Window";
            break;
        }
    }
}

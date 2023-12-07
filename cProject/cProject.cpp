// cProject.cpp : Defines the entry point for the application.
//



#include <windows.h>
#include <tchar.h>
//#include <shellapi.h>
#include <CommCtrl.h>
#include <mshtmhst.h>



// Window Procedure callback function
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            HMENU mainmenu = CreatePopupMenu();
            auto separator = [&mainmenu] {
                return AppendMenu(mainmenu, MF_SEPARATOR, 0, NULL); 
            };

            HMENU submenu = CreatePopupMenu();
            AppendMenu(submenu, MF_STRING, 1001, L"submenu 1");
            AppendMenu(submenu, MF_STRING, 1001, L"submenu 2");
            AppendMenu(submenu, MF_STRING, 1001, L"submenu 3");
            AppendMenu(submenu, MF_STRING, 1001, L"submenu 4");

            HMENU submenu1 = CreatePopupMenu();
            AppendMenu(submenu1, MF_STRING, 1002, L"submenu 1");
            AppendMenu(submenu1, MF_STRING, 1002, L"submenu 2");
            AppendMenu(submenu1, MF_STRING, 1002, L"submenu 3");
            AppendMenu(submenu1, MF_STRING, 1002, L"submenu 4");

            HMENU submenu2 = CreatePopupMenu();
            AppendMenu(submenu2, MF_STRING, 1003, L"submenu 1");
            AppendMenu(submenu2, MF_STRING, 1003, L"submenu 2");
            AppendMenu(submenu2, MF_STRING, 1003, L"submenu 3");
            AppendMenu(submenu2, MF_STRING, 1003, L"submenu 4");

            HMENU submenu3 = CreatePopupMenu();
            AppendMenu(submenu3, MF_STRING, 1004, L"submenu 1");
            AppendMenu(submenu3, MF_STRING, 1004, L"submenu 2");
            AppendMenu(submenu3, MF_STRING, 1004, L"submenu 3");
            AppendMenu(submenu3, MF_STRING, 1004, L"submenu 4");


            AppendMenu(mainmenu, MF_POPUP, (UINT)submenu, L"&menu1");
            separator();
            AppendMenu(mainmenu, MF_POPUP, (UINT)submenu1, L"&menu2");
            separator();
            AppendMenu(mainmenu, MF_POPUP, (UINT)submenu2, L"&menu3");
            separator();
            AppendMenu(mainmenu, MF_POPUP, (UINT)submenu3, L"&menu4");


            POINT p;
            GetCursorPos(&p);
            TrackPopupMenu(mainmenu, TPM_LEFTBUTTON, p.x, p.y, 0, hwnd, 0);
            //SetMenu(hwnd, mainmenu);
            break;
        }
        case WM_COMMAND: {
            /*if(LOWORD(wParam) == 1001)
                CreateWindowEx(0, _T("Submenu"), _T("App"), WS_OVERLAPPEDWINDOW,
                    CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
                    NULL, NULL, NULL, NULL);*/
            break;
        }
        case WM_DESTROY: {
            // Quit the application
            PostQuitMessage(0);
            break;
        }
        default: {
            // Default window procedure for other messages
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
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


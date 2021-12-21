#include "main.h"
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

using namespace DirectX;
using namespace DirectX::SimpleMath;

LRESULT CALLBACK WndProcFriedmann(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    static bool s_in_sizemove = false;
    static bool s_in_suspend = false;
    static bool s_minimized = false;
    static bool s_fullscreen = false; // TODO: Set s_fullscreen to true if defaulting to fullscreen

    

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        DrawFriedmann(hdc);

        EndPaint(hWnd, &ps);
        break;
    case WM_ACTIVATEAPP:
        Keyboard::ProcessMessage(message, wParam, lParam);
        Mouse::ProcessMessage(message, wParam, lParam);
        break;

    case WM_INPUT:
    case WM_MOUSEMOVE:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    case WM_MOUSEWHEEL:
    case WM_XBUTTONDOWN:
    case WM_XBUTTONUP:
    case WM_MOUSEHOVER:
        Mouse::ProcessMessage(message, wParam, lParam);
        break;
    case WM_KEYDOWN:
    case WM_KEYUP:
    case WM_SYSKEYUP:
        Keyboard::ProcessMessage(message, wParam, lParam);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

int CreateFriedmannWindow()
{
    Game& game = Game::GetInstance();

    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;

    // Initialize GDI+.
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    auto hInstance = GetModuleHandle(nullptr);

    WNDCLASSEXW wcex = {};
    wcex.cbSize = sizeof(WNDCLASSEXW);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProcFriedmann;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIconW(hInstance, L"IDI_ICON");
    wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszClassName = L"FriedmannWindowClass";
    wcex.hIconSm = LoadIconW(wcex.hInstance, L"IDI_ICON");
    if (!RegisterClassExW(&wcex))
        return 1;

    // Create window
    int w = friedmann_w, h = friedmann_h;
    RECT rc = { 0, 0, static_cast<LONG>(w), static_cast<LONG>(h) };

    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE); //чтобы это были соотношения рабочей области!

    auto gameRect = game.GetGameWindowRect();
    HWND hwnd = CreateWindowExW(0, L"FriedmannWindowClass", L"Friedmann", WS_OVERLAPPEDWINDOW,
        gameRect.right + 20, gameRect.top, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
        nullptr);

    if (!hwnd)
        return 1;

    ShowWindow(hwnd, SW_SHOWNORMAL);
    GetClientRect(hwnd, &rc);
}

void DrawFriedmann(HDC hdc)
{
    Graphics graphics(hdc);
    Pen      pen(Gdiplus::Color(255, 0, 0, 255));
    graphics.DrawLine(&pen, 5, friedmann_h - 5, friedmann_w - 5, friedmann_h - 5);
    graphics.DrawLine(&pen, 5, 5, 5, friedmann_h - 5);


    for (int i = 0; i <= 200; i++)
    {

    }
}

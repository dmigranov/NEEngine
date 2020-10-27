#include "pch.h"
#include "Game.h"
#include "Scene.h"

using namespace DirectX;

// Indicates to hybrid graphics systems to prefer the discrete part by default
extern "C"
{
    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

int Game::StartGame()
{
    m_pScene->SynchronizeSystemsWithEntities();

    // Main message loop
    // it runs indefinitely, and then check for messages inside the while loop
    // the loop will keep running forever unless something interrupts the loop and causes it to exit
    // то есть даже если не рендерим, всё равно апдейтим
    // поэтмоу жрёт столько когда свёрнута

    MSG msg = {};
    while (WM_QUIT != msg.message)
    {
        //Peek: возвращает true, если сообщение есть, если нет - то false (но мы все равно рисуем)
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) != 0)	//remove: message are removed from the queue after pick
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);	//dispatch передает сообщение winproc!!!
        }
        else
        {
            this->Tick();	//update & render
        }
    }

    Cleanup();

    CoUninitialize();

    return (int)msg.wParam;
}

int Game::InitializeEngine(HINSTANCE hInstance, int nCmdShow, const WCHAR* windowName, bool isConsoleEnabled, bool isVSyncEnabled)
{
    if (!XMVerifyCPUSupport())
        return 1;

    HRESULT hr = CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);
    if (FAILED(hr))
        return 1;


    //DEBUG ONLY - CONSOLE
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    //Game& g_game = Game::GetInstance();

    // Register class and create window
    {
        // Register class
        WNDCLASSEXW wcex = {};
        wcex.cbSize = sizeof(WNDCLASSEXW);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WndProc;
        wcex.hInstance = hInstance;
        wcex.hIcon = LoadIconW(hInstance, L"IDI_ICON");
        wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcex.lpszClassName = L"Direct3DGameWindowClass";
        wcex.hIconSm = LoadIconW(wcex.hInstance, L"IDI_ICON");
        if (!RegisterClassExW(&wcex))
            return 1;

        // Create window
        int w, h;
        GetDefaultSize(w, h);

        RECT rc = { 0, 0, static_cast<LONG>(w), static_cast<LONG>(h) };
        
        AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE); //чтобы это были соотношения рабочей области!

        HWND hwnd = CreateWindowExW(0, L"Direct3DGameWindowClass", windowName, WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
            nullptr);
        // TODO: Change to CreateWindowExW(WS_EX_TOPMOST, L"Direct3DGameWindowClass", L"Direct3DGame", WS_POPUP,
        // to default to fullscreen.

        if (!hwnd)
            return 1;

        ShowWindow(hwnd, nCmdShow);
        // TODO: Change nCmdShow to SW_SHOWMAXIMIZED to default to fullscreen.

        GetClientRect(hwnd, &rc);

        //тут, перед message loop, передаётся управление методу Init
        if (Initialize(hwnd, rc.right - rc.left, rc.bottom - rc.top) != 0)
        {
            MessageBox(nullptr, TEXT("Failed to initialize Direct3D pipeline."), TEXT("Error"), MB_OK);
            return -1;
        }
    }
    this->m_isVSyncEnabled = isVSyncEnabled;

    return 0;
}

int Game::InitializeEngine(const WCHAR* windowName, bool isConsoleEnabled, bool isVSyncEnabled)
{
    auto hInstance = GetModuleHandle(nullptr);
    return InitializeEngine(hInstance, ddd, windowName, isConsoleEnabled, isVSyncEnabled);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    static bool s_in_sizemove = false;
    static bool s_in_suspend = false;
    static bool s_minimized = false;
    static bool s_fullscreen = false;
    // TODO: Set s_fullscreen to true if defaulting to fullscreen.

    Game& g_game = Game::GetInstance();

    switch (message)
    {
    case WM_PAINT:
        if (s_in_sizemove)
        {

            {   //добавлено мной для динамического изменения картинки при изменении размера
                RECT rc;
                GetClientRect(hWnd, &rc);

                g_game.OnWindowSizeChanged(rc.right - rc.left, rc.bottom - rc.top);
            }
            g_game.Tick();
        }
        else
        {
            hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_ACTIVATEAPP:
        Keyboard::ProcessMessage(message, wParam, lParam);
        Mouse::ProcessMessage(message, wParam, lParam);
        break;
    case WM_ENTERSIZEMOVE:
        s_in_sizemove = true;
        break;

    case WM_EXITSIZEMOVE:
        s_in_sizemove = false;

        RECT rc;
        GetClientRect(hWnd, &rc);

        g_game.OnWindowSizeChanged(rc.right - rc.left, rc.bottom - rc.top);

        break;
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
        {
            if (!s_minimized)
            {
                s_minimized = true;
                s_in_suspend = true;

                //нужно чтобы ограничить потребление процессора, когда свернута
                //как следствие, когда игра свернута, все процессы приостанавливаются
                {
                    MSG newLoopMessage = {};
                    while (s_minimized == true && GetMessage(&newLoopMessage, nullptr, 0, 0) != 0)
                    {
                        TranslateMessage(&newLoopMessage);
                        DispatchMessage(&newLoopMessage);	//dispatch передает сообщение winproc!!!
                    }
                }
            }
        }
        else if (s_minimized)
        {
            s_minimized = false;
            s_in_suspend = false;
        }
        else if (!s_in_sizemove)
        {
            g_game.OnWindowSizeChanged(LOWORD(lParam), HIWORD(lParam));
        }
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
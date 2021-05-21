#include <pch.h>
#include "Game.h"

#include "Texture.h"
#include "Drawer2D.h"
#include "TextDrawer.h"
#include "SphericalMeshLoader.h"

#include "MeshComponent.h"
#include "TransformComponent.h"

#include "Scene.h"
#include "ResourceManager.h"
#include "ComponentTypeManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Game::Game(unsigned int width, unsigned int height) noexcept :
    m_hwnd(nullptr),
    m_outputWidth(width),
    m_outputHeight(height)
{
}

Game& Game::GetInstance()
{
    static Game game(800, 600);
    return game;
}

int Game::Initialize(HWND window, int width, int height)
{
    /*
    The process of initializing a Direct3D rendering device consists of several steps:
    1. Create the device and swap chain,
    2. Create a render target view of the swap chain’s back buffer,
    3. Create a texture for the depth-stencil buffer,
    4. Create a depth-stencil view from the depth-stencil buffer,
    5. Create a depth-stencil state object that defines the behaviour of the output merger stage,
    6. Create a rasterizer state object that defines the behaviour of the rasterizer stage.
    */
    srand(time(NULL));

    m_hwnd = window;
    assert(m_hwnd != 0);
    RECT clientRect;
    GetClientRect(m_hwnd, &clientRect);
    unsigned int clientWidth = clientRect.right - clientRect.left;
    unsigned int clientHeight = clientRect.bottom - clientRect.top;


    //The swap chain description defines the size and number of render buffers that will be used by the swap chain. It also associates the window to the swap chain which determines where the final image will be presented. The swap chain description also defines the quality of anti-aliasing (if any) that should be applied and how the back buffer is flipped during presentation.
    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

    swapChainDesc.BufferCount = m_backBufferCount;
    swapChainDesc.BufferDesc.Width = clientWidth;
    swapChainDesc.BufferDesc.Height = clientHeight;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.RefreshRate = {0, 1};
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = m_hwnd;
    //sampledesc - multisampling
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;

    //swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    //swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swapChainDesc.Windowed = TRUE;
    UINT createDeviceFlags = 0;
#if _DEBUG
    createDeviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#endif

    // These are the feature levels that we will accept.
    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1
    };

    // This will be the feature level that 
    // is used to create our device and swap chain.
    D3D_FEATURE_LEVEL featureLevel;

    HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE,
        nullptr, createDeviceFlags, featureLevels, _countof(featureLevels),
        D3D11_SDK_VERSION, &swapChainDesc, &g_d3dSwapChain, &g_d3dDevice, &featureLevel,
        &g_d3dDeviceContext);

    if (hr == E_INVALIDARG)
    {
        hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE,
            nullptr, createDeviceFlags, &featureLevels[1], _countof(featureLevels) - 1,
            D3D11_SDK_VERSION, &swapChainDesc, &g_d3dSwapChain, &g_d3dDevice, &featureLevel,
            &g_d3dDeviceContext);
    }

    if (FAILED(hr))
    {
        return -1;
    }


    // Next initialize the back buffer of the swap chain and associate it to a render target view.
    // we use the swap chain’s GetBuffer method to retrieve a pointer to the swap chain’s 
    // single back buffer. The swap chain’s back buffer is automatically created based on the content of the DXGI_SWAP_CHAIN_DESC variable
    // so we do not need to manually create a texture for this purpose. However we do need to associate the backbuffer to a render target view in order to render to the swap chain’s back buffer.
    
    ID3D11Texture2D* backBuffer;
    hr = g_d3dSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
    if (FAILED(hr))
    {
        return -1;
    }

    hr = g_d3dDevice->CreateRenderTargetView(backBuffer, nullptr, &g_d3dRenderTargetView);
    if (FAILED(hr))
    {
        return -1;
    }

    SafeRelease(backBuffer);


    // Create the depth buffer for use with the depth/stencil view.
    D3D11_TEXTURE2D_DESC depthStencilBufferDesc;
    ZeroMemory(&depthStencilBufferDesc, sizeof(D3D11_TEXTURE2D_DESC));

    depthStencilBufferDesc.ArraySize = 1;
    depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilBufferDesc.CPUAccessFlags = 0; // No CPU access required.
    depthStencilBufferDesc.Format = DXGI_FORMAT_D32_FLOAT;
    depthStencilBufferDesc.Width = clientWidth;
    depthStencilBufferDesc.Height = clientHeight;
    depthStencilBufferDesc.MipLevels = 1;
    depthStencilBufferDesc.SampleDesc.Count = 1;
    depthStencilBufferDesc.SampleDesc.Quality = 0;
    depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;

    hr = g_d3dDevice->CreateTexture2D(&depthStencilBufferDesc, nullptr, &g_d3dDepthStencilBuffer);
    if (FAILED(hr))
    {
        return -1;
    }
    //we must create a ID3D11DepthStencilView before we can use this depth buffer for rendering
    hr = g_d3dDevice->CreateDepthStencilView(g_d3dDepthStencilBuffer, nullptr, &g_d3dDepthStencilView);
    if (FAILED(hr))
    {
        return -1;
    }

    // Setup depth/stencil state.
    D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc;
    ZeroMemory(&depthStencilStateDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

    depthStencilStateDesc.DepthEnable = TRUE;       //тест глубины проводится
    depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS;
    depthStencilStateDesc.StencilEnable = FALSE;    //ТЕСТ трафарета НЕ ПРОВОДИТСЯ!

    hr = g_d3dDevice->CreateDepthStencilState(&depthStencilStateDesc, &g_d3dDepthStencilState);


    // Setup blend state
    D3D11_BLEND_DESC blendDesc;
    ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
    blendDesc.RenderTarget[0].BlendEnable = TRUE;   //make TRUE if want it on
    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    hr = g_d3dDevice->CreateBlendState(&blendDesc, &g_d3dBlendState);
    if (FAILED(hr))
    {
        return -1;
    }
    

    // Setup rasterizer state.
    D3D11_RASTERIZER_DESC rasterizerDesc;
    ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));

    rasterizerDesc.AntialiasedLineEnable = FALSE;
    rasterizerDesc.CullMode = D3D11_CULL_BACK;
    rasterizerDesc.DepthBias = 0;
    rasterizerDesc.DepthBiasClamp = 0.0f;
    rasterizerDesc.DepthClipEnable = TRUE;
    rasterizerDesc.FillMode = D3D11_FILL_SOLID;
    rasterizerDesc.FrontCounterClockwise = FALSE;
    rasterizerDesc.MultisampleEnable = FALSE;
    rasterizerDesc.ScissorEnable = FALSE;
    rasterizerDesc.SlopeScaledDepthBias = 0.0f;

    // Create the rasterizer state object.
    hr = g_d3dDevice->CreateRasterizerState(&rasterizerDesc, &g_d3dRasterizerState);
    if (FAILED(hr))
    {
        return -1;
    }

    // Initialize the viewport to occupy the entire client area.
    g_Viewport.Width = static_cast<float>(clientWidth);
    g_Viewport.Height = static_cast<float>(clientHeight);
    g_Viewport.TopLeftX = 0.0f;
    g_Viewport.TopLeftY = 0.0f;
    g_Viewport.MinDepth = 0.0f;
    g_Viewport.MaxDepth = 1.0f;

    // Create a texture sampler state description.
    D3D11_SAMPLER_DESC samplerDesc;
    ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.MipLODBias = 0.0f;
    samplerDesc.MaxAnisotropy = 1;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    samplerDesc.BorderColor[0] = 0;
    samplerDesc.BorderColor[1] = 0;
    samplerDesc.BorderColor[2] = 0;
    samplerDesc.BorderColor[3] = 0;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    isInitialized = true;
    m_pScene = new Scene();

    if (!LoadContent())
    {
        return -1;
    }

    m_textDrawer = new TextDrawer(g_d3dDevice, g_d3dDeviceContext);
    m_drawer2D = new Drawer2D(g_d3dDevice, g_d3dDeviceContext);
    m_pResourceManager = new ResourceManager(g_d3dDevice);
    m_pComponentTypeManager = new ComponentTypeManager();
    m_pComponentTypeManager->RegisterComponentType<TransformComponent>();
    m_pComponentTypeManager->RegisterComponentType<MeshComponent>();

    return 0;
}

void Game::Tick()
{
    //todo: перенести в таймер 
    //на первом кадре много времени, после стабилизируется. проверить и исправить?

    DWORD currentTime = timeGetTime();
    double deltaTime = (currentTime - previousTime) / 1000.;
    //DWORD deltaTime = (currentTime - previousTime);
    previousTime = currentTime;

    // Cap the delta time to the max time step (useful if your debugging and you don't want the deltaTime value to explode.
    deltaTime = std::min<double>(deltaTime, maxTimeStep);

    Update(deltaTime);
    Render();
}

// Properties
void Game::GetDefaultSize(int& width, int& height)
{
    // Change to desired default window size (note minimum size is 320x200).
    width = m_outputWidth;
    height = m_outputHeight;
}

void Game::OnWindowSizeChanged(int width, int height)
{
    m_outputWidth = std::max<int>(width, 1);
    m_outputHeight = std::max<int>(height, 1);
    CreateResources();
}


void Game::CreateResources()
{
    if (!isInitialized)
        return;

    // https://docs.microsoft.com/en-us/windows/win32/direct3dgetstarted/work-with-dxgi
    // Clear the previous window size specific context.
    // A render-target-view interface identifies the render-target subresources that can be accessed during rendering.
    ID3D11RenderTargetView* nullViews[] = { nullptr };

    // Bind one or more render targets atomically and the depth - stencil buffer to the output - merger stage.
    // To bind a render-target view to the pipeline, call ID3D11DeviceContext::OMSetRenderTargets.
    g_d3dDeviceContext->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);
    
    //g_d3dDepthStencilBuffer = nullptr;
    //g_d3dDepthStencilView = nullptr;
    //g_d3dDepthStencilState = nullptr;
    g_d3dDeviceContext->Flush();

    UINT backBufferWidth = static_cast<UINT>(m_outputWidth);
    UINT backBufferHeight = static_cast<UINT>(m_outputHeight);

    DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
    DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

    SafeRelease(g_d3dRenderTargetView);
    // If the swap chain already exists, resize it
    if (g_d3dSwapChain)	//!= null
    {
        HRESULT hr = g_d3dSwapChain->ResizeBuffers(m_backBufferCount, backBufferWidth, backBufferHeight, backBufferFormat, 0);
        DX::ThrowIfFailed(hr);
    }
    
    ID3D11Texture2D* backBuffer;
    HRESULT hr = g_d3dSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
    DX::ThrowIfFailed(hr);

    SafeRelease(g_d3dRenderTargetView);
    hr = g_d3dDevice->CreateRenderTargetView(backBuffer, nullptr, &g_d3dRenderTargetView);
    DX::ThrowIfFailed(hr);

    SafeRelease(backBuffer);

    D3D11_TEXTURE2D_DESC depthStencilBufferDesc;
    ZeroMemory(&depthStencilBufferDesc, sizeof(D3D11_TEXTURE2D_DESC));

    depthStencilBufferDesc.ArraySize = 1;
    depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilBufferDesc.CPUAccessFlags = 0; // No CPU access required.
    depthStencilBufferDesc.Format = DXGI_FORMAT_D32_FLOAT;
    depthStencilBufferDesc.Width = backBufferWidth;
    depthStencilBufferDesc.Height = backBufferHeight;
    depthStencilBufferDesc.MipLevels = 1;
    depthStencilBufferDesc.SampleDesc.Count = 1;
    depthStencilBufferDesc.SampleDesc.Quality = 0;
    depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;

    SafeRelease(g_d3dDepthStencilBuffer);
    SafeRelease(g_d3dDepthStencilView);
    hr = g_d3dDevice->CreateTexture2D(&depthStencilBufferDesc, nullptr, &g_d3dDepthStencilBuffer);
    DX::ThrowIfFailed(hr);
    //we must create a ID3D11DepthStencilView before we can use this depth buffer for rendering
    hr = g_d3dDevice->CreateDepthStencilView(g_d3dDepthStencilBuffer, nullptr, &g_d3dDepthStencilView);
    DX::ThrowIfFailed(hr);


    // Setup depth/stencil state.
    SafeRelease(g_d3dDepthStencilState);
    D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc;
    ZeroMemory(&depthStencilStateDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

    depthStencilStateDesc.DepthEnable = TRUE;       //тест глубины проводится
    depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS;
    depthStencilStateDesc.StencilEnable = FALSE;    //ТЕСТ трафарета НЕ ПРОВОДИТСЯ!

    hr = g_d3dDevice->CreateDepthStencilState(&depthStencilStateDesc, &g_d3dDepthStencilState);
    DX::ThrowIfFailed(hr);

    g_Viewport.Width = static_cast<float>(backBufferWidth);
    g_Viewport.Height = static_cast<float>(backBufferHeight);

    m_pScene->SetCameraOutputSize(backBufferWidth, backBufferHeight);
}

void Game::Update(double deltaTime)
{
    fpsCounter.Update();

    m_pScene->Update(deltaTime);
}

void Game::Render()
{
    m_pScene->Render();

    //g_d3dDeviceContext->GSSetShader(nullptr, nullptr, 0); 
}

void Game::StartDrawing()
{
    assert(g_d3dDevice);
    assert(g_d3dDeviceContext);

    Clear(m_backgroundColor, 1.0f, 0);
}

void Game::Clear(const float clearColor[4], float clearDepth, UINT8 clearStencil)
{
    g_d3dDeviceContext->ClearRenderTargetView(g_d3dRenderTargetView, clearColor);   //clear the back buffer to a particlular color
    g_d3dDeviceContext->ClearDepthStencilView(g_d3dDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, clearDepth, clearStencil);        //method is used to clear the depth and stencil buffer to a particular depth value and stencil value.
}

void Game::FinishDrawing()
{
    m_textDrawer->DrawTextUpRightAlign(std::to_string(fpsCounter.GetFPS()).c_str(), m_outputWidth - 20, 20);

    /*float sizeHori = float(aimSize) / m_outputWidth, sizeVert = float(aimSize) / m_outputHeight;
    m_drawer2D->DrawLine(Vector2(sizeHori, 0.f), Vector2(-sizeHori, 0.f), Colors::Black);
    m_drawer2D->DrawLine(Vector2(0.f, sizeVert), Vector2(0.f, -sizeVert), Colors::Black);
    */ //вынести в систему?

    Present();
}


void Game::Present()
{
    if (m_isVSyncEnabled)
        g_d3dSwapChain->Present(1, 0);    //60 гц: VSync on
    else
        g_d3dSwapChain->Present(0, 0);    //Vsync off; для тестирования производительности
}

void Game::Cleanup()
{
    UnloadContent();

    SafeRelease(g_d3dDepthStencilView);
    SafeRelease(g_d3dRenderTargetView);
    SafeRelease(g_d3dDepthStencilBuffer);
    SafeRelease(g_d3dDepthStencilState);
    SafeRelease(g_d3dRasterizerState);
    //SafeRelease(g_d3dSamplerState);
    SafeRelease(g_d3dSwapChain);
    SafeRelease(g_d3dDeviceContext);
    SafeRelease(g_d3dDevice);
}

bool Game::LoadContent()
{
    assert(g_d3dDevice);
    HRESULT hr;

    // Create the constant buffers for the variables defined in the vertex shader.
    D3D11_BUFFER_DESC constantBufferDesc;
    ZeroMemory(&constantBufferDesc, sizeof(D3D11_BUFFER_DESC));

    constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    constantBufferDesc.CPUAccessFlags = 0;
    constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;

    CreateResources();

    return true;
}

void Game::UnloadContent()
{
    //SafeRelease(...);

    m_pResourceManager->Clean();
    delete m_pResourceManager;
    delete m_pComponentTypeManager;
    delete m_pScene;
    delete m_textDrawer;
    delete m_drawer2D;
}

Scene* Game::GetScene()
{
    return m_pScene;;
}

ResourceManager* Game::GetResourceManager()
{
    return m_pResourceManager;
}

ComponentTypeManager* Game::GetComponentTypeManager()
{
    return m_pComponentTypeManager;
}

void Game::SetBackgroundColor(DirectX::XMVECTORF32 color)
{
    m_backgroundColor = color;
}

ID3D11Device* const Game::GetDevice()
{
    return g_d3dDevice;
}

ID3D11DeviceContext* const Game::GetDeviceContext()
{
    return g_d3dDeviceContext;
}

ID3D11VertexShader* Game::CreateVertexShaderFromBytecode(const void* code, SIZE_T BytecodeLength)
{
    ID3D11VertexShader* returnVertexShader = nullptr;

    HRESULT hr = g_d3dDevice->CreateVertexShader(code, BytecodeLength, nullptr, &returnVertexShader);
    if (FAILED(hr))
    {
        int msgboxID = MessageBox(
            NULL,
            (LPCWSTR)L"Can't create vertex shader",
            (LPCWSTR)L"Can't create vertex shader",
            MB_ICONERROR
        );

        return nullptr;
    }

    return returnVertexShader;
}

ID3D11PixelShader* Game::CreatePixelShaderFromBytecode(const void* code, SIZE_T BytecodeLength)
{
    ID3D11PixelShader* returnPixelShader = nullptr;

    HRESULT hr = g_d3dDevice->CreatePixelShader(code, BytecodeLength, nullptr, &returnPixelShader);
    if (FAILED(hr))
    {
        int msgboxID = MessageBox(
            NULL,
            (LPCWSTR)L"Can't create pixel shader",
            (LPCWSTR)L"Can't create pixel shader",
            MB_ICONERROR
        );

        return nullptr;
    }

    return returnPixelShader;
}


ID3D11InputLayout* Game::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* inputElementDescs, unsigned int numElements, const void* bytecode, SIZE_T bytecodeLength)
{
    ID3D11InputLayout* pReturnLayout = nullptr; //после вызова будет уже куда-то указывать!
    HRESULT hr = g_d3dDevice->CreateInputLayout(inputElementDescs, numElements, bytecode, bytecodeLength, &pReturnLayout);
    if (FAILED(hr))
    {
        int msgboxID = MessageBox(
            NULL,
            (LPCWSTR)L"Can't create input layout",
            (LPCWSTR)L"Can't create input layout",
            MB_ICONERROR
        );
        return nullptr;
    }

    return pReturnLayout;
}

ID3D11Buffer* Game::CreateBuffer(D3D11_BUFFER_DESC bufferDesc, const D3D11_SUBRESOURCE_DATA* pInitialData)
{
    ID3D11Buffer* returnBuffer = nullptr;
    HRESULT hr = g_d3dDevice->CreateBuffer(&bufferDesc, pInitialData, &returnBuffer);

    if (FAILED(hr))
    {
        int msgboxID = MessageBox(
            NULL,
            (LPCWSTR)L"Can't create buffer",
            (LPCWSTR)L"Can't create buffer",
            MB_ICONERROR
        );
        return nullptr;
    }

    return returnBuffer;
}

ID3D11SamplerState* Game::CreateSamplerState(D3D11_SAMPLER_DESC samplerDesc)
{
    ID3D11SamplerState* returnState = nullptr;
    HRESULT hr = g_d3dDevice->CreateSamplerState(&samplerDesc, &returnState);
    if (FAILED(hr))
    {
        int msgboxID = MessageBox(
            NULL,
            (LPCWSTR)L"Can't create sampler state",
            (LPCWSTR)L"Can't create sampler state",
            MB_ICONERROR
        );
        return nullptr;
    }
    return returnState;
}
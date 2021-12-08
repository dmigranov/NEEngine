#pragma once
#include <sstream>
#include <iomanip>

#include "FPSCounter.h"

class Scene;
class ResourceManager;
class ComponentTypeManager;

class Texture;
class Drawer2D;
class TextDrawer;
class Mesh;
class SphericalMesh;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

class Game
{
public:
    static Game& GetInstance();
    int InitializeEngine(const WCHAR* windowName = L"Spherical & Elliptical Spaces Visualizer", bool isConsoleEnabled = false, bool isFullscreenEnabled = false, bool isVSyncEnabled = true);

    int StartGame();

    Scene* GetScene();
    ResourceManager* GetResourceManager();
    ComponentTypeManager* GetComponentTypeManager();

    void SetBackgroundColor(DirectX::XMVECTORF32);

    ID3D11Device* const GetDevice();
    ID3D11DeviceContext* const GetDeviceContext();

    ID3D11VertexShader* CreateVertexShaderFromBytecode(const void* code, SIZE_T bytecodeLength);
    ID3D11GeometryShader* CreateGeometryShaderFromBytecode(const void* code, SIZE_T bytecodeLength);
    ID3D11PixelShader* CreatePixelShaderFromBytecode(const void* code, SIZE_T bytecodeLength);

    inline void VSSetShader(ID3D11VertexShader* pVertexShader);
    inline void GSSetShader(ID3D11GeometryShader* pGeometryShader);
    inline void PSSetShader(ID3D11PixelShader* pPixelShader);
    
    ID3D11InputLayout* CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* inputElementDescs,
        unsigned int numElements, const void* bytecode, SIZE_T bytecodeLength);

    ID3D11Buffer* CreateBuffer(D3D11_BUFFER_DESC bufferDesc, const D3D11_SUBRESOURCE_DATA* pInitialData = nullptr);

    ID3D11SamplerState* CreateSamplerState(D3D11_SAMPLER_DESC samplerDesc);

    inline void PSSetSampler(ID3D11SamplerState *samplerState); //todo: сделать вар. с несколькими сэмплерами!
    inline void IASetInputLayout(ID3D11InputLayout* inputLayout);

    inline void VSSetConstantBuffers(UINT numBuffers, ID3D11Buffer* const* ppConstantBuffers);
    inline void PSSetConstantBuffers(UINT numBuffers, ID3D11Buffer* const* ppConstantBuffers);

    inline void UpdateSubresource(ID3D11Buffer* buffer, const void* pSrcData);

    inline void PSSetShaderResources(UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews);
    


    inline void SetupRasterizer();
    inline void SetupOutputMerger();

private:
    Game(unsigned int width, unsigned int height) noexcept;
    Game(Game const&) = delete;

    int InitializeEngine(HINSTANCE hInstance, int nCmdShow, const WCHAR* windowName = L"Spherical & Elliptical Spaces Visualizer", bool isConsoleEnabled = false, bool isFullscreenEnabled = false, bool isVSyncEnabled = true);

    Game& operator=(Game const&) = delete;

    // Initialization and management
    int Initialize(HWND window, int width, int height);
    void Cleanup();

    // Basic game loop
    void Tick();
    // Properties
    void GetDefaultSize(int& width, int& height);
    // Messages
    void OnWindowSizeChanged(int width, int height);

    friend LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

    void CreateResources();

    void Update(double deltaTime);
    void Render(double deltaTime);
    void Clear(const float clearColor[4], float clearDepth, UINT8 clearStencil);
    void Present();

    void StartDrawing();
    void FinishDrawing();

    bool LoadContent();
    void UnloadContent();

    // Device resources.
    HWND                                            m_hwnd;				//дескриптор окна игры
    int                                             m_outputWidth;
    int                                             m_outputHeight;
    bool                                            m_isVSyncEnabled = true;

    // Direct3D device and swap chain.
    ID3D11Device* g_d3dDevice = nullptr;                                    //used for allocating GPU resources such as buffers, textures, shaders, and state objects
    ID3D11DeviceContext* g_d3dDeviceContext = nullptr;                      //used to configure the rendering pipeline and draw geometry
    IDXGISwapChain* g_d3dSwapChain = nullptr;                               //stores the buffers that are used for rendering data; used to determine how the buffers are swapped when the rendered image should be presented to the scree
    UINT m_backBufferCount = 1;

    // Render target view for the back buffer of the swap chain.
    ID3D11RenderTargetView* g_d3dRenderTargetView = nullptr;
    // Depth/stencil view for use as a depth buffer.
    ID3D11DepthStencilView* g_d3dDepthStencilView = nullptr;
    // A texture to associate to the depth stencil view.
    ID3D11Texture2D* g_d3dDepthStencilBuffer = nullptr;

    // Define the functionality of the depth/stencil stages.
    ID3D11DepthStencilState* g_d3dDepthStencilState = nullptr;

    // Define the functionality of the rasterizer stage.
    ID3D11RasterizerState* g_d3dRasterizerState = nullptr;

    // Blend state: necessary for alpha blending
    ID3D11BlendState* g_d3dBlendState = nullptr;
    //ID3D11BlendState* g_d3dBlendStateOff = nullptr;

    D3D11_VIEWPORT g_Viewport = { 0 };              //The g_Viewport variable defines the size of the viewport rectangle. The viewport rectangle is also used by the rasterizer stage to determine the renderable area on screen.

    Scene* m_pScene;
    ResourceManager* m_pResourceManager;
    ComponentTypeManager* m_pComponentTypeManager;

    // Timer
    DWORD                                           previousTime = timeGetTime();
    const float                                     targetFramerate = 30.0f;
    const float                                     maxTimeStep = 1.0f / targetFramerate;

    TextDrawer *                          m_textDrawer;
    Drawer2D *                            m_drawer2D;
    const int                             aimSize = 20;

    FPSCounter                            fpsCounter;

    DirectX::XMVECTORF32 m_backgroundColor = DirectX::Colors::CadetBlue;

    bool isInitialized = false;




    friend class Mesh;

    friend class SphericalMesh;
    friend class SphericalOctahedron;
    friend class SphericalCube;
    friend class SphericalSphere;
    friend class SphericalEllipsoid;

    friend class Scene;

    friend class BitmapRenderSystem;
    friend class InputSystem;
};



inline void Game::PSSetSampler(ID3D11SamplerState* samplerState)
{
    g_d3dDeviceContext->PSSetSamplers(0, 1, &samplerState);
}

inline void Game::IASetInputLayout(ID3D11InputLayout* inputLayout)
{
    g_d3dDeviceContext->IASetInputLayout(inputLayout);
}

inline void Game::VSSetConstantBuffers(UINT numBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
    g_d3dDeviceContext->VSSetConstantBuffers(0, numBuffers, ppConstantBuffers);
}

inline void Game::PSSetConstantBuffers(UINT numBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
    g_d3dDeviceContext->PSSetConstantBuffers(0, numBuffers, ppConstantBuffers);
}

inline void Game::UpdateSubresource(ID3D11Buffer* buffer, const void* pSrcData)
{
    g_d3dDeviceContext->UpdateSubresource(buffer, 0, nullptr, pSrcData, 0, 0);
}

inline void Game::PSSetShaderResources(UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
    g_d3dDeviceContext->PSSetShaderResources(0, NumViews, ppShaderResourceViews);
}

inline void Game::SetupRasterizer()
{
    g_d3dDeviceContext->RSSetState(g_d3dRasterizerState);
    g_d3dDeviceContext->RSSetViewports(1, &g_Viewport);
}

inline void Game::SetupOutputMerger()
{
    g_d3dDeviceContext->OMSetRenderTargets(1, &g_d3dRenderTargetView, g_d3dDepthStencilView);
    g_d3dDeviceContext->OMSetDepthStencilState(g_d3dDepthStencilState, 1); //1 is Reference value to perform against when doing a depth-stencil test.
    g_d3dDeviceContext->OMSetBlendState(g_d3dBlendState, 0, 0xffffffff);
}

inline void Game::VSSetShader(ID3D11VertexShader* pVertexShader)
{
    g_d3dDeviceContext->VSSetShader(pVertexShader, nullptr, 0);
}

inline void Game::GSSetShader(ID3D11GeometryShader* pGeometryShader)
{
    g_d3dDeviceContext->GSSetShader(pGeometryShader, nullptr, 0);
}

inline void Game::PSSetShader(ID3D11PixelShader* pPixelShader)
{
    g_d3dDeviceContext->PSSetShader(pPixelShader, nullptr, 0);
}
#pragma once
#include <sstream>
#include <iomanip>

//Shaders
#include "VertexShader.h"
#include "PixelShader.h"

#include "SimpleInputHandler.h"

#include "FPSCounter.h"

class Scene;
class ResourceManager;

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
    int InitializeEngine(HINSTANCE hInstance, int nCmdShow, const WCHAR* windowName = L"Spherical & Elliptical Spaces Visualizer", bool isConsoleEnabled = false, bool isVSyncEnabled = true);
    int StartGame();

    Scene* GetScene();
    ResourceManager* GetResourceManager();

    void SetBackgroundColor(DirectX::XMVECTORF32);

private:
    Game(unsigned int width, unsigned int height) noexcept;
    Game(Game const&) = delete;
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

    friend class Mesh;

    friend class SphericalMesh;
    friend class SphericalOctahedron;
    friend class SphericalCube;
    friend class SphericalSphere;
    friend class SphericalAsteroid;
    friend class SphericalEllipsoid;

    friend class Scene;
    friend class MeshComponent;

    friend LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

    void CreateResources();

    void Update(float deltaTime);
    void Render();
    void Clear(const float clearColor[4], float clearDepth, UINT8 clearStencil);
    void Present();

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

    D3D11_VIEWPORT g_Viewport = { 0 };                                      //The g_Viewport variable defines the size of the viewport rectangle. The viewport rectangle is also used by the rasterizer stage to determine the renderable area on screen.

    // Vertex buffer data
    ID3D11InputLayout * g_d3dInputLayout = nullptr;                         //used to describe the order and type of data that is expected by the vertex shader.
    
    Scene* m_pScene;
    ResourceManager* m_pResourceManager;

    // Shader data
    ID3D11VertexShader* g_d3dVertexShader = nullptr;
    ID3D11VertexShader* g_d3dSphericalVertexShader = nullptr;
    ID3D11VertexShader* g_d3dEllipticalVertexShader = nullptr;

    //ID3D11GeometryShader* g_d3dGeometryShader = nullptr;

    ID3D11PixelShader* g_d3dPixelShader = nullptr;

    ID3D11SamplerState* g_d3dSamplerState = nullptr;

    // Shader resources
    enum ConstantBuffer
    {
        CB_Application, //The application level constant buffer stores variables that rarely change. 
        CB_Frame,       //The frame level constant buffer stores variables that change each frame. An example of a frame level shader variable would be the cameraТs view matrix which changes whenever the camera moves
        CB_Object,      //The object level constant buffer stores variables that are different for every object being rendered. An example of an object level shader variable is the objectТs world matrix.
        NumConstantBuffers
    };

    //three constant buffers: buffers are used to store shader variables that remain constant during current draw call. An example of a constant shader variable is the cameraТs projection matrix. Since the projection matrix will be the same for every vertex of the object, this variable does not need to be passed to the shader using vertex data.
    ID3D11Buffer* g_d3dVSConstantBuffers[NumConstantBuffers];
    //todo: создать отдельные классы-константбуфферы (три штуки), которые будут инкапс. все вещи дл€ каждого этапа

    ID3D11Buffer* g_d3dPSConstantBuffer;

    // Timer
    DWORD                                           previousTime = timeGetTime();
    const float                                     targetFramerate = 30.0f;
    const float                                     maxTimeStep = 1.0f / targetFramerate;

    // Input
    std::unique_ptr<InputHandler>         m_inputHandler;

    TextDrawer *                          m_textDrawer;
    Drawer2D *                            m_drawer2D;
    const int                             aimSize = 20;

    FPSCounter                            fpsCounter;

    struct PerApplicationPSConstantBuffer
    {
        DirectX::XMVECTORF32 mistColor = DirectX::Colors::CadetBlue;
        float m_edgeThickness = 0.00f;
    };
    PerApplicationPSConstantBuffer perApplicationPSConstantBuffer;

    bool isInitialized = false;
};
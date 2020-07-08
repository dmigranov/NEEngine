#include "pch.h"
#include "SimpleInputHandler.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//extern void ExitGame();

const float MOVEMENT_GAIN = 0.3f;
const float ROTATION_GAIN = 1.3f;

SimpleInputHandler::SimpleInputHandler(std::shared_ptr<Camera> camera, std::function<void(float deltaTime)> func, HWND window)
{
    m_keyboard = std::make_unique<Keyboard>();
    m_mouse = std::make_unique<Mouse>();
    m_mouse->SetWindow(window);
    m_camera = camera;
    this->func = func;
}

void SimpleInputHandler::HandleInput(float deltaTime)
{
	HandleKeyboard(deltaTime);
	HandleMouse(deltaTime);
}

void SimpleInputHandler::HandleKeyboard(float deltaTime)
{
    auto kb = m_keyboard->GetState();
    if (kb.Escape)
    {
        //ExitGame();
    }

    Vector3 move = Vector3::Zero;

    if (kb.Up || kb.W)
        move.z += deltaTime;

    if (kb.Down || kb.S)
        move.z -= deltaTime;

    if (kb.Left || kb.A)
        move.x -= deltaTime;

    if (kb.Right || kb.D)
        move.x += deltaTime;

    if (kb.R)
        move.y += deltaTime;

    if (kb.F)
        move.y -= deltaTime;


    move *= MOVEMENT_GAIN;
    if(move != Vector3::Zero)
        m_camera->Move(move);

    func(deltaTime);
}

void SimpleInputHandler::HandleMouse(float deltaTime)
{
    auto mouse = m_mouse->GetState();

    if (mouse.positionMode == Mouse::MODE_RELATIVE)
    {
        Vector3 delta = Vector3(float(mouse.x) * deltaTime, float(mouse.y) * deltaTime, 0.f)
            * ROTATION_GAIN;

        m_camera->ChangePitchYawRoll(-delta.y, delta.x, 0.);
    }

    m_mouse->SetMode(mouse.leftButton ? Mouse::MODE_RELATIVE : Mouse::MODE_ABSOLUTE);
}

#pragma once
class InputInfo
{
public:
	//todo: создать свою обертку и на каждом апдейте обновлять ее в зависимости от DXTK-шной
	//static void Update();
	DirectX::Keyboard::State& GetKeys();
private:
	static DirectX::Keyboard  m_keyboard;
	static DirectX::Mouse     m_mouse;
};


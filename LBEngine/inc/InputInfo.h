#pragma once
class InputInfo
{
public:
	InputInfo();
	//todo: создать свою обертку и на каждом апдейте обновлять ее в зависимости от DXTK-шной
	//static void Update();
	//DirectX::Keyboard::State GetKeys();
	//bool IsKeyPressed(DirectX::Keyboard::Keys key);
private:
	friend class InputSystem;

	void Update();
};


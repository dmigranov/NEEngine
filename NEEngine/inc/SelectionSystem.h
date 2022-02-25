#pragma once
#include "System.h"

class InputComponent;

class SelectionSystem :
    public System
{
public:
	SelectionSystem(InputComponent* pInputComponent);
	virtual void Execute(double deltaTime) override;
private:
	InputComponent* m_pInputComponent
};


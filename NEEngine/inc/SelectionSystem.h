#pragma once
#include "System.h"
class SelectionSystem :
    public System
{
public:
	SelectionSystem(InputComponent* pInputComponent);
	virtual void Execute(double deltaTime) override;
private:

};


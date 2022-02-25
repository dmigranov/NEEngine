#pragma once
#include "System.h"
class SelectionSystem :
    public System
{
public:
	SelectionSystem();
	virtual void Execute(double deltaTime) override;
private:

};


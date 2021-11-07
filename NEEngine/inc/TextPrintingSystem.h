#pragma once
#include "System.h"
class TextPrintingSystem :
    public System
{
public:
    TextPrintingSystem();
    virtual void Execute(double deltaTime) override;
};


#pragma once
#include "System.h"

class TextDrawer;

class TextPrintingSystem :
    public System
{
public:
    TextPrintingSystem();
    virtual void Execute(double deltaTime) override;
    ~TextPrintingSystem();
private:
    TextDrawer* m_textDrawer;
};


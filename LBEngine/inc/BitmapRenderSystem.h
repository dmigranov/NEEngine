#pragma once
#include "System.h"
class BitmapRenderSystem :
    public System
{
public:
    virtual void Execute(DWORD deltaTime) override;
};


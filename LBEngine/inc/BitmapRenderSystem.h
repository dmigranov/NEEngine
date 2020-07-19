#pragma once
#include "System.h"
class BitmapRenderSystem :
    public System
{
public:
    BitmapRenderSystem();
    virtual void Execute(DWORD deltaTime) override;
private:
    virtual void AddEntity(Entity* pEntity) override;
    std::vector<Entity*> m_opaqueEntities;;
    std::vector<Entity*> m_nonOpaqueEntities;;

};


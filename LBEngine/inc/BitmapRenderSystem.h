#pragma once
#include "System.h"
class BitmapRenderSystem :
    public System
{
public:
    BitmapRenderSystem();
    virtual void Execute(double deltaTime) override;
private:
    virtual void AddEntity(Entity* pEntity) override;
    std::vector<Entity*> m_opaqueEntities;;
    std::vector<Entity*> m_nonOpaqueEntities;;
    void Render(Entity * pEntity, ID3D11DeviceContext* pDeviceContext, ID3D11Resource* pConstantBuffer);
};


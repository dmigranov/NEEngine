#pragma once
#include "System.h"
class ToricRenderSystem :
    public System
{
public:
    struct InstanceType
    {
        DirectX::SimpleMath::Vector3 position;
    };


    ToricRenderSystem(unsigned int replicationCount, double torX, double torY, double torZ);
    virtual void Execute(double deltaTime) override;
private:
    void Render(Entity* pEntity, ID3D11DeviceContext* pDeviceContext);

    unsigned int m_replicationCount;
    double m_torX, m_torY, m_torZ;

    unsigned int m_instanceCount;
};


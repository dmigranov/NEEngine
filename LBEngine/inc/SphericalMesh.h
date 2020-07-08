#pragma once
#include "Mesh.h"

class SphericalMesh : public Mesh
{
    friend class SphericalOctahedron;
    friend class SphericalCube;
    friend class SphericalSphere;
    friend class SphericalAsteroid;

public:
    SphericalMesh();
    SphericalMesh(int nv, VertexPosColor* vertices, int ni, WORD* indices);
    SphericalMesh(int nv, VertexPosColor* vertices, int ni, WORD* indices, DirectX::XMMATRIX world);

    //можно рисовать один и тот же меш используя разные матрицы
    //std::list<XMMATRIX> list = { ..., ... }; cube->Render(list); 
    virtual void Render(std::list<DirectX::XMMATRIX> matrices) override;
    virtual void Render() override;
    virtual void Render(DirectX::XMMATRIX matrix) override;

private:
};
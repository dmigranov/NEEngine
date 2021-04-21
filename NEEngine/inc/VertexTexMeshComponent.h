#pragma once

#include "Texture.h"
#include <wtypes.h>

#include "Component.h"
#include "MeshComponent.h"

struct VertexPosTex //todo: затемплейтить
{
    DirectX::XMFLOAT4 Position;  //координаты точки в четырехмерном пространстве
    DirectX::XMFLOAT2 TexCoord;
};

class VertexTexMeshComponentDel
{
public:

    VertexTexMeshComponentDel(int nv, VertexPosTex* vertices, int ni, WORD* indices);
};

#include "pch.h"
#include "ResourceManager.h"

#include "Texture.h"
#include "Game.h"

ResourceManager::ResourceManager(ID3D11Device* device)
{
    g_d3dDevice = device;
}

Texture* ResourceManager::CreateTexture(const WCHAR* name)
{
    auto texture = new Texture();
    if (!texture->Initialize(g_d3dDevice, name))
        return nullptr;
    textures.push_back(texture);
    return texture;
}

void ResourceManager::Clean()
{
    while (!textures.empty()) delete textures.front(), textures.pop_front();
}

#include "pch.h"
#include "ResourceManager.h"

#include "Texture.h"
#include "Game.h"

ResourceManager::ResourceManager(ID3D11Device* device)
{
    g_d3dDevice = device;
}

void ResourceManager::AddTexture(Texture* pTexture)
{
    textures.push_back(pTexture);
}

void ResourceManager::Clean()
{
    while (!textures.empty()) delete textures.front(), textures.pop_front();
}

// TODO: а зачем мне вообще ResourceManager? Можно все делать в текстуре, и дестуктор тоже... 
// хотя смысл есть: чтобы автоматически удалять указатели на объекты класса Texture, провоцируя очистку
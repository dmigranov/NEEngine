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
    { 
        std::wstring ws1(L"Texture ");
        std::wstring ws2(name);
        std::wstring ws3(L" not found");
        auto errorMsg = ws1 + ws2 + ws3;
        int msgboxID = MessageBox(
            NULL,
            (LPCWSTR)errorMsg.c_str(),
            (LPCWSTR)L"Resource not found",
            MB_ICONERROR
        );
        return nullptr;
    }
    textures.push_back(texture);
    return texture;
}

void ResourceManager::Clean()
{
    while (!textures.empty()) delete textures.front(), textures.pop_front();
}

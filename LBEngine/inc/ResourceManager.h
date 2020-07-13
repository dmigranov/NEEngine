#pragma once
class Texture; 

class ResourceManager
{
public:
    ResourceManager(ID3D11Device * device);
    Texture* CreateTexture(const WCHAR* name);
    void Clean();
private:
    ID3D11Device* g_d3dDevice;
    std::list<Texture*> textures;
};


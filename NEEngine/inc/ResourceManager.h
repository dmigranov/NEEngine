#pragma once
class Texture; 

class ResourceManager
{
public:
    ResourceManager(ID3D11Device * device);
    //Texture* CreateTexture(const WCHAR* name);
    //Shader* CreateShaderFromHeader(const WCHAR* name);
    //Shader* CreateShaderFromCompiled(const WCHAR* name);
    void AddTexture(Texture* pTexture);
    void Clean();
private:
    ID3D11Device* g_d3dDevice;
    std::list<Texture*> textures;
};


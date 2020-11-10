#pragma once
class Texture
{
public:
	Texture();
	Texture(const Texture&);
	~Texture();

	bool Initialize(ID3D11Device* device, const WCHAR* name);
	void Shutdown();

	unsigned int GetWidth();
	unsigned int GetHeight();

	ID3D11ShaderResourceView* GetTexture();
private:
	unsigned int m_width, m_height;

	ID3D11ShaderResourceView* m_texture;
	ID3D11Resource* m_resource;
};


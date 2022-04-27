#include "pch.h"
#include "Texture.h"
#include "DDSTextureLoader.h"
#include "Game.h"
#include "ResourceManager.h"

Texture::Texture() : m_texture(nullptr), m_resource(nullptr)
{
}

Texture::Texture(const Texture&)
{
}

Texture::Texture(const WCHAR* name)
{
	Game& game = Game::GetInstance();
	auto resourceManager = game.GetResourceManager();
	*this = *resourceManager->CreateTexture(name);
}

Texture::~Texture()
{
	Shutdown();
}

bool Texture::Initialize(ID3D11Device* device, const WCHAR* name)
{

	HRESULT result = DirectX::CreateDDSTextureFromFile(device, name, &m_resource, &m_texture); 
	if (FAILED(result))
	{
		return false;
	}
	ID3D11Texture2D* pTextureInterface = nullptr;
	m_resource->QueryInterface<ID3D11Texture2D>(&pTextureInterface);
	D3D11_TEXTURE2D_DESC desc;
	pTextureInterface->GetDesc(&desc);

	m_width = desc.Width;
	m_height = desc.Height;

	return true;
}

void Texture::Shutdown()
{
	if (m_texture)
	{
		m_texture->Release();
		m_texture = nullptr;
	}

	if (m_resource)
	{
		m_resource->Release();
		m_resource = nullptr;
	}

	return;
}

unsigned int Texture::GetWidth()
{
	return m_width;
}

unsigned int Texture::GetHeight()
{
	return m_height;
}

ID3D11ShaderResourceView* Texture::GetTexture()
{
	return m_texture;
}

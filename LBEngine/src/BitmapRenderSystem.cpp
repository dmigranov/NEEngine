#include "pch.h"
#include "BitmapRenderSystem.h"
#include "BitmapComponent.h"
#include "Entity.h"
#include "TransformComponent.h"

#include "Game.h"

BitmapRenderSystem::BitmapRenderSystem()
{
	SubscribeToComponentType(ComponentType::TransformComponentType);
	SubscribeToComponentType(ComponentType::BitmapComponentType);
}

void BitmapRenderSystem::Execute(DWORD deltaTime)
{
	ID3D11DeviceContext* pDeviceContext = Game::GetInstance().g_d3dDeviceContext;

	//сначала opaque (front-to-back)
	std::stable_sort(m_opaqueEntities.begin(), m_opaqueEntities.end(), [](Entity* e1, Entity* e2) -> bool {
		return e1->GetTransform()->GetPosition().z < e2->GetTransform()->GetPosition().z;
	});	//сортирует по возрастанию: сначала меньшие z...
	for (auto pEntity : m_opaqueEntities)
	{
		Render(pEntity, pDeviceContext);
	}


	//затем non opaque (back-to-front)
	std::stable_sort(m_opaqueEntities.begin(), m_opaqueEntities.end(), [](Entity* e1, Entity* e2) -> bool {
		return e1->GetTransform()->GetPosition().z < e2->GetTransform()->GetPosition().z;
	});	//сортирует по убыванию: сначала большие z...
	for (auto pEntity : m_nonOpaqueEntities)
	{
		Render(pEntity, pDeviceContext);
	}	
}

void BitmapRenderSystem::AddEntity(Entity* pEntity)
{
	BitmapComponent* bitmapComponent = (BitmapComponent*)pEntity->GetComponent(ComponentType::BitmapComponentType);

	if (bitmapComponent->IsOpaque())
		m_opaqueEntities.push_back(pEntity);
	else
		m_nonOpaqueEntities.push_back(pEntity);

	m_entities.push_back(pEntity);

}

void BitmapRenderSystem::Render(Entity* pEntity, ID3D11DeviceContext* pDeviceContext)
{
	BitmapComponent* p_bitmapComponent = (BitmapComponent*)pEntity->GetComponent(ComponentType::BitmapComponentType);
	TransformComponent* p_transformComponent = (TransformComponent*)pEntity->GetComponent(ComponentType::TransformComponentType);
	{

		unsigned int stride;
		unsigned int offset;

		// Set vertex buffer stride and offset.
		stride = sizeof(BitmapComponent::VertexType);
		offset = 0;

		// Set the vertex buffer to active in the input assembler so it can be rendered.
		pDeviceContext->IASetVertexBuffers(0, 1, &p_bitmapComponent->m_vertexBuffer, &stride, &offset);

		// Set the index buffer to active in the input assembler so it can be rendered.
		pDeviceContext->IASetIndexBuffer(p_bitmapComponent->m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
		pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		Texture* pTexture;
		if (( pTexture = p_bitmapComponent->m_spriteSheet) != nullptr)
		{     
			//Pixel Shader Stafe - unique 4 every stage
			auto shaderResource = pTexture->GetTexture();
			pDeviceContext->PSSetShaderResources(0, 1, &shaderResource);
		}
	}
}

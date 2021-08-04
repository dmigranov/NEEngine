#include "pch.h"
#include "HyperbolicRenderSystem.h"

#include "Entity.h"
#include "MeshComponent.h"
#include "HyperbolicTransformComponent.h"

#include "Effect.h"
HyperbolicRenderSystem::HyperbolicRenderSystem()
{
	SubscribeToComponentType<HyperbolicTransformComponent>();
	SubscribeToComponentType<MeshComponent>();

	m_isDrawing = true;
}

void HyperbolicRenderSystem::Execute(double deltaTime)
{
	auto& game = Game::GetInstance();
	ID3D11DeviceContext* pDeviceContext = game.GetDeviceContext();
	auto pDevice = game.GetDevice();

	//Rasterizer Stage
	game.SetupRasterizer();

	//Output Merger Stage (merges the output from the pixel shader onto the color and depth buffers)
	game.SetupOutputMerger();

	//TODO: more optimal per-effect traverse (и вынести может куда-то сам перебор в олтдельынй класс?)
	for (auto pEntity : m_entities)
	{
		if (pEntity->IsVisible())
			Render(pEntity, pDeviceContext);
	}
}

void HyperbolicRenderSystem::Render(Entity* pEntity, ID3D11DeviceContext* pDeviceContext)
{
	HyperbolicTransformComponent* pTransformComponent = pEntity->GetComponent<HyperbolicTransformComponent>();
	MeshComponent* pMeshComponent = pEntity->GetComponent<MeshComponent>();
	auto pEffect = pMeshComponent->GetEffect();

	if (!pEffect) //for debug: can be commented
	{
		std::cerr << "No effect found for the entity " << pEntity->GetName() << ", won't ber rendered further!" << std::endl;
		pEntity->SetVisible(false);
		return;
	}

	// Input Assembler Stage - unique for every mesh
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	unsigned int stride = pEffect->GetVertexBufferSize();
	unsigned int offset = 0;

	auto vertexBuffer = pMeshComponent->GetVertexBuffer();
	auto indexBuffer = pMeshComponent->GetIndexBuffer();
	pDeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	// Set the index buffer to active in the input assembler so it can be rendered.
	pDeviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);
	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	//TODO: draw indexed, but without instansing


}

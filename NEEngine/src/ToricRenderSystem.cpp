#include "pch.h"
#include "ToricRenderSystem.h"

#include "Entity.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "Effect.h"


ToricRenderSystem::ToricRenderSystem(unsigned int replicationCount, double torX, double torY, double torZ)
{
	SubscribeToComponentType<TransformComponent>();
	SubscribeToComponentType<MeshComponent>();

	m_replicationCount = replicationCount;
	m_torX = torX;
	m_torY = torY;
	m_torZ = torZ;

	m_isDrawing = true;
}

void ToricRenderSystem::Execute(double deltaTime)
{
	auto& game = Game::GetInstance();
	ID3D11DeviceContext* pDeviceContext = game.GetDeviceContext();
	auto pDevice = game.GetDevice();

	//Rasterizer Stage
	game.SetupRasterizer();

	//Output Merger Stage (merges the output from the pixel shader onto the color and depth buffers)
	game.SetupOutputMerger();

	//todo: а может, сделать так, чтобы инстансы у всех объектов были одинаковые 
	//(по крайней мере в рамках кадра - execute) и сразу тут формировать массив?


	//todo: более оптимальный перебор по эффектам (и вынести может куда-то сам перебор в олтдельынй класс?)
	for (auto pEntity : m_entities)
	{
		if (pEntity->IsVisible())
			Render(pEntity, pDeviceContext);
	}
}

void ToricRenderSystem::Render(Entity* pEntity, ID3D11DeviceContext* pDeviceContext)
{
	TransformComponent* pTransformComponent = pEntity->GetComponent<TransformComponent>();
	MeshComponent* pMeshComponent = pEntity->GetComponent<MeshComponent>();
	auto pEffect = pMeshComponent->GetEffect();

	if (!pEffect) //для отладки содержимое можно закомментировать
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



	//todo: в старой версии не учитывается смещение, чтобы объект был по центру!
}

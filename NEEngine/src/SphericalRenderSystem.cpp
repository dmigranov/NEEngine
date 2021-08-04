#include "pch.h"
#include "SphericalRenderSystem.h"

#include "Entity.h"
#include "MeshComponent.h"
#include "SphericalTransformComponent.h"

#include "Effect.h"

SphericalRenderSystem::SphericalRenderSystem()
{
	//MeshComponent у всех общий!!!

	SubscribeToComponentType<SphericalTransformComponent>();
	//SubscribeToComponentType<SphericalMeshComponent>();
	SubscribeToComponentType<MeshComponent>();

	m_isDrawing = true;
}

void SphericalRenderSystem::Execute(double deltaTime)
{
	auto& game = Game::GetInstance();
	ID3D11DeviceContext* pDeviceContext = game.GetDeviceContext();
	auto pDevice = game.GetDevice();

	//Input Assembler Stage - common
	//pDeviceContext->IASetInputLayout(game.g_d3dInputLayout);

	//Vertex Shader Stage
	//pDeviceContext->VSSetShader(game.g_d3dVertexShader, nullptr, 0);
	//pDeviceContext->VSSetConstantBuffers(0, 3, game.g_d3dVSConstantBuffers);

	//Geometry Shader Stage
	//pDeviceContext->GSSetShader(game.g_d3dGeometryShader, nullptr, 0);

	//Rasterizer Stage
	game.SetupRasterizer();

	//Pixel Shader Stage
	///pDeviceContext->PSSetShader(game.g_d3dPixelShader, nullptr, 0);
	//pDeviceContext->PSSetConstantBuffers(0, 1, &game.g_d3dPSConstantBuffer);
	//pDeviceContext->PSSetSamplers(0, 1, &game.g_d3dSamplerState);

	//Output Merger Stage (merges the output from the pixel shader onto the color and depth buffers)
	game.SetupOutputMerger();



	//TODO: more optimal per-effect traverse (и вынести может куда-то сам перебор в олтдельынй класс?)
	for (auto pEntity : m_entities)
	{
		if(pEntity->IsVisible())
			Render(pEntity, pDeviceContext);
	}
}

void SphericalRenderSystem::Render(Entity* pEntity, ID3D11DeviceContext* pDeviceContext)
{
	SphericalTransformComponent* pTransformComponent = pEntity->GetComponent<SphericalTransformComponent>();
	MeshComponent* pMeshComponent = pEntity->GetComponent<MeshComponent>();
	auto pEffect = pMeshComponent->GetEffect();

	if (!pEffect) //for debug: can be commented
	{
		std::cerr << "No effect found for the entity " << pEntity->GetName() << ", won't ber rendered further!"  << std::endl;
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

	pEffect->UpdatePerObject(pEntity);

	pDeviceContext->DrawIndexedInstanced(pMeshComponent->GetIndicesCount(), 2, 0, 0, 0);

}

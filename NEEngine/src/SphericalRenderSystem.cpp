#include "pch.h"
#include "SphericalRenderSystem.h"

#include "Entity.h"
#include "MeshComponent.h"
#include "SphericalTransformComponent.h"
#include "SphericalMeshComponent.h"


SphericalRenderSystem::SphericalRenderSystem()
{
	//todo:
	//или сделать универсальную систему Rendering'а?
	//короче, для начала SphericalMeshComponent и SphericalTransformComponent
	//EllipticalRenderSystem работает с ними же!

	SubscribeToComponentType<SphericalTransformComponent>();
	//SubscribeToComponentType<SphericalMeshComponent>();
	//может, добавить AbstractSpherical?
	SubscribeToComponentType<AbstractMeshComponent>();

	m_isDrawing = true;
}

void SphericalRenderSystem::Execute(double deltaTime)
{
	auto& game = Game::GetInstance();
	ID3D11DeviceContext* pDeviceContext = game.g_d3dDeviceContext;
	auto pDevice = game.g_d3dDevice;

	auto pConstantBuffer = game.g_d3dVSConstantBuffers[2];

	//todo: константные буферы перенести в Effect, как и текстуры
	//по существу, надо все эти этапы настраивать там, а создавать буферы - в его конструкторе
 
	//Input Assembler Stage - common
	pDeviceContext->IASetInputLayout(game.g_d3dInputLayout);

	//Vertex Shader Stage
	pDeviceContext->VSSetShader(game.g_d3dVertexShader, nullptr, 0);
	pDeviceContext->VSSetConstantBuffers(0, 3, game.g_d3dVSConstantBuffers);

	//Geometry Shader Stage
	//pDeviceContext->GSSetShader(game.g_d3dGeometryShader, nullptr, 0);

	//Rasterizer Stage
	pDeviceContext->RSSetState(game.g_d3dRasterizerState);
	pDeviceContext->RSSetViewports(1, &game.g_Viewport);

	//Pixel Shader Stage
	pDeviceContext->PSSetShader(game.g_d3dPixelShader, nullptr, 0);
	pDeviceContext->PSSetConstantBuffers(0, 1, &game.g_d3dPSConstantBuffer);
	pDeviceContext->PSSetSamplers(0, 1, &game.g_d3dSamplerState);

	//Output Merger Stage (merges the output from the pixel shader onto the color and depth buffers)
	pDeviceContext->OMSetRenderTargets(1, &game.g_d3dRenderTargetView, game.g_d3dDepthStencilView);
	pDeviceContext->OMSetDepthStencilState(game.g_d3dDepthStencilState, 1); //1 is Reference value to perform against when doing a depth-stencil test.
	pDeviceContext->OMSetBlendState(game.g_d3dBlendState, 0, 0xffffffff);


	for (auto pEntity : m_entities)
	{
		Render(pEntity, pDeviceContext, pConstantBuffer);
	}
}

void SphericalRenderSystem::Render(Entity* pEntity, ID3D11DeviceContext* pDeviceContext, ID3D11Resource* pConstantBuffer)
{
	SphericalTransformComponent* pTransformComponent = pEntity->GetComponent<SphericalTransformComponent>();
	//SphericalMeshComponent* pMeshComponent = pEntity->GetComponent<SphericalMeshComponent>();
	AbstractMeshComponent* pMeshComponent = pEntity->GetComponent<AbstractMeshComponent>();

	// ЭТО ВСЁ ТОЖЕ перенести потом в ЭФфект/Материал
	// Input Assembler Stage - unique for every mesh
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	unsigned int stride = sizeof(VertexPosTex);
	unsigned int offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &pMeshComponent->g_d3dVertexBuffer, &stride, &offset);
	// Set the index buffer to active in the input assembler so it can be rendered.
	pDeviceContext->IASetIndexBuffer(pMeshComponent->g_d3dIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	if (pMeshComponent->m_pTexture != nullptr)
	{   //Pixel Shader Stafe - unique 4 every stage
		auto shaderResource = pMeshComponent->m_pTexture->GetTexture();
		pDeviceContext->PSSetShaderResources(0, 1, &shaderResource);
	}


	const auto& world = pTransformComponent->GetWorld();
	pDeviceContext->UpdateSubresource(pMeshComponent->d3dConstantBuffer, 0, nullptr, &world, 0, 0);

	pDeviceContext->DrawIndexedInstanced(pMeshComponent->indicesCount, 2, 0, 0, 0);

}

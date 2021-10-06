#include "pch.h"
#include "ToricRenderSystem.h"

#include "Entity.h"
#include "ToricTransformComponent.h"
#include "MeshComponent.h"
#include "Effect.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

ToricRenderSystem::ToricRenderSystem(unsigned int replicationCount, double torX, double torY, double torZ)
{
	SubscribeToComponentType<ToricTransformComponent>();
	SubscribeToComponentType<MeshComponent>();

	m_replicationCount = replicationCount;
	m_torX = torX >= 0 ? torX : 0;
	m_torY = torY >= 0 ? torY : 0;
	m_torZ = torZ >= 0 ? torZ : 0;
	ToricTransformComponent::SetTorusDimensions(torX, torY, torZ);

	m_instanceCountPerDimension = (2 * m_replicationCount + 1);
	//m_instanceCount = m_instanceCountPerDimension * m_instanceCountPerDimension * m_instanceCountPerDimension;

	m_instanceCount = 1;
	if (m_torX != 0)
		m_instanceCount *= m_instanceCountPerDimension;
	if (m_torY != 0)
		m_instanceCount *= m_instanceCountPerDimension;
	if (m_torZ != 0)
		m_instanceCount *= m_instanceCountPerDimension;

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
	//снизу - вообще все инстансы одинаковые в рамках кадра
	//но может сделать зависимыми от камеры? или оптимизировать?

	auto X_replicationCount = m_torX > 0 ? m_replicationCount : 0;
	auto Y_replicationCount = m_torY > 0 ? m_replicationCount : 0;
	auto Z_replicationCount = m_torZ > 0 ? m_replicationCount : 0;

	auto X_instanceCountPerDimension = m_torX > 0 ? m_instanceCountPerDimension : 1;
	auto Y_instanceCountPerDimension = m_torY > 0 ? m_instanceCountPerDimension : 1;
	auto Z_instanceCountPerDimension = m_torZ > 0 ? m_instanceCountPerDimension : 1;

	auto instances = new InstanceType[m_instanceCount];
	for (int Xi = -X_replicationCount; Xi <= X_replicationCount; Xi++)
	{
		double x = Xi * m_torX;
		for (int Yi = -Y_replicationCount; Yi <= Y_replicationCount; Yi++)
		{
			double y = Yi * m_torY;
			for (int Zi = -Z_replicationCount; Zi <= Z_replicationCount; Zi++)
			{
				double z = Zi * m_torZ;

				instances[(Zi + Z_replicationCount) * X_instanceCountPerDimension * Y_instanceCountPerDimension +
					(Yi + Y_replicationCount) * X_instanceCountPerDimension +
					(Xi + X_replicationCount)].position = Vector3(x, y, z);
			}
		}
	}

	D3D11_BUFFER_DESC instanceBufferDesc;
	ZeroMemory(&instanceBufferDesc, sizeof(D3D11_BUFFER_DESC));
	D3D11_SUBRESOURCE_DATA instanceData;
	HRESULT result;

	instanceBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//instanceBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	instanceBufferDesc.ByteWidth = sizeof(InstanceType) * m_instanceCount;
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = 0;
	//instanceBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	instanceBufferDesc.MiscFlags = 0;
	instanceBufferDesc.StructureByteStride = 0;

	instanceData.pSysMem = instances;
	instanceData.SysMemPitch = 0;
	instanceData.SysMemSlicePitch = 0;

	m_d3dInstanceBuffer = game.CreateBuffer(instanceBufferDesc, &instanceData);

	delete[] instances; //can be safely deleted - accorirding to the CreateBuffer specification
	instances = nullptr;

	//TODO: more optimal effect-wise traversal (and maybe create some dedicated claas for this traversal?)
	for (auto pEntity : m_entities)
	{
		if (pEntity->IsVisible())
			Render(pEntity, pDeviceContext);
	}
}

void ToricRenderSystem::Render(Entity* pEntity, ID3D11DeviceContext* pDeviceContext)
{
	//TransformComponent* pTransformComponent = pEntity->GetComponent<TransformComponent>();

	MeshComponent* pMeshComponent = pEntity->GetComponent<MeshComponent>();
	auto pEffect = pMeshComponent->GetEffect();

	if (!pEffect) //can be commented for debug purposes
	{
		std::cerr << "No effect found for the entity " << pEntity->GetName() << ", won't be rendered further!" << std::endl;
		pEntity->SetVisible(false);
		return;
	}

	// Input Assembler Stage - unique for every mesh
	// Set the vertex buffer to active in the input assembler so it can be rendered.

	////Each stride is the size (in bytes) of the elements that are to be used from that vertex buffer.
	const unsigned int vertexStrides[2] = { pEffect->GetVertexBufferSize(), sizeof(InstanceType) };
	const unsigned int offsets[2] = { 0, 0 };
	ID3D11Buffer* bufferPointers[2] = { pMeshComponent->GetVertexBuffer(), m_d3dInstanceBuffer };

	auto indexBuffer = pMeshComponent->GetIndexBuffer();
	pDeviceContext->IASetVertexBuffers(0, 2, bufferPointers, vertexStrides, offsets);
	// Set the index buffer to active in the input assembler so it can be rendered.
	pDeviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);
	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	pEffect->UpdatePerObject(pEntity);

	pDeviceContext->DrawIndexedInstanced(pMeshComponent->GetIndicesCount(), m_instanceCount, 0, 0, 0);
}
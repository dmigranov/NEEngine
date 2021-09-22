#include "pch.h"
#include "ToricTransformComponent.h"

ToricTransformComponent::ToricTransformComponent() : TransformComponent()
{ }

ToricTransformComponent::ToricTransformComponent(double x, double y, double z) : TransformComponent(x, y, z)
{ }

ToricTransformComponent::ToricTransformComponent(DirectX::SimpleMath::Vector3 position) : TransformComponent(position)
{ }

ToricTransformComponent::ToricTransformComponent(double x, double y, double z, double rx, double ry, double rz, double sx, double sy, double sz) : TransformComponent(x, y, z, rx, ry, rz, sx, sy, sz)
{ }

ToricTransformComponent::ToricTransformComponent(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 rotation, DirectX::SimpleMath::Vector3 scale) : TransformComponent(position, rotation, scale)
{ }

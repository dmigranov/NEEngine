#pragma once

enum class ComponentType
{

	TransformComponentType,
	MeshComponentType,
	PlayerComponentType,
	CameraComponentType,
	InputComponentType,
	BitmapComponentType,
	WalkComponentType,
	VelocityComponentType,


	TypeCount 
};

auto constexpr COMPONENT_TYPE_COUNT = (size_t)ComponentType::TypeCount;

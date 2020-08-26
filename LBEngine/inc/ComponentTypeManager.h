#pragma once

#include <set>

class ComponentTypeManager
{
public:
	template<typename T> void RegisterComponentType()
	{
		auto typeInfo = typeid(T);
	}

	int GetComponentTypesCount();

private:
	std::set<std::type_info> m_componentTypes;
};
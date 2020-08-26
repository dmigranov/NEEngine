#pragma once

#include <unordered_set>

class ComponentTypeManager
{
public:
	template<typename T> void RegisterComponentType()
	{
		if(m_typeAdditionPossible)
		{
			auto typeInfo = typeid(T);
			m_componentTypes.insert(typeInfo);
		}

	}

	void SetTypeAdditionEnded();

	int GetComponentTypesCount();

private:
	bool m_typeAdditionPossible = true;
	std::vector<std::type_info> m_componentTypes;
};
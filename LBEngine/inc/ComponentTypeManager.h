#pragma once

#include <unordered_set>
#include <typeindex>

class ComponentTypeManager
{
public:
	template<typename T> void RegisterComponentType()
	{
		if(m_typeAdditionPossible)
		{
			m_componentTypes.insert(m_componentTypes.begin(), typeid(T));
		}
	}

	void SetTypeAdditionEnded();

	int GetComponentTypesCount();

private:
	bool m_typeAdditionPossible = true;
	std::vector<std::type_index> m_componentTypes;
};
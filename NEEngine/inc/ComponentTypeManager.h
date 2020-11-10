#pragma once

#include <typeindex>
#include <map>

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

	template<typename T> unsigned int GetComponentTypeIndex()
	{
		return m_componentTypesMap[typeid(T)];
	}

private:
	bool m_typeAdditionPossible = true;
	std::vector<std::type_index> m_componentTypes;
	std::map<std::type_index, unsigned int> m_componentTypesMap;
	int m_componentTypesCount = 0;
};
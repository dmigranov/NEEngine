#include "pch.h"
#include "ComponentTypeManager.h"



void ComponentTypeManager::SetTypeAdditionEnded()
{
    m_typeAdditionPossible = false;
    //удаление повторов на всякий случай
    std::sort(m_componentTypes.begin(), m_componentTypes.end()); // {1 1 2 3 4 4 5}
    auto last = std::unique(m_componentTypes.begin(), m_componentTypes.end());
    m_componentTypes.erase(last, m_componentTypes.end());
}

int ComponentTypeManager::GetComponentTypesCount()
{
    return m_componentTypes.size();
}

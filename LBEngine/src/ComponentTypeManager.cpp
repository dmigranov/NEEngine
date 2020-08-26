#include "pch.h"
#include "ComponentTypeManager.h"



void ComponentTypeManager::SetTypeAdditionEnded()
{
    m_typeAdditionPossible = false;
    //todo: удалить лишнее из вектора (на всякий случай)
}

int ComponentTypeManager::GetComponentTypesCount()
{
    return m_componentTypes.size();
}

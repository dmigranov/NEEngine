#include "pch.h"
#include "CollisionSystem.h"
#include "..\inc\CollisionSystem.h"

CollisionSystem::CollisionSystem()
{
	SubscribeToComponentType(ComponentType::CollisionComponentType);

}

void CollisionSystem::Execute(DWORD deltaTime)
{

	for (auto i = m_entities.begin(); i != m_entities.end(); ++i) {
		for (auto j = i; ++j != m_entities.end(); /**/) {
			auto pEntityFirst = *i;
			auto pEntitySecond = *j;

			std::cout << pEntityFirst << " " << pEntitySecond << std::endl;
		}
	}
}

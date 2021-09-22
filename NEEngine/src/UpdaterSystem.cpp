#include "pch.h"
#include "UpdaterSystem.h"

#include "UpdaterComponent.h"

UpdaterSystem::UpdaterSystem() : System()
{
	SubscribeToComponentType<UpdaterComponent>();
}

#include "Entity.h"

namespace Wake
{
	namespace Entity
	{
		Entity::Entity(uint32 Id)
		{
			EntityId = Id;
			Active = true;
		}

		void Entity::Tick(float DeltaTime)
		{
		}
	}
}
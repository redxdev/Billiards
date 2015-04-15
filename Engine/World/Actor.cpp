#include "Actor.h"

#include "Component.h"

#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/quaternion.hpp>

#include <cassert>

Actor::Actor(ActorID Id, bool StartActive)
{
	AID = Id;
	Active = StartActive;
}

Actor::~Actor()
{
	
}

ActorID Actor::GetActorID() const
{
	return AID;
}

const std::list<Component*>& Actor::GetComponents() const
{
	return Components;
}

bool Actor::IsActive() const
{
	return Active;
}

void Actor::Activate()
{
	if (!Active)
	{
		Active = true;
		Activated();
	}
}

void Actor::Deactivate()
{
	if (Active)
	{
		Active = false;
		Deactivated();
	}
}

void Actor::ToggleActive()
{
	if (Active)
	{
		Deactivate();
	}
	else
	{
		Activate();
	}
}

void Actor::Spawn()
{
	if (Active)
	{
		Activate();
	}
}

void Actor::Destroy()
{
	for (auto Comp : Components)
	{
		Comp->Deactivate();
		Comp->Destroy();
		delete Comp;
	}

	Components.clear();
}

void Actor::Draw()
{
	for (auto Comp : Components)
	{
		if (Comp->IsActive())
		{
			Comp->Draw();
		}
	}
}

void Actor::Tick()
{
	for (auto Comp : Components)
	{
		if (Comp->IsActive())
		{
			Comp->Tick();
		}
	}
}

const glm::vec3& Actor::GetPosition() const
{
	return Position;
}

const glm::vec3& Actor::GetRotation() const
{
	return Rotation;
}

const glm::vec3& Actor::GetScale() const
{
	return Scale;
}

glm::mat4x4 Actor::CreateRotationMatrix() const
{
	return glm::rotate(Rotation[0], glm::vec3(1, 0, 0)) * glm::rotate(Rotation[1], glm::vec3(0, 1, 0)) * glm::rotate(Rotation[2], glm::vec3(0, 0, 1));
}

glm::mat4x4 Actor::CreateMatrix() const
{
	return glm::translate(Position) * CreateRotationMatrix() * glm::scale(Scale);
}

void Actor::SetPosition(const glm::vec3& Position)
{
	this->Position = Position;
}

void Actor::SetRotation(const glm::vec3& Rotation)
{
	this->Rotation = Rotation;
}

void Actor::SetScale(const glm::vec3& Scale)
{
	this->Scale = Scale;
}

glm::vec3 Actor::GetForward() const
{
	glm::vec4 Result = CreateRotationMatrix() * glm::vec4(0, 0, 1, 1);
	return glm::vec3(Result[0], Result[1], Result[2]);
}

glm::vec3 Actor::GetRight() const
{
	glm::vec4 Result = glm::normalize(CreateRotationMatrix() * glm::vec4(1, 0, 0, 1));
	return glm::vec3(Result[0], Result[1], Result[2]);
}

void Actor::Activated()
{
	
}

void Actor::Deactivated()
{
	
}
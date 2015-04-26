#pragma once

#include "../World/Actor.h"
#include "../World/StaticMeshComponent.h"

class Ball : public Actor
{
public:
	Ball(ActorID Id, bool StartActive = true);

	virtual ~Ball();

	virtual void Spawn() override;

	virtual void Tick() override;

	StaticMeshComponent* GetMeshComponent();

	const glm::vec2& GetVelocity() const;
	void SetVelocity(const glm::vec2& Val);

private:
	StaticMeshComponent* MeshComponent;

	glm::vec2 Velocity;
};
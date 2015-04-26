#include "Ball.h"

#include "../Engine/Mesh.h"
#include "../Engine/Shader.h"
#include "../Engine/GEngine.h"

#include "Game.h"

extern StaticMesh* BallMesh;
extern ShaderProgram* ColorProgram;

Ball::Ball(ActorID Id, bool StartActive)
	: Actor(Id, StartActive)
{
	
}

Ball::~Ball()
{
	
}


void Ball::Spawn()
{
	Actor::Spawn();

	MeshComponent = CreateComponent<StaticMeshComponent>(true, BallMesh, ColorProgram);
}

void Ball::Tick()
{
	Actor::Tick();

	SetPosition(GetPosition() + glm::vec3(Velocity, 0) * W_ENGINE.GetDeltaTime());
	Velocity *= 1.f - (GAME_FRICTION * W_ENGINE.GetDeltaTime());
	if (glm::length(Velocity) < 0.01f)
		Velocity = glm::vec2();
}

StaticMeshComponent* Ball::GetMeshComponent()
{
	return MeshComponent;
}

const glm::vec2& Ball::GetVelocity() const
{
	return Velocity;
}

void Ball::SetVelocity(const glm::vec2& Val)
{
	Velocity = Val;
}
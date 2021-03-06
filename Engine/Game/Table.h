#pragma once

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Texture.hpp>


#include "../World/Actor.h"
#include "../World/StaticMeshComponent.h"

class Table : public Actor
{
public:
	Table(ActorID Id, bool StartActive, GLuint Texture);

	virtual void Spawn() override;

	virtual void Draw() override;

private:
	StaticMeshComponent* MeshComponent;

	GLuint Texture;
};
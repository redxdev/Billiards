#include "Table.h"
#include "../Engine/Shader.h"

extern ShaderProgram* TextureProgram;
extern StaticMesh* TableMesh;

Table::Table(ActorID Id, bool StartActive, GLuint Texture)
	: Actor(Id, StartActive), Texture(Texture)
{
	
}

void Table::Spawn()
{
	Actor::Spawn();
	
	MeshComponent = CreateComponent<StaticMeshComponent>(true, TableMesh, TextureProgram);
}

void Table::Draw()
{
	glActiveTexture(Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);

	Actor::Draw();
}
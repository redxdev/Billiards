#include "Table.h"
#include "../Engine/Shader.h"

extern ShaderProgram* TextureProgram;
extern StaticMesh* TableMesh;

Table::Table(ActorID Id, bool StartActive, sf::Texture* Texture)
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
	sf::Texture::bind(Texture);

	Actor::Draw();

	sf::Texture::bind(nullptr);
}
#include "GameManager.h"

#include <gl/glew.h>
#include <SFML/Window.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/glm.hpp>

#include "../Engine/Mesh.h"
#include "../Engine/Shader.h"
#include "../Engine/GEngine.h"
#include "../World/World.h"

#include "Game.h"
#include "Ball.h"

ShaderProgram* ColorProgram;
StaticMesh* BallMesh;

ShaderProgram* TextureProgram;
StaticMesh* TableMesh;

Ball* CueBall;

void GM_Setup()
{
	ColorProgram = new ShaderProgram(ShaderProgram::LoadProgram("assets/shaders/basic.vert", "assets/shaders/basic.frag"));
	if (ColorProgram->GetProgram() == 0)
	{
		LOG_ERROR(GlobalLogger, "Something went wrong loading the shader program!");
	}

	W_ENGINE.Tick.Bind(&GM_Tick);

	W_INPUT.Bind("Action", INPUT_BIND(Mouse, Pressed, Left));
	W_INPUT.Bind("Action", INPUT_BIND(Mouse, Released, Left));

	W_INPUT.Event("Action").Bind(&GM_OnLeftClick);

	GLuint vbo;
	GLuint vao;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	float Vertices[50*2];
	float Scale = 0.05f;

	for (int i = 0; i < 50; ++i)
	{
		Vertices[i * 2] = cosf(glm::two_pi<float>() / 50 * i) * Scale;
		Vertices[i * 2 + 1] = sinf(glm::two_pi<float>() / 50 * i) * Scale;
	}

	GLint PositionAttr = glGetAttribLocation(ColorProgram->GetProgram(), "position");

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(PositionAttr, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(PositionAttr);

	BallMesh = new StaticMesh(vbo, vao, 50, GL_TRIANGLE_FAN);

	CueBall = W_WORLD.SpawnActor<Ball>(false); // start inactive
	CueBall->GetMeshComponent()->SetR(1);
	CueBall->GetMeshComponent()->SetB(1);
	CueBall->GetMeshComponent()->SetG(1);
}

void GM_Teardown()
{
	delete ColorProgram;
	delete BallMesh;
}

void GM_Tick()
{
	
}

glm::vec2 GetMouseCoords()
{
	auto Coords = sf::Mouse::getPosition(*(W_ENGINE.GetGameWindow().GetRenderWindow()));
	auto WorldCoords = glm::vec2(Coords.x, Coords.y);
	WorldCoords /= W_ENGINE.GetGameWindow().GetWidth();
	WorldCoords -= 0.5f;
	WorldCoords *= 2;
	WorldCoords[1] = -WorldCoords[1];
	return WorldCoords;
}

bool WasDown = false;
glm::vec2 MouseStart = glm::vec2();

void GM_OnLeftClick(const Input& Input)
{
	if (Input.Mode == EInputMode::Pressed)
	{
		if (CueBall->IsActive())
		{
			WasDown = true;
			MouseStart = GetMouseCoords();
		}
	}
	else
	{
		if (CueBall->IsActive())
		{
			if (WasDown)
			{
				if (CueBall->GetVelocity() == glm::vec2(0, 0))
				{
					glm::vec2 MouseEnd = GetMouseCoords();
					glm::vec2 Velocity = MouseStart - MouseEnd;
					CueBall->SetVelocity(Velocity * GAME_VELOCITY_MULTIPLIER);
				}
			}
		}
		else
		{
			auto WorldCoords = GetMouseCoords();
			glm::vec3 Pos = glm::vec3(WorldCoords[0], WorldCoords[1], 0);
			CueBall->SetPosition(Pos);
			CueBall->Activate();
		}
	}
}
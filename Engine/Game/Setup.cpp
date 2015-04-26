#include "Setup.h"

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>

#include <random>

#include "../Engine/GEngine.h"
#include "../Engine/InputManager.h"
#include "../Engine/Shader.h"
#include "../Engine/Mesh.h"
#include "../Logging/LogMacros.h"

#include "GameManager.h"

void Input_Stop(const Input& Input)
{
	W_ENGINE.Stop();
}

void GameSetup()
{
	W_INPUT.Bind("Exit", INPUT_BIND(Keyboard, Released, Escape));
	W_INPUT.Event("Exit").Bind(&Input_Stop);

	W_ENGINE.GetGameWindow().SetTitle("Billiards");

	GM_Setup();
}

void GameTeardown()
{
	GM_Teardown();

	// Actors do not need to be deleted; they are automatically deleted by the world when the engine stops.
	// See Engine/Bootstrap.cpp and World/World.cpp
}
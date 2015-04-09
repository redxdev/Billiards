#include "Window.h"

#include <GL/glew.h>

Window::Window()
{
	RenderWindow = nullptr;
}

Window::~Window()
{
	if (RenderWindow != nullptr)
	{
		if (RenderWindow->isOpen())
		{
			RenderWindow->close();
		}

		delete RenderWindow;
		RenderWindow = nullptr;
	}
}

bool Window::Initialize(const WindowOptions& Options)
{
	sf::ContextSettings CtxSettings;
	CtxSettings.antialiasingLevel = Options.AntiAliasing;
	CtxSettings.depthBits = Options.DepthBits;
	CtxSettings.stencilBits = Options.StencilBits;
	CtxSettings.majorVersion = Options.OGL_Major;
	CtxSettings.minorVersion = Options.OGL_Minor;

	if (!RenderWindow)
	{
		RenderWindow = new sf::Window();
	}

	RenderWindow->create(sf::VideoMode(Options.Width, Options.Height, Options.BitsPerPixel), Options.Title, Options.Fullscreen ? sf::Style::Fullscreen : sf::Style::Close, CtxSettings);
	RenderWindow->setActive(true);

	glewExperimental = GL_TRUE;
	glewInit();

	return true;
}

void Window::Deinitialize()
{
	if (RenderWindow != nullptr)
	{
		if (RenderWindow->isOpen())
		{
			RenderWindow->close();
		}

		delete RenderWindow;
		RenderWindow = nullptr;
	}

	Closed.Clear();
	Resized.Clear();
	LostFocus.Clear();
	GainedFocus.Clear();

	TextEntered.Clear();
	KeyPressed.Clear();
	KeyReleased.Clear();

	MouseButtonPressed.Clear();
	MouseButtonReleased.Clear();
	MouseWheelMoved.Clear();

	MouseMoved.Clear();
	MouseEntered.Clear();
	MouseLeft.Clear();
}

void Window::PollEvents()
{
	sf::Event Event;
	while (RenderWindow->pollEvent(Event))
	{
		switch (Event.type)
		{
		case sf::Event::Closed:
			Closed.Call();
			break;

		case sf::Event::Resized:
			Resized.Call(Event.size.width, Event.size.height);
			break;

		case sf::Event::LostFocus:
			LostFocus.Call();
			break;

		case sf::Event::GainedFocus:
			GainedFocus.Call();
			break;

		case sf::Event::TextEntered:
			TextEntered.Call(Event.text.unicode);
			break;

		case sf::Event::KeyPressed:
			KeyPressed.Call(ConvertSFKeyToInput(Event.key.code));
			break;

		case sf::Event::KeyReleased:
			KeyReleased.Call(ConvertSFKeyToInput(Event.key.code));
			break;

		case sf::Event::MouseButtonPressed:
			MouseButtonPressed.Call(ConvertSFMouseToInput(Event.mouseButton.button));
			break;

		case sf::Event::MouseButtonReleased:
			MouseButtonReleased.Call(ConvertSFMouseToInput(Event.mouseButton.button));
			break;

		case sf::Event::MouseWheelMoved:
			MouseWheelMoved.Call(Event.mouseWheel.delta);
			break;

		case sf::Event::MouseMoved:
			MouseMoved.Call(Event.mouseMove.x, Event.mouseMove.y);
			break;

		case sf::Event::MouseEntered:
			MouseEntered.Call();
			break;

		case sf::Event::MouseLeft:
			MouseLeft.Call();
			break;
		}
	}
}

bool Window::IsOpen()
{
	return RenderWindow->isOpen();
}
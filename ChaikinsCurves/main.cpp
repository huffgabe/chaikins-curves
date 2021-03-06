#include <vector>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "main.h"
#include "Curve.h"
#include "ProgramDrawable.h"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Chaikin's Curve Generator", sf::Style::Close, settings);
	window.setVerticalSyncEnabled(true);

	std::vector<sf::Color> vertexColors = {
		sf::Color::White, sf::Color::Red, sf::Color::Green, sf::Color::Blue
	};
	int colorIndex = 0;

	sf::Font font = loadFont();

	ProgramDrawable drawable = initializeDrawables(font);

	while (window.isOpen())
	{
		handleEvents(window, drawable, colorIndex, vertexColors);

		const sf::Vertex nextVertex((sf::Vector2f)sf::Mouse::getPosition(window), vertexColors[colorIndex]);
		drawable.curve.updateLastVertex(nextVertex);

		window.clear();
		window.draw(drawable);
		window.display();
	}

	return 0;
}

ProgramDrawable initializeDrawables(sf::Font& font)
{
	ProgramDrawable drawable;
	drawable.curve = initializeCurve();
	drawable.counter = initializeCounter(font);
	drawable.colorText = initializeColorText(font);
	return drawable;
}

Curve initializeCurve()
{
	sf::VertexArray controlPolygon(sf::LineStrip);
	controlPolygon.append(sf::Vertex(sf::Vector2f(0, 0), sf::Color::White));
	return Curve(controlPolygon, 0);
}

sf::Font loadFont()
{
	sf::Font font;
	if (!font.loadFromFile("calibri.ttf"))
	{
		throw std::runtime_error("Failed to load font calibri.ttf.");
	}
	return font;
}

sf::Text initializeCounter(sf::Font& font)
{
	sf::Text counter("0", font);
	counter.setFillColor(sf::Color::White);
	counter.setPosition(sf::Vector2f(windowWidth - 75, windowHeight - 75));
	return counter;
}

sf::Text initializeColorText(sf::Font& font)
{
	sf::Text colorText("White", font);
	colorText.setFillColor(sf::Color::White);
	colorText.setPosition(sf::Vector2f(50, windowHeight - 75));
	return colorText;
}

void handleEvents(sf::Window& window, ProgramDrawable& drawable, int& colorIndex, std::vector<sf::Color>& vertexColors)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::KeyPressed:
			handleKeyPressedEvent(drawable.curve, colorIndex, event.key.code);
			updateText(drawable, colorIndex);
			break;

		case sf::Event::MouseButtonPressed:
			drawable.curve.appendVertex(sf::Vertex((sf::Vector2f)sf::Mouse::getPosition(window), vertexColors[colorIndex]));
			break;

		default:
			break;
		}
	}
}

void handleKeyPressedEvent(Curve& curve, int& colorIndex, sf::Keyboard::Key keyCode)
{
	switch (keyCode)
	{
	case sf::Keyboard::Right:
		curve.incrementIterations();
		break;

	case sf::Keyboard::Left:
		curve.decrementIterations();
		break;

	case sf::Keyboard::Up:
		colorIndex = (colorIndex + 1) % 4;
		break;

	case sf::Keyboard::Down:
		if (colorIndex == 0)
		{
			colorIndex = 3;
		}
		else
		{
			colorIndex = (colorIndex - 1) % 4;
		}
		break;

	case sf::Keyboard::Space:
		curve.reset();
		break;

	default:
		break;
	}
}

void updateText(ProgramDrawable& drawable, int& colorIndex)
{
	drawable.counter.setString(std::to_string(drawable.curve.iterations()));
	drawable.colorText.setString(colorTexts[colorIndex]);
}

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
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Chaikin's Curve Generator", sf::Style::Close, settings);
	window.setVerticalSyncEnabled(true);

	std::vector<sf::Color> vertexColors = {
		sf::Color::White, sf::Color::Red, sf::Color::Green, sf::Color::Blue
	};
	int colorIndex = 0;

	/* font needs to stay alive for the duration of the program, otherwise
		an exception is thrown when trying to use an sf::Text */
	sf::Font font;
	try {
		font = loadFont();
	}
	catch (std::runtime_error &e) {
		return -1;
	}

	ProgramDrawable drawable = initializeDrawables(font);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed) {
				updateCurveIterations(drawable.curve, drawable.counter, event.key.code);
				updateVertexColor(colorIndex, drawable.colorText, event.key.code);
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				sf::VertexArray controlPolygon = drawable.curve.getControlPolygon();
				controlPolygon.append(sf::Vertex((sf::Vector2f)sf::Mouse::getPosition(window), vertexColors[colorIndex]));
				drawable.curve.setControlPolygon(controlPolygon);
			}
		}

		sf::Vertex nextVertex((sf::Vector2f)sf::Mouse::getPosition(window), vertexColors[colorIndex]);
		sf::VertexArray controlPolygon = drawable.curve.getControlPolygon();
		if (controlPolygon.getVertexCount() > 0) {
			controlPolygon[controlPolygon.getVertexCount() - 1] = nextVertex;
			drawable.curve.setControlPolygon(controlPolygon);
		}

		window.clear();
		window.draw(drawable);
		window.display();
	}

	return 0;
}

ProgramDrawable initializeDrawables(sf::Font &font)
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
	if (!font.loadFromFile("calibri.ttf")) {
		throw std::runtime_error("Failed to load font.");
	}
	return font;
}

sf::Text initializeCounter(sf::Font &font)
{
	sf::Text counter("0", font);
	counter.setFillColor(sf::Color::White);
	counter.setPosition(sf::Vector2f(WINDOW_WIDTH - 75, WINDOW_HEIGHT - 75));
	return counter;
}

sf::Text initializeColorText(sf::Font &font)
{
	sf::Text colorText("White", font);
	colorText.setFillColor(sf::Color::White);
	colorText.setPosition(sf::Vector2f(50, WINDOW_HEIGHT - 75));
	return colorText;
}

void updateCurveIterations(Curve &curve, sf::Text &counter, sf::Keyboard::Key keyCode)
{
	int iterations = curve.getIterations();

	if (keyCode == sf::Keyboard::Right) {
		iterations++;
	}
	else if (keyCode == sf::Keyboard::Left) {
		if (iterations > 0) {
			iterations--;
		}
	}
	else if (keyCode == sf::Keyboard::Space) {
		sf::VertexArray controlPolygon(sf::LineStrip);
		controlPolygon.append(sf::Vertex(sf::Vector2f(0, 0), sf::Color::White));
		curve.setControlPolygon(controlPolygon);
		return;
	}
	else {
		return;
	}

	curve.setIterations(iterations);

	counter.setString(std::to_string(iterations));
}

void updateVertexColor(int &colorIndex, sf::Text &colorText, sf::Keyboard::Key keyCode)
{
	std::vector<std::string> colorTexts = { "White", "Red", "Green", "Blue" };

	if (keyCode == sf::Keyboard::Up) {
		colorIndex = (colorIndex + 1) % 4;
	}
	else if (keyCode == sf::Keyboard::Down) {
		if (colorIndex == 0) {
			colorIndex = 3;
		}
		else {
			colorIndex = (colorIndex - 1) % 4;
		}
	}
	else {
		return;
	}

	colorText.setString(colorTexts[colorIndex]);
}

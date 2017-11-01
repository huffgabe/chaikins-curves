#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "main.h"
#include "Curve.h"

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

	sf::Font font;
	if (!font.loadFromFile("calibri.ttf")) {
		return -1;
	}

	Curve curve;
	initializePrimitives(curve);

	sf::Text counter("0", font);
	counter.setFillColor(sf::Color::White);
	counter.setPosition(sf::Vector2f(WINDOW_WIDTH - 75, WINDOW_HEIGHT - 75));

	sf::Text colorText("White", font);
	colorText.setFillColor(sf::Color::White);
	colorText.setPosition(sf::Vector2f(50, WINDOW_HEIGHT - 75));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed) {
				updateCurveIterations(curve, counter, event.key.code);
				updateVertexColor(colorIndex, colorText, event.key.code);
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				sf::VertexArray controlPolygon = curve.getControlPolygon();
				controlPolygon.append(sf::Vertex((sf::Vector2f)sf::Mouse::getPosition(window), vertexColors[colorIndex]));
				curve.setControlPolygon(controlPolygon);
			}
		}

		sf::Vertex nextVertex((sf::Vector2f)sf::Mouse::getPosition(window), vertexColors[colorIndex]);
		sf::VertexArray controlPolygon = curve.getControlPolygon();
		if (controlPolygon.getVertexCount() > 0) {
			controlPolygon[controlPolygon.getVertexCount() - 1] = nextVertex;
			curve.setControlPolygon(controlPolygon);
		}

		window.clear();

		window.draw(curve);
		window.draw(counter);
		window.draw(colorText);

		window.display();
	}

	return 0;
}

void initializePrimitives(Curve &curve)
{
	sf::VertexArray controlPolygon(sf::LineStrip);
	controlPolygon.append(sf::Vertex(sf::Vector2f(0, 0), sf::Color::White));
	curve = Curve(controlPolygon, 0);
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

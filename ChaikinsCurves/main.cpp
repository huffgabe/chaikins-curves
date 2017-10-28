#include <vector>
#include <random>
#include <memory>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Curve.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

void initializePrimitives(std::vector<std::unique_ptr<sf::Drawable>> &primitives)
{
	sf::VertexArray controlPolygon(sf::LineStrip, 6);
	int x = 300;
	int y = 50;
	int dx = 200;
	int dy = 60;

	for (int i = 0; i < 6; i++) {
		controlPolygon[i] = sf::Vertex(sf::Vector2f(x, y), sf::Color::White);
		dx -= 60;
		dy += 10;
		x += dx;
		y += dy;
	}

	primitives.push_back(std::make_unique<Curve>(controlPolygon, 0));
}

void updateState(std::vector<std::unique_ptr<sf::Drawable>> &primitives, sf::Window &window)
{
}

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Chaikin's Curve Generator", sf::Style::Close, settings);
	window.setVerticalSyncEnabled(true);

	std::vector<std::unique_ptr<sf::Drawable>> primitives;
	initializePrimitives(primitives);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		updateState(primitives, window);

		window.clear();

		for (auto &primitive : primitives) {
			window.draw(*primitive);
		}

		window.display();
	}

	return 0;
}
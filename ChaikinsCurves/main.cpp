#include <vector>
#include <random>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Curve.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

void initializePrimitives(std::vector<sf::Drawable> &primitives)
{
}

void updateState(std::vector<sf::Drawable> &primitives, sf::Window &window)
{
}

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Chaikin's Curve Generator", sf::Style::Close, settings);
	window.setVerticalSyncEnabled(true);

	std::vector<sf::Drawable> primitives;
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
			window.draw(primitive);
		}

		window.display();
	}

	return 0;
}
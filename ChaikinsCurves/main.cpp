#include <vector>
#include <random>
#include <memory>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Curve.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

void initializePrimitives(std::vector<Curve> &curves)
{
	sf::VertexArray controlPolygon(sf::LineStrip, 6);
	int x = 300;
	int y = 50;
	int dx = 200;
	int dy = 40;

	for (int i = 0; i < 6; i++) {
		sf::Color color;
		if (i % 2 == 0) {
			color = sf::Color::Red;
		}
		else {
			color = sf::Color::Green;
		}
		controlPolygon[i] = sf::Vertex(sf::Vector2f(x, y), color);
		dx -= 70;
		dy += 10;
		x += dx;
		y += dy;
	}

	curves.push_back(Curve(controlPolygon, 0));
}

void updateState(std::vector<Curve> &curves, sf::Window &window)
{
}

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Chaikin's Curve Generator", sf::Style::Close, settings);
	window.setVerticalSyncEnabled(true);

	std::vector<Curve> curves;
	initializePrimitives(curves);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Right) {
					curves[0].setIterations(curves[0].getIterations() + 1);
				}
				else if (event.key.code == sf::Keyboard::Left) {
					curves[0].setIterations(curves[0].getIterations() - 1);
				}
				break;

			default:
				break;
			}
		}

		updateState(curves, window);

		window.clear();

		for (auto &curve : curves) {
			window.draw(curve);
		}

		window.display();
	}

	return 0;
}

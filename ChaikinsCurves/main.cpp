#include <vector>
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

void updateCurveIterations(std::vector<Curve> &curves, sf::Text &counter, sf::Keyboard::Key keyCode)
{
	int iterations = curves[0].getIterations();

	if (keyCode == sf::Keyboard::Right) {
		iterations++;
	}
	else if (keyCode == sf::Keyboard::Left) {
		if (iterations > 0) {
			iterations--;
		}
	}

	for (auto &curve : curves) {
		curve.setIterations(iterations);
	}

	counter.setString(std::to_string(iterations));
}

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Chaikin's Curve Generator", sf::Style::Close, settings);
	window.setVerticalSyncEnabled(true);

	sf::Font font;
	if (!font.loadFromFile("calibri.ttf")) {
		return -1;
	}

	std::vector<Curve> curves;
	initializePrimitives(curves);

	sf::Text counter("0", font);
	counter.setFillColor(sf::Color::White);
	counter.setPosition(sf::Vector2f(WINDOW_WIDTH - 75, WINDOW_HEIGHT - 75));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed) {
				updateCurveIterations(curves, counter, event.key.code);
			}
		}

		updateState(curves, window);

		window.clear();

		for (auto &curve : curves) {
			window.draw(curve);
		}
		window.draw(counter);

		window.display();
	}

	return 0;
}

#include <vector>
#include <SFML/Graphics.hpp>
#include "Curve.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

void initializePrimitives(std::vector<Curve> &curves)
{
	sf::VertexArray controlPolygon(sf::LineStrip);
	curves.push_back(Curve(controlPolygon, 0));
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
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Chaikin's Curve Generator", sf::Style::Close);
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
			else if (event.type == sf::Event::MouseButtonPressed) {
				sf::VertexArray controlPolygon = curves[0].getControlPolygon();
				controlPolygon.append(sf::Vertex((sf::Vector2f)sf::Mouse::getPosition(window), sf::Color::White));
				curves[0].setControlPolygon(controlPolygon);
			}
		}

		window.clear();

		for (auto &curve : curves) {
			window.draw(curve);
		}
		window.draw(counter);

		window.display();
	}

	return 0;
}

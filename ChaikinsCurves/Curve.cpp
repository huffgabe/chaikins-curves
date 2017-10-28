#include "Curve.h"
#include <SFML/Graphics.hpp>

Curve::Curve(sf::VertexArray controlPolygon, int iterations) :
	controlPolygon(controlPolygon), iterations(iterations)
{
	buildCurve();
}

Curve::~Curve()
{
}

void Curve::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(generatedCurve, states);
}

void Curve::setIterations(int iterations)
{
	if (iterations < 0) {
		this->iterations = 0;
	}
	else {
		this->iterations = iterations;
	}

	buildCurve();
}

int Curve::getIterations()
{
	return this->iterations;
}

void Curve::buildCurve()
{
	generatedCurve = controlPolygon;

	for (int i = 0; i < iterations; i++) {
		int vertices = generatedCurve.getVertexCount();
		sf::VertexArray newCurve(sf::LineStrip);

		for (int j = 0; j < vertices - 1; j++) {
			sf::Vector2f displacement = generatedCurve[j + 1].position - generatedCurve[j].position;
			sf::Vector2f newPoint1 = generatedCurve[j].position + (0.25f * displacement);
			sf::Vector2f newPoint2 = generatedCurve[j].position + (0.75f * displacement);

			newCurve.append(sf::Vertex(newPoint1, generatedCurve[j].color));
			newCurve.append(sf::Vertex(newPoint2, generatedCurve[j + 1].color));
		}

		generatedCurve = newCurve;
	}
}

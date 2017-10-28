#include <SFML/Graphics.hpp>
#include "Curve.h"

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
	this->iterations = iterations;
	buildCurve();
}

void Curve::buildCurve()
{
}

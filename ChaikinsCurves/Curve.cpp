#include <SFML/Graphics.hpp>
#include "Curve.h"

Curve::Curve()
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

void Curve::buildCurve()
{
}

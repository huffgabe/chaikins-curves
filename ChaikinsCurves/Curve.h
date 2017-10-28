#pragma once

#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class Curve : public sf::Drawable, public sf::Transformable
{
public:
	Curve();
	~Curve();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	// Builds the generatedCurve from controlPolygon.
	void buildCurve();

private:
	// The original control polygon for this curve.
	sf::VertexArray controlPolygon;
	// The curve generated after running Chaikin's algorithm.
	sf::VertexArray generatedCurve;
	// The number of times to run the Chaikin's curve algorithm.
	int iterations;
};

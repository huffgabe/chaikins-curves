#pragma once

#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class Curve : public sf::Drawable, public sf::Transformable
{
public:
	Curve(sf::VertexArray controlPolygon, int iterations);
	~Curve();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	// Builds the generatedCurve from controlPolygon.
	void buildCurve();

	// Set number of iterations and rebuild curve.
	void setIterations(int iterations);

private:
	// The original control polygon for this curve.
	sf::VertexArray controlPolygon;
	// The curve generated after running Chaikin's algorithm.
	sf::VertexArray generatedCurve;
	// The number of times to run the Chaikin's curve algorithm.
	int iterations;
};

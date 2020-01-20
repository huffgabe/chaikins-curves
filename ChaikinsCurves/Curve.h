#pragma once

#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class Curve : public sf::Drawable
{
public:
	Curve();
	Curve(sf::VertexArray controlPolygon, int iterations);
	~Curve();

	void iterations(int iterations);
	int iterations() const;

	void controlPolygon(const sf::VertexArray& controlPolygon);
	sf::VertexArray controlPolygon() const;

	void updateLastVertex(const sf::Vertex& vertex);
	void appendVertex(const sf::Vertex& vertex);
	void reset();

private:
	// The original control polygon for this curve.
	sf::VertexArray _controlPolygon;
	// The number of times to run the Chaikin's curve algorithm.
	int _iterations;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// Builds the generated curve from controlPolygon.
	sf::VertexArray buildCurve() const;
};

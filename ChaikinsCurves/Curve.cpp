#include <SFML/Graphics.hpp>
#include "Curve.h"

Curve::Curve()
{
}

Curve::Curve(sf::VertexArray controlPolygon, int iterations) :
	_controlPolygon(controlPolygon), _iterations(iterations)
{
}

Curve::~Curve()
{
}

void Curve::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(buildCurve(), states);
}

void Curve::iterations(int iterations)
{
	if (iterations < 0)
	{
		this->_iterations = 0;
	}
	else
	{
		this->_iterations = iterations;
	}
}

int Curve::iterations() const
{
	return this->_iterations;
}

void Curve::controlPolygon(const sf::VertexArray& controlPolygon)
{
	this->_controlPolygon = controlPolygon;
}

sf::VertexArray Curve::controlPolygon() const
{
	return this->_controlPolygon;
}

void Curve::updateLastVertex(const sf::Vertex& vertex)
{
	const int vertexCount = _controlPolygon.getVertexCount();
	if (vertexCount <= 0) return;
	_controlPolygon[vertexCount - 1] = vertex;
}

void Curve::appendVertex(const sf::Vertex& vertex)
{
	_controlPolygon.append(vertex);
}

void Curve::reset()
{
	sf::VertexArray controlPolygon(sf::LineStrip);
	controlPolygon.append(sf::Vertex(sf::Vector2f(0, 0), sf::Color::White));
	_controlPolygon = controlPolygon;
}

sf::VertexArray Curve::buildCurve() const
{
	sf::VertexArray generatedCurve = _controlPolygon;

	for (int i = 0; i < _iterations; i++)
	{
		int vertices = generatedCurve.getVertexCount();
		sf::VertexArray newCurve(_controlPolygon.getPrimitiveType());

		for (int j = 0; j < vertices - 1; j++)
		{
			sf::Vector2f displacement = generatedCurve[j + 1].position - generatedCurve[j].position;
			sf::Vector2f newPoint1 = generatedCurve[j].position + (0.25f * displacement);
			sf::Vector2f newPoint2 = generatedCurve[j].position + (0.75f * displacement);

			newCurve.append(sf::Vertex(newPoint1, generatedCurve[j].color));
			newCurve.append(sf::Vertex(newPoint2, generatedCurve[j + 1].color));
		}

		generatedCurve = newCurve;
	}

	return generatedCurve;
}

#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Curve.h"

class ProgramDrawable : public sf::Drawable
{
public:
	ProgramDrawable();
	~ProgramDrawable();

	Curve curve;
	sf::Text counter;
	sf::Text colorText;

private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

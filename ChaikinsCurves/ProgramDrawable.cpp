#include <SFML/Graphics.hpp>
#include "ProgramDrawable.h"

ProgramDrawable::ProgramDrawable()
{
}

ProgramDrawable::~ProgramDrawable()
{
}

void ProgramDrawable::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(curve, states);
	target.draw(counter, states);
	target.draw(colorText, states);
}

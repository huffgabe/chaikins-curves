#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Curve.h"

class Program
{
public:
	static int main();
private:
	static void updateCurveIterations(Curve &curve, sf::Text &counter, sf::Keyboard::Key keyCode);
	static void updateVertexColor(int &colorIndex, sf::Text &colorText, sf::Keyboard::Key keyCode);
};

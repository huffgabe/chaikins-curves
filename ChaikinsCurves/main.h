#pragma once

#include <vector>
#include "Curve.h"
#include "ProgramDrawable.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

ProgramDrawable initializeDrawables(sf::Font &font);
Curve initializeCurve();
sf::Font loadFont();
sf::Text initializeCounter(sf::Font &font);
sf::Text initializeColorText(sf::Font &font);
void handleEvents(sf::Window &window, ProgramDrawable &drawable, int &colorIndex, std::vector<sf::Color> &vertexColors);
void updateCurveIterations(Curve &curve, sf::Text &counter, sf::Keyboard::Key keyCode);
void updateVertexColor(int &colorIndex, sf::Text &colorText, sf::Keyboard::Key keyCode);

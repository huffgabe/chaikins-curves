#pragma once

#include <vector>
#include "Curve.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

Curve initializeCurve();
sf::Font loadFont();
std::vector<sf::Text> initializeTexts(sf::Font &font);
sf::Text initializeCounter(sf::Font &font);
sf::Text initializeColorText(sf::Font &font);
void updateCurveIterations(Curve &curve, sf::Text &counter, sf::Keyboard::Key keyCode);
void updateVertexColor(int &colorIndex, sf::Text &colorText, sf::Keyboard::Key keyCode);

#pragma once

#include <vector>
#include "Curve.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

void initializeDrawables(Curve &curve, sf::Text &counter, sf::Text &colorText);
void updateCurveIterations(Curve &curve, sf::Text &counter, sf::Keyboard::Key keyCode);
void updateVertexColor(int &colorIndex, sf::Text &colorText, sf::Keyboard::Key keyCode);

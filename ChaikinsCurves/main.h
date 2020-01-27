#pragma once

#include <vector>
#include "Curve.h"
#include "ProgramDrawable.h"

constexpr int windowWidth = 800;
constexpr int windowHeight = 600;
const std::vector<std::string> colorTexts = { "White", "Red", "Green", "Blue" };

ProgramDrawable initializeDrawables(sf::Font& font);
Curve initializeCurve();
sf::Font loadFont();
sf::Text initializeCounter(sf::Font& font);
sf::Text initializeColorText(sf::Font& font);
void handleEvents(sf::Window& window, ProgramDrawable& drawable, int& colorIndex, std::vector<sf::Color>& vertexColors);
void updateCurveIterations(Curve& curve, sf::Text& counter, sf::Keyboard::Key keyCode);
void updateVertexColor(int& colorIndex, sf::Text& colorText, sf::Keyboard::Key keyCode);
void handleKeyPressedEvent(Curve& curve, int& colorIndex, sf::Keyboard::Key keyCode);
void updateText(ProgramDrawable& drawable, int& colorIndex);

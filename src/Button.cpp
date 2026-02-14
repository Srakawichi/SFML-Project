// Button.cpp
#include "Button.hpp"
#include <iostream>

Button::Button(float x, float y, float width, float height, const std::string& text, sf::Font& font) {
    buttonShape.setPosition(x, y);
    buttonShape.setSize(sf::Vector2f(width, height));
    buttonShape.setFillColor(sf::Color::Red);

    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(30);
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setPosition(
        x + width / 2 - buttonText.getGlobalBounds().width / 2,
        y + height / 2 - buttonText.getGlobalBounds().height / 2
    );
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(buttonShape);
    window.draw(buttonText);
}

bool Button::isMouseOver(sf::Vector2i mousePos) {
    return buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

void Button::setOnClick(const std::function<void()>& func) {
    onClick = func;
}

void Button::setEnabled(bool enabled) {
    isEnabled = enabled;
    buttonShape.setFillColor(enabled ? sf::Color::White : sf::Color(128, 128, 128)); // Gray if disabled
}


void Button::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (!isEnabled) return;

    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (isMouseOver(mousePos)) {
            // Counter erhöhen und in der Konsole ausgeben
            clickCounter++;
            std::cout << "Button wurde " << clickCounter << " Mal geklickt." << std::endl;

            if (onClick) {
                onClick(); // Klick-Funktion ausführen
            }
        }
    }
}

void Button::setLabel(const std::string& newLabel) {
    buttonText.setString(newLabel);
    // Update the position of the text to keep it centered
    buttonText.setPosition(
        buttonShape.getPosition().x + (buttonShape.getSize().x - buttonText.getGlobalBounds().width) / 2,
        buttonShape.getPosition().y + (buttonShape.getSize().y - buttonText.getGlobalBounds().height) / 2
    );
}




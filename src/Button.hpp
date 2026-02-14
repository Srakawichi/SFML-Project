// Button.hpp
#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <functional>

class Button {
public:
    Button(float x, float y, float width, float height, const std::string& text, sf::Font& font);
    void draw(sf::RenderWindow& window);
    bool isMouseOver(sf::Vector2i mousePos);
    void setOnClick(const std::function<void()>& func);
    void setColor(const sf::Color& color);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void setEnabled(bool enabled); // New method to enable/disable
    void setLabel(const std::string& newLabel); // New method to update the label

private:
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
    std::function<void()> onClick;
    int clickCounter = 0; // Zähler für Klicks
    bool isEnabled = true; // New state variable (default: enabled)
};

#endif // BUTTON_HPP

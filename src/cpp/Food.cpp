#include "../include/Food.hpp"

Food::Food(int x, int y) : x(x), y(y) {
    setColor(sf::Color::Red);
}

int Food::getX() const {
    return x;
}

int Food::getY() const {
    return y;
}

void Food::setX(int x) {
    this->x = x;
}

void Food::setY(int y) {
    this->y = y;
}

void Food::setColor(const sf::Color& color) {
    this->color = color;
}

sf::Color Food::getColor() const {
    return color;
}

void Food::draw(sf::RenderWindow& window) {
    sf::RectangleShape food(sf::Vector2f(20, 20));
    food.setPosition(x * 20, y * 20);
    food.setFillColor(color);
    window.draw(food);
}

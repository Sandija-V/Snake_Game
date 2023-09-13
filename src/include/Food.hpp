#ifndef FOOD_HPP
#define FOOD_HPP

#include <SFML/Graphics.hpp>

class Food {
public:
    Food(int x, int y);

    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);
    void setColor(const sf::Color& color);
    sf::Color getColor() const;
    void draw(sf::RenderWindow& window);

private:
    int x;
    int y;
    sf::Color color;
};

#endif // FOOD_HPP

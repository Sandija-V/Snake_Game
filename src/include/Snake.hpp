#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <SFML/Graphics.hpp>
#include "Food.hpp"

class Snake {
public:
	// Define the Node struct within the Snake class
    struct Node {
        int x, y;
        Node* next = nullptr;
    };

    Snake(int x, int y, int length, int speed, int direction);

     // Accessors and mutators for Snake properties
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);
    int getLength() const;
    void setLength(int length);
    int getSpeed() const;
    void setSpeed(int speed);
    void setDirection(int direction);
    int getDirection() const;
    Node* getHead() const;

    // Snake movement and rendering functions
    void move();
    void draw(sf::RenderWindow& window);

    // Collision detection functions
    bool checkCollisionWithItself();
    bool checkCollision(Food& food);

    // Helper function for color checking
    bool isColorTooDark(const sf::Color& color);

    // Game state control functions
    void pause();
    void start();
    bool isPaused() const;

private:
	Node m_head { 0, 0, nullptr };
	Node* head = &m_head;
	int length;
	int speed;
	int direction; // 0 = up, 1 = right, 2 = down, 3 = left
	int m_direction;
	bool paused = false;
};

#endif // SNAKE_HPP
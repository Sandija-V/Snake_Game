#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cstdlib> // For rand()
#include <sstream> // For std::stringstream
#include "include/Food.hpp"
#include "include/Snake.hpp"
#include "include/LoginScreen.hpp"

int main() {

	LoginScreen loginScreen;
    loginScreen.run();

	// Create the game window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Snake Game");

	// Create the snake object
	Snake snake(10, 10, 8, 5, 1);
	Food food(5, 5);

    // init clock
    sf::Clock clock;
    sf::Time lt = clock.getElapsedTime();

	// Game loop
	while (window.isOpen()) {
		// Handle events
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Up && snake.getDirection() != 2) {
					snake.setDirection(0);
				}
				else if (event.key.code == sf::Keyboard::Right && snake.getDirection() != 3) {
					snake.setDirection(1);
				}
				else if (event.key.code == sf::Keyboard::Down && snake.getDirection() != 0) {
					snake.setDirection(2);
				}
				else if (event.key.code == sf::Keyboard::Left && snake.getDirection() != 1) {
					snake.setDirection(3);
				}
				else if (event.key.code == sf::Keyboard::Space) {
                    if (snake.isPaused()) {
                        snake.start();
                    }
                    else {
                        snake.pause();
					}
				}
			}
		}

		// Clear the window
		window.clear();

		if (!snake.isPaused()) {
			//ged diference from lt to now
            sf::Time now = clock.getElapsedTime();
			sf::Time diff = now - lt;
			if (diff.asMilliseconds() > 1000 / snake.getSpeed()) {
				lt = now;
				snake.move();
			}
        }

		// Draw the snake
		snake.draw(window);
		// Draw the food
		food.draw(window);

		(snake.checkCollision(food));

		if(snake.checkCollisionWithItself()) {
			snake = Snake(10, 10, 8, 5, 1);
		}

		// Update the window
		window.display();
		//sf::sleep(sf::milliseconds(1000 / (snake.getSpeed())));
	}

	// LoginScreen loginScreen;
    // loginScreen.run();

	return 0;
}

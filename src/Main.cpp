#include <SFML/Graphics.hpp>

class Snake {
public:
	struct Node {
		int x, y;
		Node* next = nullptr;
	};

	//constructor
	Snake(int x, int y, int length, int speed, int direction) :
		m_head { x, y, nullptr },
		length { length },
		speed { speed },
		direction { direction },
		m_direction { direction } {
        head = new Node { x, y, nullptr };
        Node* current = head;
        for (int i = 1; i < length; i++) {
            current->next = new Node { x, y + i, nullptr };
            current = current->next;
        }
		this->length = length;
		this->speed = speed;
		this->direction = direction;
	}

	// Get the x coordinate of the head of the snake
	int getX() const {
		return head->x;
	}

	// Get the y coordinate of the head of the snake
	int getY() const {
		return head->y;
	}

	// Set the x coordinate of the head of the snake
	void setX(int x) {
		head->x = x;
	}

	// Set the y coordinate of the head of the snake
	void setY(int y) {
		head->y = y;
	}

	// Get the length of the snake
	int getLength() const {
		return length;
	}

	// Set the length of the snake
	void setLength(int length) {
		if (length >= 1) {
			// Only allow lengths of 1 or more
			Node* current = head;
			while (current->next != nullptr) {
				current = current->next;
			}
			for (int i = this->length; i < length; i++) {
				current->next = new Node { current->x, current->y, nullptr };
				current = current->next;
			}
			this->length = length;
		}
	}

	// Get the speed of the snake
	int getSpeed() const {
		return speed;
	}

	// Set the speed of the snake
	void setSpeed(int speed) {
		if (speed >= 1) {
			// Only allow speeds of 1 or more
			this->speed = speed;
		}
	}

	// Set the direction of the snake's movement
	void setDirection(int direction) {
		if (direction >= 0 && direction <= 3) {
			// Only allow directions between 0 and 3
			m_direction = direction;
		}
	}

	// Get the direction of the snake's movement
	int getDirection() const {
		return m_direction;
	}

	void move() {
		// Move the head in the direction of the snake
		Node* newHead = new Node { head->x, head->y, head };

		switch (m_direction) {
			case 0: newHead->y--; break; // Up
			case 1: newHead->x++; break; // Right
			case 2: newHead->y++; break; // Down
			case 3: newHead->x--; break; // Left
			default: break;
		}

		// test out of bounds
		if (newHead->x > 39) {
			newHead->x = 0;
		}
		if (newHead->x < 0) {
			newHead->x = 39;
		}
		if (newHead->y > 29) {
			newHead->y = 0;
		}
		if (newHead->y < 0) {
			newHead->y = 29;
		}

		head = newHead;

		// Move the rest of the body to follow the head
		Node* current = head;
		while (current->next->next != nullptr) {
			current = current->next;
		}
		delete current->next;
		current->next = nullptr;
	}

	// Draw the snake on the screen
	void draw(sf::RenderWindow& window) {
		Node* current = head;
		while (current != nullptr) {
			sf::RectangleShape segment(sf::Vector2f(20, 20));
			segment.setPosition(current->x * 20, current->y * 20);
			window.draw(segment);
			current = current->next;
		}
	}

	// Get the head of the snake
	Node* getHead() const {
		return head;
	}

private:
	Node m_head { 0, 0, nullptr };
	Node* head = &m_head;
	int length;
	int speed;
	int direction; // 0 = up, 1 = right, 2 = down, 3 = left
	int m_direction;
};

int main() {
	// Create the game window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Snake Game");

	// Create the snake object
	Snake snake(10, 10, 8, 5, 1);

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
			}
		}
		// Clear the window
		window.clear();

        //ged diference from lt to now
        sf::Time now = clock.getElapsedTime();
        sf::Time diff = now - lt;
        if (diff.asMilliseconds() > 1000 / snake.getSpeed()) {
            lt = now;
            snake.move();
        }

		//snake.move();

		// Draw the snake
		snake.draw(window);

		// Update the window
		window.display();
		sf::sleep(sf::milliseconds(1000 / (snake.getSpeed())));
	}

	return 0;
}

#include "../include/Snake.hpp"
#include "../include/Food.hpp"

//constructor
Snake::Snake(int x, int y, int length, int speed, int direction) :
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
int Snake::getX() const {
	return head->x;
}

// Get the y coordinate of the head of the snake
int Snake::getY() const {
	return head->y;
}

// Set the x coordinate of the head of the snake
void Snake::setX(int x) {
	head->x = x;
}

// Set the y coordinate of the head of the snake
void Snake::setY(int y) {
	head->y = y;
}

// Get the length of the snake
int Snake::getLength() const {
	return length;
}

// Set the length of the snake
void Snake::setLength(int length) {
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
int Snake::getSpeed() const {
	return speed;
}

// Set the speed of the snake
void Snake::setSpeed(int speed) {
	if (speed >= 1) {
		// Only allow speeds of 1 or more
		this->speed = speed;
	}
}

// Set the direction of the snake's movement
void Snake::setDirection(int direction) {
	if (direction >= 0 && direction <= 3) {
		// Only allow directions between 0 and 3
		m_direction = direction;
	}
}

// Get the direction of the snake's movement
int Snake::getDirection() const {
	return m_direction;
}

void Snake::move() {
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
void Snake::draw(sf::RenderWindow& window) {
	Node* current = head;
	while (current != nullptr) {
		sf::RectangleShape segment(sf::Vector2f(20, 20));
		segment.setPosition(current->x * 20, current->y * 20);
		segment.setFillColor(sf::Color::Green);
		window.draw(segment);
		current = current->next;
	}
}

// Get the head of the snake
Snake::Node* Snake::getHead() const {
	return head;
}

bool Snake::checkCollisionWithItself() {
	Node* current = head->next;
	while (current != nullptr) {
		if (head->x == current->x && head->y == current->y) {
			// The snake has collided with itself
			return true;
		}
		current = current->next;
	}
	return false;
}


bool Snake::checkCollision(Food& food) {
	if (head->x == food.getX() && head->y == food.getY()) {
		// The snake has collided with the food
		Node* current = head;
		while (current->next != nullptr) {
			current = current->next;
		}
		// A new node is added to the end of the snake
		current->next = new Node{ current->x, current->y, nullptr };
		//The food is set to a random color
		// sf::Color newColor(rand() % 256, rand() % 256, rand() % 256);
		// food.setColor(newColor);

			// Generate a new random color for the food
		sf::Color newColor;
		do {
			newColor = sf::Color(rand() % 256, rand() % 256, rand() % 256);
		} while (isColorTooDark(newColor));

		food.setColor(newColor);

		//The food is moved to a new random location
		food.setX(rand() % 40);
		food.setY(rand() % 30);
	}
	return false;
}

bool Snake::isColorTooDark(const sf::Color& color) {
	// Calculate the brightness of the color using a simple formula (adjust the threshold as needed)
	int brightness = (color.r + color.g + color.b) / 3;
	return brightness < 50; // Adjust the threshold as needed
}

	// Set the game state to paused
void Snake::pause() {
	paused = true;
}

// Set the game state to running
void Snake::start() {
	paused = false;
}

// Check if the game is currently paused
bool Snake::isPaused() const {
	return paused;
}
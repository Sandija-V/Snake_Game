#include "../include/LoginScreen.hpp"
#include "../include/Snake.hpp"
#include "../include/Food.hpp"
#include <iostream>

// Constructor implementation
LoginScreen::LoginScreen() : window(sf::VideoMode(800, 600), "Snake Game"), loginSuccess(false) {
    // Load the font
    if (!font.loadFromFile("D:/sfml/Snake_Game/src/Poppins-Medium.ttf")) {
        std::cout << "Error loading font\n";
    }

    title.setFont(font);
    title.setString("Register for the game");
    title.setCharacterSize(34);
    title.setFillColor(sf::Color::White);
    title.setPosition(100, 100);

    usernameLabel.setFont(font);
    usernameLabel.setString("Username");
    usernameLabel.setCharacterSize(34);
    usernameLabel.setFillColor(sf::Color::White);
    usernameLabel.setPosition(100, 150);

    passwordLabel.setFont(font);
    passwordLabel.setString("Password");
    passwordLabel.setCharacterSize(34);
    passwordLabel.setFillColor(sf::Color::White);
    passwordLabel.setPosition(100, 200);

    usernameInput.setFont(font);
    usernameInput.setCharacterSize(34);
    usernameInput.setFillColor(sf::Color::White);
    usernameInput.setPosition(300, 150);

    passwordInput.setFont(font);
    passwordInput.setCharacterSize(34);
    passwordInput.setFillColor(sf::Color::White);
    passwordInput.setPosition(300, 200);

    loginButton.setFont(font);
    loginButton.setString("Login");
    loginButton.setCharacterSize(34);
    loginButton.setFillColor(sf::Color::White);
    loginButton.setPosition(100, 250);

    registerButton.setFont(font);
    registerButton.setString("Register");
    registerButton.setCharacterSize(34);
    registerButton.setFillColor(sf::Color::White);
    registerButton.setPosition(350, 250);

    // Make the username input field active so that the user can actually type in the username
    usernameInput.setString("");
    usernameInput.setFillColor(sf::Color::Black);

    // Make the password input field active so that the user can actually type in the password
    passwordInput.setString("");
    passwordInput.setFillColor(sf::Color::Black);
}

// run() function implementation
void LoginScreen::run() {
    while (window.isOpen()) {
        handleEvents();

        window.clear();
        window.draw(title);
        window.draw(usernameLabel);
        window.draw(passwordLabel);

        // Draw the username input field
        sf::RectangleShape usernameField(sf::Vector2f(200, 34));
        usernameField.setPosition(300, 150);
        usernameField.setFillColor(sf::Color::White);
        window.draw(usernameField);
        window.draw(usernameInput);

        // Draw the password input field
        sf::RectangleShape passwordField(sf::Vector2f(200, 34));
        passwordField.setPosition(300, 200);
        passwordField.setFillColor(sf::Color::White);
        window.draw(passwordField);
        window.draw(passwordInput);

        window.draw(loginButton);
        window.draw(registerButton);
        window.display();

        if (loginSuccess) {
            // Start the game
            startGame();
            break;
        }
    }
}

    void LoginScreen::handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    handleTextInput(static_cast<char>(event.text.unicode));
                }
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    validateCredentials();
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (loginButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        validateCredentials();
                    }
                }
            }
        }
    }

	void LoginScreen::handleTextInput(char inputChar) {
        if (usernameInput.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
            if (inputChar == '\b') {
                // Remove the last character from the input string
                if (!username.empty()) {
                    username.pop_back();
                }
            }
            else if (inputChar == '\r') {
                validateCredentials();
            }
            else {
                // Append the input character to the username string
                username += inputChar;
            }
            usernameInput.setString(username);
        }
        else if (passwordInput.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
            if (inputChar == '\b') {
                // Remove the last character from the input string
                if (!password.empty()) {
                    password.pop_back();
                }
            }
            else if (inputChar == '\r') {
                validateCredentials();
            }
            else {
                // Append the input character to the password string
                password += inputChar;
            }
            // Replace the characters with asterisks for password masking
            passwordInput.setString(std::string(password.length(), '*'));
        }
    }

	void LoginScreen::validateCredentials() {
        // Implement your own validation logic here
        // For simplicity, let's consider the credentials valid if both fields are non-empty
        if (!username.empty() && !password.empty()) {
            loginSuccess = true;
        }
    }

	void LoginScreen::startGame() {
        // Create the game window
        sf::RenderWindow gameWindow(sf::VideoMode(800, 600), "Snake Game");

        // Create the snake object
        Snake snake(10, 10, 8, 5, 1);
        Food food(5, 5);

        // Initialize clock
        sf::Clock clock;
        sf::Time lt = clock.getElapsedTime();

        // Game loop
        while (gameWindow.isOpen()) {
            // Handle events
            sf::Event event;
            while (gameWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    gameWindow.close();
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
            gameWindow.clear();

            if (!snake.isPaused()) {
                // Get difference from lt to now
                sf::Time now = clock.getElapsedTime();
                sf::Time diff = now - lt;
                if (diff.asMilliseconds() > 1000 / snake.getSpeed()) {
                    lt = now;
                    snake.move();
                }
            }

			  // Draw the snake
            snake.draw(gameWindow);
            // Draw the food
            food.draw(gameWindow);

            (snake.checkCollision(food));

            if (snake.checkCollisionWithItself()) {
                snake = Snake(10, 10, 8, 5, 1);
            }

            // Update the window
            gameWindow.display();
        }
    }

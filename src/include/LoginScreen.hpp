#ifndef LOGIN_SCREEN_HPP
#define LOGIN_SCREEN_HPP

#include <SFML/Graphics.hpp>

class LoginScreen {
public:
    LoginScreen();
    void run();

private:
    void handleEvents();
    void handleTextInput(char inputChar);
    void validateCredentials();
    void startGame();

	sf::RenderWindow window;
    sf::Font font;

	sf::Text title;
    sf::Text usernameLabel;
    sf::Text passwordLabel;
    sf::Text usernameInput;
    sf::Text passwordInput;
    sf::Text loginButton;
    sf::Text registerButton;

    std::string username;
    std::string password;
    bool loginSuccess;

};

#endif // LOGIN_SCREEN_HPP
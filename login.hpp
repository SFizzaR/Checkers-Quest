#pragma once
#include <stack>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>

struct Cursor {
    sf::RectangleShape cursor;
    bool cursorVisible;
    float cursorTimer;
    float cursorBlinkDuration;
    sf::Clock clock;
};

class Login {
public:
    enum class Player {
        Player1,
        Player2
    };

    Login(sf::RenderWindow& renderWindow);
    bool run();

    std::ostringstream player1InputBuffer; // Buffer to store input
    std::ostringstream player2InputBuffer; // Buffer to store input

    //void startThread();
    //void stopThread();
private:
    std::stack<char> playerInputStack;
    std::string player1InitialText;
    std::string player2InitialText;
    char arr[8];
    char name[8];
    int end; 
    int s;
    void setarray();
    char pop();
    char leave();
    void push(char);
    /*std::thread dataThread;
    std::atomic<bool> threadRunning{ false };
    std::mutex dataMutex;
    void dataThreadFunction();*/

    Player activePlayer;

    sf::RenderWindow& window;
    sf::Font font;
    Cursor cursor1;
    Cursor cursor2;

    sf::Text player1Text;
    sf::Text player2Text;

    std::unique_ptr<sf::Texture> loginTexture;  // Use std::unique_ptr for managing texture
    sf::Sprite loginSprite;

    sf::RectangleShape start;
    sf::RectangleShape user1;
    sf::RectangleShape user2;

    bool inputComplete;

    void updateCursorPosition();
    void handleKeyPress(sf::Event::KeyEvent keyEvent);
    void handleKeyTab();
};


// Menu.cpp
#include "Menu.hpp"
#include <iostream>
#include "login.hpp"
#include "game.hpp"
#include "score.hpp"
#include "AVL.hpp"

Menu::Menu(sf::RenderWindow& renderWindow)
    : window(renderWindow) {
    if (!font.loadFromFile("C:/Users/fizza/source/repos/k22-4543/Project6/TheQualityBrave-Regular.ttf")) {
        // Handle error: Font not found
        return;
    }

    initBackground();
    initTextButtons();
}

void Menu::initBackground() {
    if (!backgroundTexture.loadFromFile("C:/Users/fizza/source/repos/k22-4543/Project6/checkMate.png")) {
        // Handle error: Image not found
        return;
    }

    backgroundSprite.setTexture(backgroundTexture);
}

void Menu::initTextButtons() {
    playText.setString("Play");
    playText.setFont(font);
    playText.setCharacterSize(30);
    playText.setPosition(350, 403);
    playText.setFillColor(sf::Color::White);
    playText.setOutlineColor(sf::Color::Black);
    playText.setOutlineThickness(4.0f);

    highScoresText.setString("Scores");
    highScoresText.setFont(font);
    highScoresText.setCharacterSize(30);
    highScoresText.setPosition(340, 460);
    highScoresText.setFillColor(sf::Color::White);
    highScoresText.setOutlineColor(sf::Color::Black);
    highScoresText.setOutlineThickness(4.0f);

    quitText.setString("Quit");
    quitText.setFont(font);
    quitText.setCharacterSize(30);
    quitText.setPosition(350, 520);
    quitText.setFillColor(sf::Color::White);
    quitText.setOutlineColor(sf::Color::Black);
    quitText.setOutlineThickness(4.0f);
}

void Menu::handleEvents(AVLTree& avl) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePos(sf::Mouse::getPosition(window));

            // Check if the mouse is over the "Play" button
            if (playText.getGlobalBounds().contains(mousePos)) {
                std::cout << "Play button clicked!" << std::endl;
                // Add code to start the game or switch to the login screen
                window.close();  // Close the main menu window
                sf::RenderWindow loginWindow(sf::VideoMode(600, 600), "Login Screen");
                Login loginScreen(loginWindow);
                if (loginScreen.run()) {

                    Game game;
                    game.Start(loginScreen.player1InputBuffer.str(), loginScreen.player2InputBuffer.str(), avl);
                }
            }

            // Check if the mouse is over the "High Scores" button
            else if (highScoresText.getGlobalBounds().contains(mousePos)) {
                std::cout << "High Scores button clicked!" << std::endl;
                window.close();
                // Add code to show high scores
                sf::RenderWindow ScoreWindow(sf::VideoMode(277, 600), "High Scores Screen");
                Score score(ScoreWindow, avl);
                score.Display(avl);
            }

            // Check if the mouse is over the "Quit" button
            else if (quitText.getGlobalBounds().contains(mousePos)) {
                window.close();
            }
        }
    }
}

void Menu::displayMenu() {
    // Clear the window
    window.clear();

    // Draw the background
    window.draw(backgroundSprite);

    // Draw the text buttons
    window.draw(playText);
    window.draw(highScoresText);
    window.draw(quitText);

    // Display the contents of the window
    window.display();
}
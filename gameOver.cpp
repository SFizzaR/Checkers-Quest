#include "GameOver.hpp"
#include "menu.hpp"
#include "score.hpp"
#include "AVL.hpp"
#include <iostream>
GameOver::GameOver(sf::RenderWindow& renderWindow, std::string winner, int score, int moves)
    : window(renderWindow) {
    if (!winnerTexture.loadFromFile("C:/Users/fizza/source/repos/k22-4543/Project6/game_Over.png")) {
        // Handle error: Image not found
        return;
    }

    winnerSprite.setTexture(winnerTexture);

    if (!font.loadFromFile("C:/Users/fizza/source/repos/k22-4543/Project6/HalloweenSpooky.otf")) {
        // Handle error: Font not found
        return;
    }

    winnerText.setFont(font);
    winnerText.setCharacterSize(45);
    winnerText.setString(winner);
    winnerText.setPosition(18, 170);
    // Set the position, color, and other properties for winnerText

    scoreText.setFont(font);
    scoreText.setCharacterSize(22);
    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setPosition(100, 340);

    movesText.setFont(font);
    movesText.setCharacterSize(22);
    movesText.setString("Move count: " + std::to_string(moves));
    movesText.setPosition(75, 370);
    // Initialize your close button
    closeButton.setRadius(17.0f); // Increase the size of the button
    closeButton.setPosition(240, 8); // Adjust the position of the button
    closeButton.setFillColor(sf::Color::Red); // Set a fill color to make it more noticeable (optional)

    scoreButton.setSize(sf::Vector2f(95.f, 23.f));
    scoreButton.setPosition(160, 445);

    menuButton.setSize(sf::Vector2f(95.f, 23.f));
    menuButton.setPosition(20, 445);

    //sf::RenderWindow mwindow(sf::VideoMode(750, 750), "SFML Main Menu");
    //Menu menu(mwindow);
}

void GameOver::handleEvents(AVLTree& avl) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePos(sf::Mouse::getPosition(window));

            // Check if the mouse is over the "Play" button
            if (closeButton.getGlobalBounds().contains(mousePos)) {
                // Add code to start the game
                std::cout << "close button clicked!" << std::endl;
                window.close();
            }
            else if (menuButton.getGlobalBounds().contains(mousePos)) {
                std::cout << "menu button clicked!" << std::endl;
                window.close();
                sf::RenderWindow window(sf::VideoMode(750, 750), "SFML Main Menu");
                Menu menu(window);

                std::cout << "Menu created" << std::endl;

                // Main loop
                while (window.isOpen()) {
                    // Handle events and display the menu
                    menu.handleEvents(avl);
                    menu.displayMenu();
                }

                std::cout << "Menu displayed" << std::endl;
            }
            else if (scoreButton.getGlobalBounds().contains(mousePos)) {
                std::cout << "score button clicked!" << std::endl;
                sf::RenderWindow ScoreWindow(sf::VideoMode(277, 600), "High Scores Screen");
                window.close();
                Score score(ScoreWindow, avl);
                score.Display(avl);
            }
        }
        // Add logic to handle button click events or other events
    }
}

void GameOver::DisplayWinner(AVLTree& avl) {
    while (window.isOpen()) {
        handleEvents(avl);

        window.clear();
        // Draw other elements, such as winnerSprite and winnerText
        window.draw(closeButton);
        window.draw(scoreButton);
        window.draw(menuButton);
        window.draw(winnerSprite);
        window.draw(winnerText);
        window.draw(scoreText);
        window.draw(movesText);

        window.display();
    }
}



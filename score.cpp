#include "score.hpp"
#include "menu.hpp"
#include "game.hpp"
#include <SFML/Graphics.hpp>
#include "AVL.hpp"
using namespace std; 
using namespace sf;
Score::Score(RenderWindow& renderWindow, AVLTree& avl) : window(renderWindow) {
    if (!scoreTexture.loadFromFile("C:/Users/fizza/source/repos/k22-4543/Project6/2.png")) {
        // Handle error: Image not found
        return;
    }
    if (!font.loadFromFile("C:/Users/fizza/source/repos/k22-4543/Project6/HalloweenSpooky.otf")) {
        // Handle error: Font not found
        return;
    }
    ScoreSprite.setTexture(scoreTexture);
    int x = 120;
    std::vector<AVLNode*> sortedData = avl.getSortedData();
    std::string playerArray[5];
    for (int i = 0; i < 5; i++) {
        playerArray[i] = " ";
    }
    // Store sorted data in an array of structures
    int index = 0;
    for (const auto& node : sortedData) {
        playerArray[index] = node->playerName + " :" + to_string(node->score);
        index++;
    }
    header.setFont(font);
    header.setString("Player : scores");
    header.setCharacterSize(35);
    header.setFillColor(Color::White);
    header.setPosition(20.f, x);

    for (int i = 0; i < 5; ++i) {
        texts[i].setString(playerArray[i]);
        texts[i].setFont(font);
        texts[i].setCharacterSize(35);
        texts[i].setFillColor(Color::White);
        texts[i].setPosition(20.f, (i+1) * 50.f + x);
    }
    for (int i = 0; i < index; ++i) {
        highscores[i].setSize(Vector2f(258.f, 40.f));
        highscores[i].setFillColor(Color(150, 75, 0));
        highscores[i].setPosition(11.f, ((i+1)*50.f) +x);
    }

    closeButton.setRadius(17.0f); // Increase the size of the button
    closeButton.setPosition(230, 8); // Adjust the position of the button
    closeButton.setFillColor(Color::Red); // Set a fill color to make it more noticeable (optional)

    menuButton.setSize(Vector2f(95.f, 23.f));
    menuButton.setPosition(90, 530);

}

void Score:: handleEvents(AVLTree& avl) {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
        else if (event.type == Event::MouseButtonPressed) {
            Vector2f mousePos(Mouse::getPosition(window));

            // Check if the mouse is over the "Play" button
            if (closeButton.getGlobalBounds().contains(mousePos)) {
                // Add code to start the game
                cout << "close button clicked!" << endl;
                window.close();
            }
            else if (menuButton.getGlobalBounds().contains(mousePos)) {
                cout << "menu button clicked!" << endl;
                window.close();
                RenderWindow window(VideoMode(750, 750), "SFML Main Menu");
                Menu menu(window);

                cout << "Menu created" << endl;

                // Main loop
                while (window.isOpen()) {
                    // Handle events and display the menu
                    menu.handleEvents(avl);
                    menu.displayMenu();
                }

                cout << "Menu displayed" << endl;
            }
            // Add logic to handle button click events or other events
        }
    }
}

void Score::Display(AVLTree& avl) {
    while (window.isOpen()) {
        handleEvents(avl);

        window.clear();
        window.draw(menuButton);
        window.draw(closeButton);
        window.draw(ScoreSprite);
        for (int i = 0; i < 5; ++i) {
            window.draw(highscores[i]);
        }
        for (int i = 0; i < 5; ++i) {
            window.draw(texts[i]);
        }
        window.draw(header);
        window.display();
    }
}

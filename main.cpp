#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.hpp"
#include "login.hpp"
#include "title.hpp"
#include "gameOver.hpp"
#include "menu.hpp"
#include "AVL.hpp"


AVLTree avl;

int main() {
    Title title;
    title.Begin();

    //sf::RenderWindow tempwindow(sf::VideoMode(277, 600), "Game over");
    //GameOver gameover(tempwindow, "winner");
    //gameover.DisplayWinner();

    // Create the main menu window
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

    return 0;
}

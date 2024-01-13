// Menu.hpp
#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include "AVL.hpp"

class Menu {
public:
    Menu(sf::RenderWindow& renderWindow);

    void handleEvents(AVLTree& avl);
    void displayMenu();

private:
    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Text playText;
    sf::Text highScoresText;
    sf::Text quitText;

    void initBackground();
    void initTextButtons();
};

#endif // MENU_HPP



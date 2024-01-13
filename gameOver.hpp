#pragma once
#include <SFML/Graphics.hpp>
#include "AVL.hpp"
class GameOver {
public:
    GameOver(sf::RenderWindow& renderWindow, std::string winner, int score, int moves);
    void DisplayWinner(AVLTree& avl);

private:
    sf::RenderWindow& window;
    sf::Texture winnerTexture;
    sf::Sprite winnerSprite;
    sf::Font font;
    sf::Text winnerText;
    sf::CircleShape closeButton; // Assuming you have a close button 
    sf::RectangleShape scoreButton;
    sf::RectangleShape menuButton;
    sf::Text scoreText;
    sf::Text movesText;
    void handleEvents(AVLTree& avl);
};


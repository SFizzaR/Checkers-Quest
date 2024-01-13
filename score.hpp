#pragma once
#include <SFML/Graphics.hpp>
#include "AVL.hpp"
class Score
{
	sf::Font font;
	sf::RectangleShape highscores[5];
	sf::RenderWindow& window;
	sf::Texture scoreTexture;
	sf::Sprite ScoreSprite;
	sf::Text texts[5];
	sf::Text header;
	sf::CircleShape closeButton;
	sf::RectangleShape menuButton;
	void handleEvents(AVLTree& avl);
	
public:
	Score(sf::RenderWindow& renderWindow, AVLTree& avl);
	void Display(AVLTree& avl);
};

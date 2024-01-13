// board.hpp
#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include "piece.hpp"

class Board {
public:
    void Draw(sf::RenderWindow& window);
    void Highlight(sf::RenderWindow& window, int x, int y);
    void Setup(sf::RenderWindow& window, Piece* RedPieces, Piece* WhitePieces);
private:
    static const int size = 8; // assuming you have a constant size for the board
};

#endif // BOARD_HPP


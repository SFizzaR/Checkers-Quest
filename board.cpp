// board.cpp
#include "board.hpp"
#include "piece.hpp"  // Include the header file for the Piece class

void Board::Draw(sf::RenderWindow& window) {
    sf::RectangleShape tile;
    tile.setSize(sf::Vector2f(75.f, 75.f));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            tile.setPosition(sf::Vector2f(75 * i, 75 * j));
            if ((i + j) % 2 == 0) {
                tile.setFillColor(sf::Color(76, 46, 5));
            }
            else {
                tile.setFillColor(sf::Color(248, 231, 187));
            }
            window.draw(tile);
        }
    }
}
void Board::Highlight(sf::RenderWindow& window, int x, int y) {
    sf::RectangleShape tile;
    tile.setSize(sf::Vector2f(75.f, 75.f));
    tile.setFillColor(sf::Color::Green);
    tile.setPosition(sf::Vector2f(75 * x, 75 * y));
    window.draw(tile);
}

void Board::Setup(sf::RenderWindow& window, Piece* RedPieces, Piece* WhitePieces) {
    int m = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = (int)!(i % 2 & 1); j < 8; j += 2) {
            WhitePieces[m].isAlive = true;
            WhitePieces[m].x = j;
            WhitePieces[m].y = i;
            m++;
        }
    }
    m = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = (int)(i % 2 & 1); j < 8; j += 2) {
            RedPieces[m].isAlive = true;
            RedPieces[m].x = j;
            RedPieces[m].y = 7 - i;
            m++;
        }

    }
}

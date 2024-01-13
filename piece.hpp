// piece.hpp
#ifndef PIECE_HPP
#define PIECE_HPP
#include <iostream>
#include <SFML/Graphics.hpp>

class Piece {
public:
    float radius = 30;
    int x;
    int y;
    bool isAlive;
    bool isKing = false;
    std::string playerName; 
    sf::Color color;

    void Draw(sf::RenderWindow& window);
    Piece* FindPiece(int x, int y, Piece* RedPieces, Piece* WhitePieces);

    void KillPiece(int x, int y, Piece* RedPieces, Piece* WhitePieces, int* turn);

    int MovePiece(int x, int y, Piece* s_Piece, Piece* RedPieces, Piece* WhitePieces, int* turn);
    int endGame(Piece* RedPieces, Piece* WhitePieces);

};

#endif // PIECE_HPP

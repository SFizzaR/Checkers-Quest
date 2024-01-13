// piece.cpp
#include "piece.hpp"
#include <iostream>

void Piece::Draw(sf::RenderWindow& window) {
    if (isAlive) {
        sf::Texture pieceShape;
        

        // Use different textures based on the color of the piece
        if (color == sf::Color::Red) {
            if (!pieceShape.loadFromFile("C:/Users/fizza/source/repos/k22-4543/Project6/Brown.png")) {
                // Handle error: Image not found
                return;
            }

            // Create sprite
            sf::Sprite pieceSprite (pieceShape);
            float scaleFactor = (2 * radius) / pieceSprite.getLocalBounds().width;
            pieceSprite.setScale(scaleFactor, scaleFactor);

            pieceSprite.setPosition(x * 75 + 5, y * 75 + 5);
            window.draw(pieceSprite);
        }
        else if (color == sf::Color::White) {
            if (!pieceShape.loadFromFile("C:/Users/fizza/source/repos/k22-4543/Project6/black.png")) {
                // Handle error: Image not found
                return;
            }

            // Create sprite
            sf::Sprite pieceSprite(pieceShape);
            float scaleFactor = (2 * radius) / pieceSprite.getLocalBounds().width;
            pieceSprite.setScale(scaleFactor, scaleFactor);

            pieceSprite.setPosition(x * 75 + 5, y * 75 + 5);
            window.draw(pieceSprite);
            
        }

        if (isKing) {
            if (color == sf::Color::Red) {
                if (!pieceShape.loadFromFile("C:/Users/fizza/source/repos/k22-4543/Project6/brown_king.png")) {
                    // Handle error: Image not found
                    return;
                }

                // Create sprite
                sf::Sprite pieceSprite(pieceShape);
                float scaleFactor = (2 * radius) / pieceSprite.getLocalBounds().width;
                pieceSprite.setScale(scaleFactor, scaleFactor);

                pieceSprite.setPosition(x * 75 + 5, y * 75 + 5);
                window.draw(pieceSprite);
            }
            else if (color == sf::Color::White) {
                if (!pieceShape.loadFromFile("C:/Users/fizza/source/repos/k22-4543/Project6/black_king.png")) {
                    // Handle error: Image not found
                    return;
                }

                // Create sprite
                sf::Sprite pieceSprite(pieceShape);
                float scaleFactor = (2 * radius) / pieceSprite.getLocalBounds().width;
                pieceSprite.setScale(scaleFactor, scaleFactor);

                pieceSprite.setPosition(x * 75 + 5, y * 75 + 5);
                window.draw(pieceSprite);
            }
            
        }

    }
}
Piece* Piece::FindPiece(int x, int y, Piece* RedPieces, Piece* WhitePieces) {
    for (int i = 0; i < 12; i++) {
        if (RedPieces[i].x == x && RedPieces[i].y == y) {
            if (RedPieces[i].isAlive) {
                std::cout << "Found Red Piece at (" << x << ", " << y << ")\n";
                return &RedPieces[i];
            }
        }
        if (WhitePieces[i].x == x && WhitePieces[i].y == y) {
            if (WhitePieces[i].isAlive) {
                std::cout << "Found White Piece at (" << x << ", " << y << ")\n";
                return &WhitePieces[i];
            }
        }
    }
    std::cout << "Piece not found at (" << x << ", " << y << ")\n";
    return nullptr;
}
int Piece::endGame(Piece* RedPieces, Piece* WhitePieces) {
    bool pRed = true, pWhite = true;
    for (int i=0; i < 12; i++) {
        if (RedPieces[i].isAlive) {
            pWhite = false;
            break;
        }
    }
    if (pWhite)
        return 1;
    for (int i=0; i < 12; i++) {
        if (WhitePieces[i].isAlive) {
            pRed = false;
            break;
        }
    }
    if (pRed)
        return 2;
    return 0;
}

void Piece::KillPiece(int x, int y, Piece* RedPieces, Piece* WhitePieces, int* turn) {
    FindPiece(x, y, RedPieces, WhitePieces)->isAlive = false;
    *turn = ((*turn == 1) ? 2 : 1);
}
int Piece::MovePiece(int x, int y, Piece* s_Piece, Piece* RedPieces, Piece* WhitePieces, int* turn) {
    if (s_Piece->color == sf::Color::Red || s_Piece->color == sf::Color::White && s_Piece->isKing) {
        if (x == s_Piece->x - 1 && y == s_Piece->y - 1) {
            if (!FindPiece(x, y, RedPieces, WhitePieces)) {
                *turn = ((*turn == 1) ? 2 : 1);
                s_Piece->x = x;
                s_Piece->y = y;
                return 1;
            }
        }
        if (x == s_Piece->x + 1 && y == s_Piece->y - 1) {
            if (!FindPiece(x, y, RedPieces, WhitePieces)) {
                *turn = ((*turn == 1) ? 2 : 1);
                s_Piece->x = x;
                s_Piece->y = y;
                return 1;
            }
        }
        if (x == s_Piece->x - 2 && y == s_Piece->y - 2) {
            if (!FindPiece(x, y, RedPieces, WhitePieces) && FindPiece(x + 1, y + 1, RedPieces, WhitePieces) != nullptr && FindPiece(x + 1, y + 1, RedPieces, WhitePieces)->color != s_Piece->color) {
                *turn = ((*turn == 1) ? 2 : 1);
                KillPiece(x + 1, y + 1, RedPieces, WhitePieces, turn);
                s_Piece->x = x;
                s_Piece->y = y;
                return 1;
            }
        }
        if (x == s_Piece->x + 2 && y == s_Piece->y - 2) {
            if (!FindPiece(x, y, RedPieces, WhitePieces) && FindPiece(x - 1, y + 1, RedPieces, WhitePieces) != nullptr && FindPiece(x - 1, y + 1, RedPieces, WhitePieces)->color != s_Piece->color) {
                *turn = ((*turn == 1) ? 2 : 1);
                KillPiece(x - 1, y + 1, RedPieces, WhitePieces, turn);
                s_Piece->x = x;
                s_Piece->y = y;
                return 1;
            }
        }
    }
    if (s_Piece->color == sf::Color::White || s_Piece->color == sf::Color::Red && s_Piece->isKing) {
        if (x == s_Piece->x - 1 && y == s_Piece->y + 1) {
            if (!FindPiece(x, y, RedPieces, WhitePieces)) {
                *turn = ((*turn == 1) ? 2 : 1);
                s_Piece->x = x;
                s_Piece->y = y;
                return 1;
            }
        }
        if (x == s_Piece->x + 1 && y == s_Piece->y + 1) {
            if (!FindPiece(x, y, RedPieces, WhitePieces)) {
                *turn = ((*turn == 1) ? 2 : 1);
                s_Piece->x = x;
                s_Piece->y = y;
                return 1;
            }
        }
        if (x == s_Piece->x - 2 && y == s_Piece->y + 2) {
            if (!FindPiece(x, y, RedPieces, WhitePieces) && FindPiece(x + 1, y - 1, RedPieces, WhitePieces) != nullptr && FindPiece(x + 1, y - 1, RedPieces, WhitePieces)->color != s_Piece->color) {
                *turn = ((*turn == 1) ? 2 : 1);
                s_Piece->x = x;
                s_Piece->y = y;
                KillPiece(x + 1, y - 1, RedPieces, WhitePieces, turn);
                return 1;
            }
        }
        if (x == s_Piece->x + 2 && y == s_Piece->y + 2) {
            if (!FindPiece(x, y, RedPieces, WhitePieces) && FindPiece(x - 1, y - 1, RedPieces, WhitePieces) != nullptr && FindPiece(x - 1, y - 1, RedPieces, WhitePieces)->color != s_Piece->color) {
                *turn = ((*turn == 1) ? 2 : 1);
                s_Piece->x = x;
                s_Piece->y = y;
                KillPiece(x - 1, y - 1, RedPieces, WhitePieces, turn);
                return 1;
            }
        }
    }
    return 0;
}

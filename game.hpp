// Game.hpp
#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <stack>
#include <queue>
#include "AVL.hpp"
#include <algorithm> // for std::sort

// Include necessary headers for your other classes
#include "board.hpp"
#include "piece.hpp"
#include "gameOver.hpp"

class Game {
    int player1Moves;
    int player2Moves;
    Piece* BinarySearchPieceByXCoordinate(int x, Piece arr[], int size);
public:
    int player1Score;
    int player2Score;
    std::string Start(const std::string& initialPlayer1Text, const std::string& initialPlayer2Text, AVLTree& avl);
    int CalculateScore(int moves);
    void quickSort(Piece arr[], int low, int high);
    int partition(Piece arr[], int low, int high);
};

#endif // GAME_HPP





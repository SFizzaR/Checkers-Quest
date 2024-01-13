// game.cpp
#include "game.hpp"
#include "board.hpp" // Include the header file for the Board class
#include "piece.hpp"
#include <iostream>
#include "gameOver.hpp"
#include "AVL.hpp"

int Game::CalculateScore(int moves) {
    // Assuming a simple scoring mechanism: the fewer the moves, the higher the score
    // You can customize this based on your specific scoring criteria
    return 1000 / (moves + 1);
}

std::string Game::Start(const std::string& initialPlayer1Text, const std::string& initialPlayer2Text, AVLTree& avl) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16.0;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Checkers", sf::Style::Default, settings);
    sf::Event event;
    Board board;
    int grid[8][8];
    Piece piece;
    Piece RedPieces[12];
    Piece WhitePieces[12];
    sf::Texture sidebar;
    std::string player1 = initialPlayer1Text;
    std::string player2 = initialPlayer2Text;
    player1Moves = 0;
    player2Moves = 0;

    if (!sidebar.loadFromFile("C:/Users/fizza/source/repos/k22-4543/Project6/Checkers Quest.png")) {
        // Handle error: Image not found
        return "error";
    }

    // Create sidebar sprite
    sf::Sprite sidebarSprite(sidebar);
    sidebarSprite.setPosition(600.f, 0.f);
    sf::Font font;
    if (!font.loadFromFile("C:/Users/fizza/source/repos/k22-4543/Project6/HalloweenSpooky.otf")) {
        // Handle error: Font not found
        return "error";
    }

    sf::Text player1Text(player1, font, 37);
    player1Text.setPosition(635, 185);
    player1Text.setFillColor(sf::Color::White); // Set text color


    sf::Text player2Text(player2, font, 37);
    player2Text.setPosition(635, 384);
    player2Text.setFillColor(sf::Color::White); // Set text color


    bool selected = false;
    Piece* SelectedPiece = nullptr;
    int turn = 1;

    for (int i = 0; i < 12; i++) {
        // assigning playername to piece 
        WhitePieces[i].color = sf::Color::White;
        WhitePieces[i].playerName = player1;
        RedPieces[i].color = sf::Color::Red;
        RedPieces[i].playerName = player2;
    }

    board.Setup(window, RedPieces, WhitePieces);
    std::stack<int> myStack;
    std::queue<int> myQueue;

    // Example usage of stack and queue
    for (int i = 0; i < 5; ++i) {
        myStack.push(i);   // Pushing elements onto the stack
        myQueue.push(i);   // Pushing elements into the queue
    }

    // Popping elements from the stack
    while (!myStack.empty()) {
        std::cout << myStack.top() << " ";
        myStack.pop();
    }

    std::cout << std::endl;

    // Popping elements from the queue
    while (!myQueue.empty()) {
        std::cout << myQueue.front() << " ";
        myQueue.pop();
    }

    std::cout << std::endl;

    // Sorting RedPieces based on the x-coordinate
    quickSort(RedPieces, 0, 11);

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    selected = !selected;
                    if (selected) {
                        if (turn == 1) {
                            player1Moves++;
                        }
                        else {
                            player2Moves++;
                        }
                    }
                }
            }
        }

        window.clear();
        board.Draw(window);

        if (SelectedPiece != nullptr) {
            board.Highlight(window, SelectedPiece->x, SelectedPiece->y);
        }

        for (int i = 0; i < 12; i++) {
            WhitePieces[i].Draw(window);
            RedPieces[i].Draw(window);
        }

        // Draw the sidebar
        window.draw(sidebarSprite);

        //Draw text 
        window.draw(player1Text);
        window.draw(player2Text);
        // Draw vertical lines to border the checkers board
        sf::RectangleShape verticalLines[4];
        verticalLines[0].setSize(sf::Vector2f(4.f, 600.f));
        verticalLines[0].setPosition(600.f, 0.f);
        verticalLines[0].setFillColor(sf::Color(98, 42, 15));
        window.draw(verticalLines[0]);
        verticalLines[1].setSize(sf::Vector2f(4.f, 600.f));
        verticalLines[1].setPosition(0.f, 0.f);
        verticalLines[1].setFillColor(sf::Color(98, 42, 15));
        window.draw(verticalLines[1]);
        verticalLines[2].setSize(sf::Vector2f(600.f, 4.f));
        verticalLines[2].setPosition(0.f, 0.f);
        verticalLines[2].setFillColor(sf::Color(98, 42, 15));
        window.draw(verticalLines[2]);
        verticalLines[3].setSize(sf::Vector2f(600.f, 4.f));
        verticalLines[3].setPosition(0.f, 596.f);
        verticalLines[3].setFillColor(sf::Color(98, 42, 15));
        window.draw(verticalLines[3]);



        // Set the default outline color and thickness for player 1

        player1Text.setOutlineThickness(0.f);

        // Set the default outline color and thickness for player 2
        player2Text.setOutlineThickness(0.f);

        // Indicate next turn
        if (turn == 1) {
            player1Text.setOutlineColor(sf::Color(255, 87, 51));  // Outline color for the current player
            player1Text.setOutlineThickness(4.f);
        }
        else {
            player2Text.setOutlineThickness(4.f);
            player2Text.setOutlineColor(sf::Color(255, 87, 51));  // Outline color for the current player
        }
        if (selected) {
            int x = sf::Mouse::getPosition(window).x / 75;
            int y = sf::Mouse::getPosition(window).y / 75;
            Piece* clickedPiece = BinarySearchPieceByXCoordinate(x, RedPieces, 12);
            if (clickedPiece != nullptr) {
                // You found a piece, do something with it
                std::cout << "Clicked piece details: x = " << clickedPiece->x << ", y = " << clickedPiece->y << std::endl;
            }
            if (piece.FindPiece(x, y, RedPieces, WhitePieces) &&
                (piece.FindPiece(x, y, RedPieces, WhitePieces)->color == sf::Color::Red && turn == 1 ||
                    piece.FindPiece(x, y, RedPieces, WhitePieces)->color == sf::Color::White && turn == 2)) {
                if (piece.FindPiece(x, y, RedPieces, WhitePieces) == SelectedPiece) {
                    SelectedPiece = nullptr;
                }
                else {
                    SelectedPiece = piece.FindPiece(x, y, RedPieces, WhitePieces);
                }

                selected = false;
            }
            else if (SelectedPiece != nullptr &&
                SelectedPiece->MovePiece(x, y, SelectedPiece, RedPieces, WhitePieces, &turn)) {
                selected = false;
                SelectedPiece = nullptr;
            }
            selected = false;
        }

        // Check for game end
        int result = piece.endGame(RedPieces, WhitePieces);
        if (result == 1) {
            // Open a new window for the end game scenario where White wins
            // You can replace this with your actual code to open a new window
            avl.AddScore(player1Score, player1);
            avl.AddScore(CalculateScore(player2Moves), player2);
            std::cout << "White wins!" << std::endl;
            player1 = player1 + " wins!";
            // Open a new window or perform other end game actions
            window.close();
            sf::RenderWindow tempwindow(sf::VideoMode(277, 600), "Game over");
            GameOver gameover(tempwindow, player1, player1Score, player1Moves);
            gameover.DisplayWinner(avl);

            return player1;// Close the current window or handle it appropriately
        }
        else if (result == 2) {
            avl.AddScore(CalculateScore(player2Moves), player2);
            avl.AddScore(player1Score, player1);
            // Open a new window for the end game scenario where Red wins
            std::cout << "Red wins!" << std::endl;
            player2 = player2 + " wins!";
            // Open a new window or perform other end game actions
            window.close();
            sf::RenderWindow tempwindow(sf::VideoMode(277, 600), "Game over");
            GameOver gameover(tempwindow, player2, player2Moves, player2Score);
            gameover.DisplayWinner(avl);

            // Open a new window or perform other end game actions
             // Close the current window or handle it appropriately
            return player2;
        }

        for (int i = 0; i < 12; i++) {
            if (RedPieces[i].y == 0) {
                RedPieces[i].isKing = true;
            }
            if (WhitePieces[i].y == 7) {
                WhitePieces[i].isKing = true;
            }
        }
        player1Score = CalculateScore(player1Moves);
        player2Score = CalculateScore(player2Moves);


        window.display();
    }
}
// Sorting RedPieces based on the x-coordinate using Quick Sort
void Game::quickSort(Piece arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int Game::partition(Piece arr[], int low, int high) {
    int pivot = arr[high].x;
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j].x < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}
// Inside your Game class
Piece* Game::BinarySearchPieceByXCoordinate(int x, Piece arr[], int size) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid].x == x) {
            return &arr[mid]; // Found the piece
        }

        if (arr[mid].x < x) {
            low = mid + 1; // Search in the right half
        }
        else {
            high = mid - 1; // Search in the left half
        }
    }

    return nullptr; // Piece not found
}

#include "login.hpp"
#include <iostream>
#include <memory>  // for std::unique_ptr, std::make_unique
#include <SFML/Graphics.hpp>
/*void Login::startThread() {
    threadRunning = true;
    dataThread = std::thread(&Login::dataThreadFunction, this);
}

void Login::stopThread() {
    threadRunning = false;
    if (dataThread.joinable()) {
        dataThread.join();
    }
}
void  Login::dataThreadFunction() {
    while (threadRunning) {
        // Perform data manipulation and string appending here
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulating work

        // Use a lock to safely update the input buffers
        std::lock_guard<std::mutex> lock(dataMutex);
        if (activePlayer == Player::Player1) {
            player1InputBuffer << "ThreadData"; // Replace this with your actual data
        }
        else if (activePlayer == Player::Player2) {
            player2InputBuffer << "ThreadData"; // Replace this with your actual data
        }
    }
}*/
Login::Login(sf::RenderWindow& renderWindow) : window(renderWindow) {
    if (!font.loadFromFile("C:/Users/fizza/source/repos/k22-4543/Project6/HalloweenSpooky.otf")) {
        // Handle error: Font not found
        return;
    }
    activePlayer = Player::Player1;
    loginTexture = std::make_unique<sf::Texture>();

    if (!loginTexture->loadFromFile("C:/Users/fizza/source/repos/k22-4543/Project6/1.png")) {
        // Handle error: Image not found
        return;
    }
    cursor1.cursorBlinkDuration = 1.0f;
    cursor2.cursorBlinkDuration = 1.0f;

    // Create login sprite
    loginSprite.setTexture(*loginTexture);

    // Initialize player1Text here
    player1Text.setFont(font);
    player1Text.setCharacterSize(30);
    player1Text.setPosition(200, 279);
    player1Text.setFillColor(sf::Color::White);

    // Initialize player2Text here
    player2Text.setFont(font);
    player2Text.setCharacterSize(30);
    player2Text.setPosition(200, 361);
    player2Text.setFillColor(sf::Color::White);

    start.setSize(sf::Vector2f(153.f, 38.f));
    start.setPosition(220, 440);

    user1.setSize(sf::Vector2f(370.f, 38.f));
    user1.setPosition(114, 279);

    user2.setSize(sf::Vector2f(370.f, 38.f));
    user2.setPosition(114, 361);

    cursor1.cursor.setSize(sf::Vector2f(2.f, 30.f));
    cursor1.cursor.setFillColor(sf::Color::White);
    cursor1.cursor.setPosition(player1Text.getPosition().x + player1Text.getGlobalBounds().width, user1.getPosition().y);
    cursor1.cursorVisible = false; // Initially set to invisible
    updateCursorPosition(); // Initial cursor position
    cursor1.cursorTimer = 0.0f;

    cursor2.cursor.setSize(sf::Vector2f(2.f, 30.f));
    cursor2.cursor.setFillColor(sf::Color::White);
    cursor2.cursor.setPosition(player2Text.getPosition().x + player2Text.getGlobalBounds().width, user2.getPosition().y);
    cursor2.cursorVisible = false; // Initially set to invisible
    cursor2.cursorTimer = 0.0f;
}

void Login::updateCursorPosition() {
    // Update cursor position based on the width of the entered text
    cursor1.cursor.setPosition(player1Text.getPosition().x + player1Text.getGlobalBounds().width + 11, user1.getPosition().y);
    cursor2.cursor.setPosition(player2Text.getPosition().x + player2Text.getGlobalBounds().width + 11, user2.getPosition().y);
}

void Login::handleKeyPress(sf::Event::KeyEvent keyEvent) {
    char pressedKey = '\0';

    if (keyEvent.code >= sf::Keyboard::A && keyEvent.code <= sf::Keyboard::Z) {
        pressedKey = 'A' + (keyEvent.code - sf::Keyboard::A);
        push(pressedKey);
    }
    else if (keyEvent.code >= sf::Keyboard::Num0 && keyEvent.code <= sf::Keyboard::Num9) {
        pressedKey = '0' + (keyEvent.code - sf::Keyboard::Num0);
        push(pressedKey);

    }

    if (pressedKey != '\0') {
        std::cout << pressedKey << " key pressed" << std::endl;

        if (activePlayer == Player::Player1) {
            // Check if adding the pressed key would exceed the maximum length
            if (player1InputBuffer.str().length() < 8) {
                // Append the pressed key to the existing text
                player1InputBuffer << pressedKey;
            }
        }
        else if (activePlayer == Player::Player2) {
            if (player2InputBuffer.str().length() < 8) {
                // Append the pressed key to the existing text
                player2InputBuffer << pressedKey;
            }
        }
    }

    if (keyEvent.code == sf::Keyboard::BackSpace) {
        // Check if the active player is Player1 or Player2
        std::ostringstream& playerInputBuffer = (activePlayer == Player::Player1) ? player1InputBuffer : player2InputBuffer;

        if (!playerInputBuffer.str().empty()) {
            // Remove the last character from the player input buffer
            playerInputBuffer.str(playerInputBuffer.str().substr(0, playerInputBuffer.str().size() - 1));
        }

        // For demonstration purposes, you may want to handle the stack operations as well
        pop();
        int i = 0;
        std::cout << s;
        while (s >= 0) {
            char stackTop = name[s];
            arr[i] = stackTop;
            std::cout << arr[i];
            leave();
            

            if (activePlayer == Player::Player1 && player1InputBuffer.str().length() < 8) {
                player1InputBuffer << stackTop;
                i++;
            }
            else if (activePlayer == Player::Player2 && player2InputBuffer.str().length() < 8) {
                player2InputBuffer << stackTop;
                i++;
            }

        }
        setarray();
        for (int x = 0; x < i; x++) {
            push(arr[x]);
        }
    }
}


void Login::setarray() {
    end = -1;
    s= -1;
    for (int i = 0; i < 8; i++) {
        name[i] = ' ';
    }
}

char Login::pop() {
    char t = name[end];
    // Check if there's only one element in the stack
    if (s == end) {
        // If yes, reset start and end to -1 to indicate an empty stack

        s = -1;
        end = -1;
    }
    else {
        // If there is more than one element, decrement end to remove the top element
        end--;
    }
    return t; 
}
char Login::leave() {

    char leftElement = name [s];

    // Check if there's only one element in the stack
    if (s == end) {
        // If yes, reset start and end to -1 to indicate an empty stack
        s = -1;
        end = -1;
    }
    else {
        // If there is more than one element, increment start to leave the bottom element
        s++;
    }

    return leftElement;
}
void Login::push(char value) {
    if (s == -1) {
        s = 0;
    }
        // Increment end to add a new element
        end++;

    // Push the element onto the stack
    name[end] = value;
    std::cout << name[end] << std::endl;
}
void Login::handleKeyTab() {
    // Toggle between Player1 and Player2 when Tab key is pressed
    setarray();
    if (activePlayer == Player::Player1) {
        activePlayer = Player::Player2;
        while (end > 0) {
            pop();
        }
    }
    else {
        activePlayer = Player::Player1;
        while (end > 0) {
            pop();
        }
    }

}

bool Login::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                handleKeyPress(event.key);
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                else if (event.key.code == sf::Keyboard::Tab) {
                    handleKeyTab();
                }
                break;
            case sf::Event::MouseButtonPressed:
                sf::Vector2f mousePos(sf::Mouse::getPosition(window));
                if (start.getGlobalBounds().contains(mousePos)) {
                    if (inputComplete) {
                        std::cout << "start button clicked!" << std::endl;
                        window.close();
                    }
                    else
                        std::cout << "Data not entered" << std::endl;
                }
                else if (user1.getGlobalBounds().contains(mousePos)) {
                    cursor1.cursorVisible = true;
                    cursor1.cursorTimer = 0.0f;
                }
                else if (user2.getGlobalBounds().contains(mousePos)) {
                    cursor2.cursorVisible = true;
                    cursor2.cursorTimer = 0.0f;
                }
                break;
            }
        }

        cursor1.cursorTimer += cursor1.clock.restart().asSeconds();
        if (cursor1.cursorTimer >= cursor1.cursorBlinkDuration) {
            cursor1.cursorVisible = !cursor1.cursorVisible; // Toggle cursor visibility
            cursor1.cursorTimer = 0.0f;             // Reset the cursor timer
        }
        player1Text.setString(player1InputBuffer.str());

        cursor2.cursorTimer += cursor2.clock.restart().asSeconds();
        if (cursor2.cursorTimer >= cursor2.cursorBlinkDuration) {
            cursor2.cursorVisible = !cursor2.cursorVisible; // Toggle cursor visibility
            cursor2.cursorTimer = 0.0f;             // Reset the cursor timer
        }
        player2Text.setString(player2InputBuffer.str());

        // Update cursor positions inside the main loop
        updateCursorPosition();

        window.clear(); // Clear the window once at the beginning of each frame

        // Draw UI elements...

        window.draw(start);
        window.draw(user2);
        window.draw(user1);
        window.draw(loginSprite);

        // Draw player1Text and cursor
        window.draw(player1Text);
        if (activePlayer == Player::Player1) {
            if (cursor1.cursorVisible) {
                window.draw(cursor1.cursor);
            }
        }

        // Draw player2Text and cursor
        window.draw(player2Text);
        if (activePlayer == Player::Player2) {
            if (cursor2.cursorVisible) {
                window.draw(cursor2.cursor);
            }
        }

        window.display();
        if (!player1InputBuffer.str().empty() && !player2InputBuffer.str().empty()) {
            inputComplete = true;
        }
    }

    return true;
}
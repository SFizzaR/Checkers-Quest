#include "title.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>

void Title::Begin() {
    sf::RenderWindow window(sf::VideoMode(600, 600), "Title Window");
    sf::Clock clockWindow;
    sf::Clock clockLoad;

    sf::Texture storyTexture;
    if (!storyTexture.loadFromFile("C:/Users/fizza/source/repos/k22-4543/Project6/Untitled.png")) {
        // Handle error: Image not found
        return;
    }

    // Create background sprite
    sf::Sprite storySprite(storyTexture);

    // Font for loading dots
    sf::Font font;
    if (!font.loadFromFile("C:/Users/fizza/source/repos/k22-4543/Project6/HalloweenSpooky.otf")) {
        // Handle error: Font not found
        return;
    }

    sf::Text loadingDots("Loading...", font, 20);
    loadingDots.setPosition(25, window.getSize().y - 30);
    loadingDots.setFillColor(sf::Color::White);

    int dotCount = 0;
    const int maxDotCount = 3;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Check if 15 seconds have passed
        if (clockWindow.getElapsedTime().asSeconds() >= 10.0)
            break; // Exit the loop when 15 seconds have passed

        // Update loading dots every second
        if (clockLoad.getElapsedTime().asSeconds() >= 1.0) {
            dotCount = (dotCount + 1) % (maxDotCount + 1);
            loadingDots.setString("Loading" + std::string(dotCount, '.'));
            clockLoad.restart();
        }

        window.clear();
        // Draw your content here
        window.draw(storySprite);
        window.draw(loadingDots);
        window.display();
    }

    window.close(); // Ensure the window is closed after the loop
}

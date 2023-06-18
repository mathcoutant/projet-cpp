//
// Created by leo on 10/06/23.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "DebugB2Draw.h"
#include "Enemy.h"
#include "ContactListener.h"
#include <vector>

class Game {
    sf::Texture playerTexture;
    sf::Texture enemyTexture;
    sf::Texture coinTexture;
    sf::Texture graveTexture;
    sf::Sprite coinSprite;

    sf::Time timePerFrame = sf::seconds(1.f / 60.f);
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(1920, 1080), "projet cpp", sf::Style::Fullscreen);
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Coin>> coins;
    std::unique_ptr<Grave> grave;
    std::unique_ptr<ContactListener> contactListener = std::make_unique<ContactListener>();
    DebugB2Draw debugB2Draw;

    sf::RectangleShape hBarBG = sf::RectangleShape(sf::Vector2f(500, 50));
    sf::RectangleShape hBar = sf::RectangleShape(sf::Vector2f(500, 50));;
    sf::Text coinsText;
    sf::Font font;

    void update(sf::Time deltaTime);

    void render();

    void renderUI();

    void handleEvent();

public:
    void run();

    Game();
};

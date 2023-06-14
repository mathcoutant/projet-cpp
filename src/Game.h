//
// Created by leo on 10/06/23.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include <vector>

class Game {
    sf::Time timePerFrame = sf::seconds(1.f/60.f);
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(1920,1080),"projet cpp",sf::Style::Fullscreen);
    Player player;
    Enemy enemy = Enemy::Enemy(player);

    void update(sf::Time deltaTime);
    void render();
    void handleEvent();
public:
    void run();
    Game();
};

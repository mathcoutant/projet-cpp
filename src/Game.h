//
// Created by leo on 10/06/23.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "DebugB2Draw.h"
#include "Enemy.h"
#include "ContactListener.h"
#include "SFMLOrthogonalLayer.h"
#include <vector>

class Game {
    sf::Texture playerTexture;
    sf::Texture enemyTexture;
    sf::Texture coinTexture;
    sf::Texture graveTexture;
    sf::Texture diggedGraveTexture;
    sf::Sprite coinSprite;

    sf::Time timePerFrame = sf::seconds(1.f / 60.f);
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(1920, 1080), "projet cpp", sf::Style::Fullscreen);
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Coin>> coins;
    std::vector<std::unique_ptr<Grave>> graves;
    std::unique_ptr<ContactListener> contactListener = std::make_unique<ContactListener>();
    DebugB2Draw debugB2Draw;

    std::unique_ptr<MapLayer> tilemap;

    sf::RectangleShape hBarBG = sf::RectangleShape(sf::Vector2f(500, 50));
    sf::RectangleShape hBar = sf::RectangleShape(sf::Vector2f(500, 50));;
    sf::Text coinsText;
    sf::Font font;

    /// @param deltaTime the time between this update and the previous update.
    /// Update the state of the game, by first updating the physic simulation and then updating each entities.
    void update(sf::Time deltaTime);

    /// Render the state of the game on screen
    void render();

    // Render the UI on screen
    void renderUI();

    /// Handle SFML windows and keyboards events.
    /// When receiving a keyboard event, it is send to the Player.
    void handleEvent();

    /// load all textures
    void loadTextures();

    /// Instantiate entities of the game (Player, ennemies and grave)
    void settingUpEntities();

public:
    /// Run the game.
    void run();

    Game();

    /// The destructor of the Game class. We need a destructor to ensure we destroy entities (destroying their rigidbody)
    /// before destroying the contactListener.
    ~Game();
};

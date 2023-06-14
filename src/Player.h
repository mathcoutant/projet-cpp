//
// Created by leo on 14/06/23.
//

#pragma once


#include "Entity.h"
#include "SFML/Window/Keyboard.hpp"

class Player : public Entity {
    bool isMovingUp = false;
    bool isMovingDown = false;
    bool isMovingLeft = false;
    bool isMovingRight = false;
public:
    explicit Player();
    void createBody(b2World& world);
    void handleInput(sf::Keyboard::Key key, bool isPressed);
    void update(sf::Time deltaTime) override;
};

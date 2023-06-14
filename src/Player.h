//
// Created by leo on 14/06/23.
//

#pragma once


#include "Entity.h"
#include "SFML/Window/Keyboard.hpp"
#include "PlayerState.h"
#include "MoveState.h"

class Player : public Entity {
    std::unique_ptr<PlayerState> state;
public:
    explicit Player();

    void handleInput(sf::Keyboard::Key key, bool isPressed);

    void update(sf::Time deltaTime) override;
};

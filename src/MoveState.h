//
// Created by leo on 14/06/23.
//

#pragma once


#include "PlayerState.h"
#include "Player.h"
#include "SFML/System/Time.hpp"

class Player;

class MoveState : public PlayerState {
public:
    void handleInput(Player &player, sf::Keyboard::Key key, bool isPressed) override;

    PlayerState *update(Player &player, sf::Time deltaTime) override;

    ~MoveState() override = default;

};


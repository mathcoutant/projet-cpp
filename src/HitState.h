//
// Created by leo on 15/06/23.
//

#pragma once


#include "PlayerState.h"
#include "SFML/System/Clock.hpp"

class HitState : public PlayerState {
    sf::Clock clock;
    float stunTime{0.5f};

public:
    void handleInput(Player &player, sf::Keyboard::Key key, bool isPressed) override;

    std::unique_ptr<PlayerState> update(Player &player, sf::Time deltaTime) override;
};

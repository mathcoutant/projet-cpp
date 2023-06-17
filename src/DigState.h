//
// Created by leo on 15/06/23.
//

#pragma once


#include "PlayerState.h"
#include "Grave.h"

class DigState : public PlayerState {
public:
    explicit DigState(const Grave& grave);
    void handleInput(Player &player, sf::Keyboard::Key key, bool isPressed) override;

    std::unique_ptr<PlayerState> update(Player &player, sf::Time deltaTime) override;
};

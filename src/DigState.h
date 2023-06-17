//
// Created by leo on 15/06/23.
//

#pragma once


#include "PlayerState.h"
#include "Grave.h"

class DigState : public PlayerState {
private:
    Grave *grave;
public:
    explicit DigState(Grave *grave);

    void handleInput(Player &player, sf::Keyboard::Key key, bool isPressed) override;

    PlayerState *update(Player &player, sf::Time deltaTime) override;
};

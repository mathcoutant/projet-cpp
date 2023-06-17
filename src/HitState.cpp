//
// Created by leo on 15/06/23.
//

#include "HitState.h"
#include "MoveState.h"

void HitState::handleInput(Player &player, sf::Keyboard::Key key, bool isPressed) {
    // when the player is hit, he can't move anymore
}

PlayerState *HitState::update(Player &player, sf::Time deltaTime) {
    if (clock.getElapsedTime().asSeconds() < stunTime) {
        return nullptr;
    } else {
        return new MoveState();
    }
}

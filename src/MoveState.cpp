//
// Created by leo on 14/06/23.
//

#include "MoveState.h"
#include "SFML/System/Vector2.hpp"
#include "PhysicsUtil.h"
#include "DigState.h"

PlayerState *MoveState::update(Player &player, sf::Time deltaTime) {
    if (!nextState) {
        auto moveDirection = sf::Vector2f(0.f, 0.f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            moveDirection.x -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            moveDirection.x += 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            moveDirection.y -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            moveDirection.y += 1.f;

        player.setVelocity(physics::normalize(moveDirection));
    }
    return nextState;
}

void MoveState::handleInput(Player &player, sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::Space && isPressed) {
        Grave *grave = player.getGrave();
        if (grave != nullptr) {
            if (!grave->isDigged()) {
                player.setVelocity(sf::Vector2f(0.f, 0.f));
                nextState = new DigState(grave);
            }
        }
    }
}
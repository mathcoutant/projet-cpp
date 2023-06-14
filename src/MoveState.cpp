//
// Created by leo on 14/06/23.
//

#include "MoveState.h"
#include "SFML/System/Vector2.hpp"
#include "PhysicsUtil.h"

std::unique_ptr<PlayerState> MoveState::update(Player& player, sf::Time deltaTime) {
    return nullptr;
}

void MoveState::handleInput(Player& player, sf::Keyboard::Key key, bool isPressed) {
    auto moveDirection = sf::Vector2f(0.f, 0.f);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        moveDirection.x -= 1.f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        moveDirection.x += 1.f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        moveDirection.y -= 1.f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        moveDirection.y += 1.f;

    player.setVelocity(physics::normalize(moveDirection));
}
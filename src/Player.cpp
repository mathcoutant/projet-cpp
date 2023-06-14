//
// Created by leo on 14/06/23.
//

#include "Player.h"

Player::Player() : Entity() {
}

void Player::handleInput(sf::Keyboard::Key key, bool isPressed) {
    switch (key) {
        case sf::Keyboard::Left:
            isMovingLeft = isPressed;
            break;
        case sf::Keyboard::Right:
            isMovingRight = isPressed;
            break;
        case sf::Keyboard::Up:
            isMovingUp = isPressed;
            break;
        case sf::Keyboard::Down:
            isMovingDown = isPressed;
            break;
        default:
            break;
    }
}

void Player::update(sf::Time deltaTime) {
    moveDirection = sf::Vector2f(0.f,0.f);
    if(isMovingUp)
        moveDirection.y -= 1.f;
    if(isMovingDown)
        moveDirection.y += 1.f;
    if(isMovingLeft)
        moveDirection.x -= 1.f;
    if(isMovingRight)
        moveDirection.x += 1.f;

    Entity::update(deltaTime);
}

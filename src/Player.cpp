//
// Created by leo on 14/06/23.
//

#include "Player.h"

Player::Player() : Entity() {}

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

    moveDirection = sf::Vector2f (0.f,0.f);

    if(isMovingLeft)
        moveDirection.x -= 1.f;
    if(isMovingRight)
        moveDirection.x += 1.f;
    if(isMovingUp)
        moveDirection.y -= 1.f;
    if(isMovingDown)
        moveDirection.y += 1.f;

    if(moveDirection != sf::Vector2f (0.f,0.f))
        moveDirection /= std::sqrt(moveDirection.x*moveDirection.x + moveDirection.y*moveDirection.y);

    setVelocity(moveDirection);
}

void Player::createBody(b2World& world){
    b2BodyDef bodyDef;
    bodyDef.position      = b2Vec2(0.f, 0.f);
    bodyDef.angle         = 0.f;
    bodyDef.allowSleep    = false;
    bodyDef.fixedRotation = true;
    bodyDef.gravityScale  = 1.f;
    bodyDef.type          = b2_dynamicBody;
    //create a box shape
    b2PolygonShape boxShape;

    boxShape.SetAsBox(boundingBox.width /(2*physics::SCALE), boundingBox.height /(2*physics::SCALE));
    //create a fixture and provide the shape to the body
    b2FixtureDef fixtureDef;
    fixtureDef.shape        = &boxShape;
    fixtureDef.isSensor     = false;
    fixtureDef.density      = 50.f;
    fixtureDef.friction     = 0.1f;
    fixtureDef.restitution  = 0.0f;
    Entity::createBody(bodyDef,world,fixtureDef);
}

void Player::update(sf::Time deltaTime) {
    moveDirection = sf::Vector2f (0.f,0.f);
    Entity::update(deltaTime);
}

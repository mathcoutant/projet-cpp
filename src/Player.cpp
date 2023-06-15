#include "Player.h"
#include <iostream>
#include "Link.h"

Player::Player() : Entity() {
    state = std::make_unique<MoveState>(MoveState());

    texture.loadFromFile("resources/images/tilemap/raider.png");
    sprite.setTexture(texture);
    sprite.setScale(4.f, 4.f);
    sf::FloatRect boundingBox = sprite.getGlobalBounds();
    sf::FloatRect localBoundingBox = sprite.getLocalBounds();
    sprite.setOrigin(localBoundingBox.width / 2, localBoundingBox.height / 2);

    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(0.f, 0.f);
    bodyDef.allowSleep = true;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_dynamicBody;
    //create a box shape
    b2PolygonShape boxShape;


    boxShape.SetAsBox(boundingBox.width / (2 * physics::SCALE), boundingBox.height / (2 * physics::SCALE));
    //create a fixture and provide the shape to the body
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.isSensor = false;
    fixtureDef.density = 50.f;
    fixtureDef.friction = 0.1f;
    fixtureDef.restitution = 0.0f;

    body = std::unique_ptr<b2Body, physics::b2BodyDeleter>(PhysicWorld::GetInstance()->CreateBody(&bodyDef));
    body->CreateFixture(&fixtureDef);
    body->GetUserData().pointer = (uintptr_t)new Link(0, this);
}

void Player::handleInput(sf::Keyboard::Key key, bool isPressed) {
    state->handleInput(*this,key,isPressed);
}

void Player::update(sf::Time deltaTime) {
    if (std::unique_ptr<PlayerState> nextState = state->update(*this, deltaTime); nextState)
        state.swap(nextState);
    Entity::update(deltaTime);
}

void Player::takeDamage() {
    health--;
    if (health <= 0) {
        health = 0;
        std::cout << "Your dead !\n";
    }
}

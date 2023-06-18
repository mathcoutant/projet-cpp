#include "Player.h"
#include <iostream>


Player::Player(const sf::Texture &texture, float x, float y) : Entity(texture, x, y) {
    type = EntityType::PLAYER;
    state = std::make_unique<MoveState>(MoveState());
    sprite.setScale(4.f, 4.f);
    sf::FloatRect boundingBox = sprite.getGlobalBounds();
    sf::FloatRect localBoundingBox = sprite.getLocalBounds();
    sprite.setOrigin(localBoundingBox.width / 2, localBoundingBox.height / 2);

    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(physics::sfTob2(getPosition()));
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
    body->GetUserData().pointer = (uintptr_t) this;
}

void Player::handleInput(sf::Keyboard::Key key, bool isPressed) {
    state->handleInput(*this, key, isPressed);
}

void Player::update(sf::Time deltaTime) {
    if (PlayerState *nextState = state->update(*this, deltaTime); nextState != nullptr)
        state.reset(nextState);
    Entity::update(deltaTime);
}

void Player::takeDamage() {
    std::cout << health << "\n";
    health--;
    if (health <= 0) {
        health = 0;
        std::cout << "Your dead !\n";
    }
}

void Player::setGrave(Grave *grave) {
    this->grave = grave;
    if (grave != nullptr) {
        std::cout << "on grave" << std::endl;
    } else {
        std::cout << "not on grave" << std::endl;
    }
}

Grave *Player::getGrave() {
    return grave;
}

void Player::collectCoin(Coin *coin) {
    coins++;
    coin->collect();
}

PlayerState* Player::getState() {
    return state.get();
}

//
// Created by leo on 14/06/23.
//

#include "Entity.h"
#include <SFML/Graphics/Texture.hpp>
#include "PhysicWorld.h"

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Entity::update(sf::Time deltaTime) {
    setPosition(physics::b2Tosf(body->GetPosition()));
    sprite.setPosition(getPosition());
}

Entity::Entity() = default;

void Entity::setSpeed(float speed) {
    this->speed = speed;
}

void Entity::createBody(b2BodyDef &bodyDef, b2FixtureDef &fixtureDef) {
    body = PhysicWorld::GetInstance()->CreateBody(&bodyDef);
    body->CreateFixture(&fixtureDef);
}

void Entity::setVelocity(sf::Vector2f v) {
    body->SetLinearVelocity(physics::sfTob2(v * speed));
}

Entity::~Entity() = default;
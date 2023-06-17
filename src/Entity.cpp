#include "Entity.h"

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Entity::update(sf::Time deltaTime) {
    if (body)
        setPosition(physics::b2Tosf(body->GetPosition()));
    sprite.setPosition(getPosition());
}

Entity::Entity() = default;

Entity::Entity(const sf::Texture &texture, float x, float y) {
    sprite.setTexture(texture);
    setPosition(x, y);
}


void Entity::setSpeed(float s) {
    speed = s;
}


void Entity::setVelocity(sf::Vector2f v) {
    body->SetLinearVelocity(physics::sfTob2(v * speed));
}

Entity::~Entity() = default;
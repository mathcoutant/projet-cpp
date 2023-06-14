//
// Created by leo on 14/06/23.
//

#include "Entity.h"
#include <SFML/Graphics/Texture.hpp>

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}
void Entity::update(sf::Time deltaTime) {
    move(moveDirection * speed * deltaTime.asSeconds());
    sprite.setPosition(getPosition());
}

Entity::Entity() {
    texture.loadFromFile("resources/images/tilemap/test_texture.png");
    sprite.setTexture(texture);
}

void Entity::setSpeed(float speed) {
    this->speed = speed;
}

Entity::~Entity() = default;
//
// Created by leo on 14/06/23.
//

#include "Entity.h"
#include <SFML/Graphics/Texture.hpp>
#include <cmath>

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}
void Entity::update(sf::Time deltaTime) {
    move(normalize(moveDirection) * speed * deltaTime.asSeconds());
    sprite.setPosition(getPosition());
}

sf::Vector2f Entity::normalize(sf::Vector2f v) const {
    float norme = std::sqrt(v.x * v.x + v.y * v.y);
    if (norme != 0) return (v / norme);
    return v;
}

Entity::Entity() {
    texture.loadFromFile("resources/images/tilemap/test_texture.png");
    sprite.setTexture(texture);
}

void Entity::setSpeed(float speed) {
    this->speed = speed;
}

Entity::~Entity() = default;

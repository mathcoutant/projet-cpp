#include "Enemy.h"

Enemy::Enemy(Player& p) : Entity(), player(p) {
    sprite.setScale(0.5f, 0.5f);
}

void Enemy::update(sf::Time deltaTime) {
    moveDirection = player.getPosition() - getPosition();
    Entity::update(deltaTime);
}

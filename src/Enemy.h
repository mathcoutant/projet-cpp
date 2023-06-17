#pragma once

#include "Entity.h"
#include "Player.h"

class Enemy : public Entity {

public:
    explicit Enemy(Player &p, const sf::Texture& texture);

    void update(sf::Time deltaTime) override;

private:
    Player &player;
};
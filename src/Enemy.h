#pragma once

#include "Entity.h"
#include "Player.h"

class Enemy : public Entity {

public:
    explicit Enemy(Player &p, const sf::Texture &texture, float x, float y);

    void update(sf::Time deltaTime) override;

    void respawn();

private:
    Player &player;
    bool respawnFlag = false;
    sf::Vector2f initPosition;
};
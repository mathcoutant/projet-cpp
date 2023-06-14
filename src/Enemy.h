#pragma once

#include "Entity.h"
#include "Player.h"

class Enemy : public Entity {

public:
    explicit Enemy(Player& p);
    void update(sf::Time deltaTime) override;
private:
    Player& player;
};
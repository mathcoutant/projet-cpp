//
// Created by leo on 17/06/23.
//

#pragma once


#include "Entity.h"
#include "Grave.h"

class Grave;

class Coin : public Entity {
    void applyRandomForce();

public:
    bool collected = false;

    Coin(const sf::Texture &texture, float x, float y);

    void collect();

    void update(sf::Time deltaTime) override;
};
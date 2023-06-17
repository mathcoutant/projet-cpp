//
// Created by leo on 15/06/23.
//

#pragma once


#include "Entity.h"
#include "Coin.h"
#include <vector>

class Coin;

class Grave : public Entity {
private:
    std::vector<std::unique_ptr<Coin>> *coins;
    sf::Texture coinTexture;

public:
    Grave(const sf::Texture &graveTexture, sf::Texture &coinTexture, float x, float y,
          std::vector<std::unique_ptr<Coin>> &coins);

    void dig();
};

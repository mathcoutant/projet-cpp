#pragma once

#include "Entity.h"
#include "SFML/Window/Keyboard.hpp"
#include "PlayerState.h"
#include "MoveState.h"
#include "Grave.h"


class Player : public Entity {
    std::unique_ptr<PlayerState> state;
    Grave *grave = nullptr;

public:
    int health = 3;
    int coins = 0;

    explicit Player(const sf::Texture &texture, float x, float y);

    void handleInput(sf::Keyboard::Key key, bool isPressed);

    void takeDamage();

    void update(sf::Time deltaTime) override;

    void setGrave(Grave *grave);

    Grave *getGrave();

    void collectCoin(Coin *Coin);
};

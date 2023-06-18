//
// Created by leo on 14/06/23.
//

#pragma once


#include "SFML/Window/Keyboard.hpp"
#include "SFML/System/Time.hpp"
#include <memory>

class Player;

class PlayerState {
protected:
    PlayerState *nextState = nullptr;
public:
    virtual ~PlayerState() = default;

    virtual void handleInput(Player &player, sf::Keyboard::Key key, bool isPressed) = 0;

    virtual PlayerState *update(Player &player, sf::Time deltaTime) {
        return nextState;
    };
};


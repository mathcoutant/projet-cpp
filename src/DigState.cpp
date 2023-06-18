//
// Created by leo on 15/06/23.
//

#include <iostream>
#include "DigState.h"
#include "MoveState.h"


void DigState::handleInput(Player &player, sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::BackSpace && isPressed) {
        grave->setDigged();
        nextState = new MoveState();
    }

    if (key == sf::Keyboard::Space && isPressed) {
        std::cout << "Dig dig dig" << std::endl;
        grave->dig();
    }
}

PlayerState *DigState::update(Player &player, sf::Time deltaTime) {
    return nextState;
}

DigState::DigState(Grave *grave) : grave(grave) {}



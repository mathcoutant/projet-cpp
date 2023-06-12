//
// Created by leo on 10/06/23.
//

#include "Game.h"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Sleep.hpp"

Game::Game(){
    window.setFramerateLimit(60);
    player.setFillColor(sf::Color::Red);
}

void Game::run() {

    sf::Clock clock;
    sf::Time timeAfterLastUpdate = sf::Time::Zero;
    while (window.isOpen()) {
        handleEvent();
        timeAfterLastUpdate += clock.restart();
        while (timeAfterLastUpdate > timePerFrame){
            timeAfterLastUpdate -= timePerFrame;
            handleEvent();
            update(timePerFrame);
        }
        render();

    }
}


void Game::handleEvent() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void Game::update(sf::Time deltaTime) {
    // update ne fait rien pour l'instant, car on a rien à update
}

void Game::render() {
    window.clear(sf::Color::White);
    window.draw(player);
    window.display();
}
//
// Created by leo on 10/06/23.
//

#include "Game.h"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Sleep.hpp"

Game::Game() {
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    player.setSpeed(500.f);
    enemy.setSpeed(100.f);
    enemy.setScale(0.5f, 0.5f);
}

void Game::run() {

    sf::Clock clock;
    sf::Time timeAfterLastUpdate = sf::Time::Zero;
    while (window.isOpen()) {
        handleEvent();
        timeAfterLastUpdate += clock.restart();
        while (timeAfterLastUpdate > timePerFrame) {
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
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                player.handleInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                player.handleInput(event.key.code, false);
                break;
            default:
                break;
        }
    }
}

void Game::update(sf::Time deltaTime) {
    player.update(deltaTime);
    enemy.update(deltaTime);
}

void Game::render() {
    window.clear(sf::Color::White);
    window.draw(player);
    window.draw(enemy);
    window.display();
}
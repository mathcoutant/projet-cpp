//
// Created by leo on 10/06/23.
//

#include <iostream>
#include <algorithm>
#include "Game.h"
#include "SFML/System/Clock.hpp"
#include "PhysicWorld.h"
#include "tmxlite/Map.hpp"
#include "SFMLOrthogonalLayer.h"

Game::Game() : debugB2Draw(window) {

    tmx::Map map;
    map.load("resources/tilemap.tmx");

    tilemap = std::make_unique<MapLayer>(map, 0);


    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    loadTextures();
    settingUpEntities();

    debugB2Draw.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit | b2Draw::e_pairBit |
                         b2Draw::e_centerOfMassBit);
    PhysicWorld::GetInstance()->SetDebugDraw(&debugB2Draw);
    PhysicWorld::GetInstance()->SetContactListener(contactListener.get());

    hBarBG.setFillColor(sf::Color(0, 0, 0));
    hBar.setFillColor(sf::Color(255, 0, 0));
    hBarBG.setPosition((window.getSize().x - hBarBG.getSize().x) / 2, window.getSize().y - 100);
    font.loadFromFile("resources/TheConfessionRegular.ttf");
    coinsText.setFont(font);
    coinsText.setCharacterSize(50);
    coinsText.setFillColor(sf::Color::White);
    coinsText.setStyle(sf::Text::Bold);
    coinSprite.setTexture(coinTexture);
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
                player->handleInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                player->handleInput(event.key.code, false);
                break;
            default:
                break;
        }
    }
}

void Game::update(sf::Time deltaTime) {
    coins.erase(std::remove_if(coins.begin(), coins.end(), [](auto &c) -> bool { return c->collected; }), coins.end());
    PhysicWorld::GetInstance()->Step(timePerFrame.asSeconds(), 6, 2);
    player->update(deltaTime);
    for (const auto &g: graves) {
        g->update(deltaTime);
    }
    for (const auto &c: coins) {
        c->update(deltaTime);
    }
    for (const auto &enemy: enemies) {
        enemy->update(deltaTime);
    }
}

void Game::render() {
    window.clear(sf::Color::White);
    window.draw(*tilemap);

    for (const auto &g: graves) {
        window.draw(*g);
    }

    for (const auto &c: coins) {
        window.draw(*c);
    }

    for (const auto &enemy: enemies) {
        window.draw(*enemy);
    }
    window.draw(*player);
    renderUI();
    //PhysicWorld::GetInstance()->DebugDraw();
    window.display();
}

void Game::renderUI() {
    if (player->health == 0) {
        hBar.setSize(sf::Vector2f(0, 50));
        window.draw(hBarBG);
        window.draw(hBar);
        window.display();
        sf::sleep(sf::seconds(2));
        window.close();
    } else {
        hBar.setSize(sf::Vector2f(500.f * (player->health / 3.f), 50));
    }
    hBar.setPosition((window.getSize().x - hBarBG.getSize().x) / 2, window.getSize().y - 100);

    coinsText.setString(" x " + std::to_string(player->coins));
    coinsText.setPosition(300, window.getSize().y - 110);

    coinSprite.setPosition(250, window.getSize().y - 110);
    coinSprite.setScale(sf::Vector2f(4.f, 4.f));

    window.draw(hBarBG);
    window.draw(hBar);
    window.draw(coinsText);
    window.draw(coinSprite);
}


Game::~Game() {
    player.reset();
    enemies.erase(enemies.begin(), enemies.end());
    coins.erase(coins.begin(), coins.end());
    graves.erase(graves.begin(), graves.end());
}

void Game::loadTextures() {
    playerTexture.loadFromFile("resources/images/raider.png");
    coinTexture.loadFromFile("resources/images/coin.png");
    enemyTexture.loadFromFile("resources/images/fantome.png");
    graveTexture.loadFromFile("resources/images/tomb.png");
    diggedGraveTexture.loadFromFile("resources/images/tomb_2.png");
}

void Game::settingUpEntities() {
    player = std::make_unique<Player>(playerTexture, 200, 200);
    enemies.push_back(std::make_unique<Enemy>(*player, enemyTexture, 0, 0));
    enemies.push_back(std::make_unique<Enemy>(*player, enemyTexture, 1920, 0));
    enemies.push_back(std::make_unique<Enemy>(*player, enemyTexture, 0, 1080));
    enemies.push_back(std::make_unique<Enemy>(*player, enemyTexture, 1920, 1080));
    graves.push_back(std::make_unique<Grave>(graveTexture, diggedGraveTexture, coinTexture, 500, 500, coins));
    graves.push_back(std::make_unique<Grave>(graveTexture, diggedGraveTexture, coinTexture, 1600, 900, coins));
    graves.push_back(std::make_unique<Grave>(graveTexture, diggedGraveTexture, coinTexture, 900, 500, coins));
    graves.push_back(std::make_unique<Grave>(graveTexture, diggedGraveTexture, coinTexture, 200, 500, coins));
    graves.push_back(std::make_unique<Grave>(graveTexture, diggedGraveTexture, coinTexture, 1600, 200, coins));
    for (const auto &enemy: enemies) {
        enemy->setSpeed(100.f);
    }
    player->setSpeed(500.f);
}

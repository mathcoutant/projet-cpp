//
// Created by leo on 10/06/23.
//

#include <iostream>
#include <algorithm>
#include "Game.h"
#include "SFML/System/Clock.hpp"
#include "PhysicWorld.h"

Game::Game() : debugB2Draw(window) {
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    playerTexture.loadFromFile("resources/images/tilemap/raider.png");
    coinTexture.loadFromFile("resources/images/tilemap/coin.png");
    enemyTexture.loadFromFile("resources/images/tilemap/fantome.png");
    graveTexture.loadFromFile("resources/images/tilemap/test_texture.png");

    player = std::make_unique<Player>(playerTexture, 200, 200);
    enemies.push_back(std::make_unique<Enemy>(*player, enemyTexture, 900, 900));
    enemies.push_back(std::make_unique<Enemy>(*player, enemyTexture, 0, 900));
    grave = std::make_unique<Grave>(graveTexture, coinTexture, 500, 500, coins);
    for (const auto &enemy: enemies) {
        enemy->setSpeed(100.f);
    }

    player->setSpeed(500.f);

    b2Body *body;
    b2BodyDef bodyDef;
    bodyDef.position = physics::sfTob2(sf::Vector2f(500.f, 500.f));
    bodyDef.angle = 0.f;
    bodyDef.allowSleep = true;
    bodyDef.fixedRotation = false;
    bodyDef.gravityScale = 1.f;
    bodyDef.type = b2_staticBody;
    body = PhysicWorld::GetInstance()->CreateBody(&bodyDef);

    b2PolygonShape boxShape;

    boxShape.SetAsBox(20.f / physics::SCALE, 500.f / physics::SCALE);
    //create a fixture and provide the shape to the body
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.isSensor = false;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.1f;
    fixtureDef.restitution = 0.1f;
    body->CreateFixture(&fixtureDef);

    debugB2Draw.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit | b2Draw::e_pairBit |
                         b2Draw::e_centerOfMassBit);
    PhysicWorld::GetInstance()->SetDebugDraw(&debugB2Draw);

    PhysicWorld::GetInstance()->SetContactListener(contactListener.get());

    hBarBG.setFillColor(sf::Color(0, 0, 0));
    hBar.setFillColor(sf::Color(255, 0, 0));
    hBarBG.setPosition((window.getSize().x - hBarBG.getSize().x) / 2, window.getSize().y - 100);
    font.loadFromFile("resources/images/tilemap/TheConfessionRegular.ttf");
    coinsText.setFont(font);
    coinsText.setCharacterSize(50);
    coinsText.setFillColor(sf::Color::Black);
    coinsText.setStyle(sf::Text::Bold);
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
    grave->update(deltaTime);
    for (const auto &c: coins) {
        c->update(deltaTime);
    }
    for (const auto &enemy: enemies) {
        enemy->update(deltaTime);
    }
}

void Game::render() {
    window.clear(sf::Color::White);
    window.draw(*grave);


    for (const auto &c: coins) {
        window.draw(*c);
    }
    for (const auto &enemy: enemies) {
        window.draw(*enemy);
    }
    window.draw(*player);
    renderUI();
    PhysicWorld::GetInstance()->DebugDraw();
    window.display();
}

void Game::renderUI() {
    if (player->health == 0) {
        hBar.setSize(sf::Vector2f(0, 50));
    } else {
        hBar.setSize(sf::Vector2f(500.f * (player->health / 3.f), 50));
    }
    hBar.setPosition((window.getSize().x - hBarBG.getSize().x) / 2, window.getSize().y - 100);

    coinsText.setString(" x " + std::to_string(player->coins));
    coinsText.setPosition(300, window.getSize().y - 110);

    window.draw(hBarBG);
    window.draw(hBar);
    window.draw(coinsText);
}

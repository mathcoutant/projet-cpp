//
// Created by leo on 10/06/23.
//

#include "Game.h"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Sleep.hpp"

Game::Game() : debugB2Draw(window) {
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    player.setSpeed(500.f);



    player.createBody(world);
    enemy.createBody(world);

    b2Body* body;
    b2BodyDef bodyDef;
    bodyDef.position      = physics::sfTob2(sf::Vector2f(500.f,500.f));
    bodyDef.angle         = 0.f;
    bodyDef.allowSleep    = true;
    bodyDef.fixedRotation = false;
    bodyDef.gravityScale  = 1.f;
    bodyDef.type          = b2_staticBody;
    body = world.CreateBody(&bodyDef);

    b2PolygonShape boxShape;

    boxShape.SetAsBox(20.f / physics::SCALE, 500.f / physics::SCALE);
    //create a fixture and provide the shape to the body
    b2FixtureDef fixtureDef;
    fixtureDef.shape        = &boxShape;
    fixtureDef.isSensor     = false;
    fixtureDef.density      = 1.f;
    fixtureDef.friction     = 0.1f;
    fixtureDef.restitution  = 0.1f;
    body->CreateFixture(&fixtureDef);

    debugB2Draw.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit);   // | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);
    world.SetDebugDraw(&debugB2Draw);
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
    world.Step(timePerFrame.asSeconds(),6,2);
    player.update(deltaTime);
    enemy.update(deltaTime);
}

void Game::render() {
    window.clear(sf::Color::White);
    window.draw(player);
    window.draw(enemy);
    world.DebugDraw();
    window.display();
}
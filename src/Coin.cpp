//
// Created by leo on 17/06/23.
//

#include "Coin.h"
#include <random>

float random_0_to_1() {
    static std::random_device rd;
    static std::default_random_engine engine(rd());
    std::uniform_real_distribution<float> distribution(0, 1);
    return distribution(engine);
}


Coin::Coin(const sf::Texture &texture, float x, float y) : Entity(texture, x, y) {
    type = EntityType::COIN;
    sprite.scale(2.f, 2.f);
    sf::FloatRect boundingBox = sprite.getGlobalBounds();
    sf::FloatRect localBoundingBox = sprite.getLocalBounds();
    sprite.setOrigin(localBoundingBox.width / 2, localBoundingBox.height / 2);

    b2BodyDef bodyDef;
    bodyDef.position = physics::sfTob2(getPosition());
    bodyDef.allowSleep = true;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_dynamicBody;
    //create a box shape
    b2PolygonShape boxShape;

    // SetAsBox need the half-width and half-height, because... I don't know ?
    boxShape.SetAsBox(boundingBox.width / (2 * physics::SCALE), boundingBox.height / (2 * physics::SCALE));
    //create a fixture and provide the shape to the body
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.f;
    fixtureDef.isSensor = true;

    body = std::unique_ptr<b2Body, physics::b2BodyDeleter>(PhysicWorld::GetInstance()->CreateBody(&bodyDef));
    body->CreateFixture(&fixtureDef);
    body->GetUserData().pointer = (uintptr_t) this;
    applyRandomForce();
}

void Coin::applyRandomForce() {

    body->ApplyLinearImpulseToCenter(b2Vec2(50 * (random_0_to_1() - 0.5f), 50 * (random_0_to_1() - 0.5f)), true);
}

void Coin::update(sf::Time deltaTime) {
    b2Vec2 vel = body->GetLinearVelocity();
    float vSquared = vel.LengthSquared();
    vel.Normalize();
    b2Vec2 drag = 3 * vSquared * -vel;
    body->ApplyForceToCenter(drag, false);
    Entity::update(deltaTime);
}

void Coin::collect() {
    collected = true;
}



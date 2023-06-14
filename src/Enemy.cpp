#include "Enemy.h"

Enemy::Enemy(Player& p) : Entity(), player(p) {
}

void Enemy::update(sf::Time deltaTime) {
    moveDirection = player.getPosition() - getPosition();
    setVelocity(moveDirection);
    Entity::update(deltaTime);
}

void Enemy::createBody(b2World &world) {
    b2BodyDef bodyDef;
    bodyDef.position      = physics::sfTob2(getPosition());
    bodyDef.angle         = 0.f;
    bodyDef.allowSleep    = false;
    bodyDef.fixedRotation = true;
    bodyDef.gravityScale  = 1.f;
    bodyDef.type          = b2_kinematicBody;
    //create a box shape
    b2PolygonShape boxShape;

    boxShape.SetAsBox(boundingBox.width /(2*physics::SCALE), boundingBox.height / (2*physics::SCALE));
    //create a fixture and provide the shape to the body
    b2FixtureDef fixtureDef;
    fixtureDef.shape        = &boxShape;
    fixtureDef.isSensor     = true;
    fixtureDef.density      = 50.f;
    fixtureDef.friction     = 0.1f;
    fixtureDef.restitution  = 0.0f;
    Entity::createBody(bodyDef,world,fixtureDef);
}

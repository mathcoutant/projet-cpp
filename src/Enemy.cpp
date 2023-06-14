#include "Enemy.h"

Enemy::Enemy(Player &p) : Entity(), player(p) {
    texture.loadFromFile("resources/images/tilemap/fantome.png");
    sprite.setTexture(texture);
    sprite.setScale(4.f, 4.f);
    sf::FloatRect boundingBox = sprite.getGlobalBounds();
    sf::FloatRect localBoundingBox = sprite.getLocalBounds();
    sprite.setOrigin(localBoundingBox.width / 2, localBoundingBox.height / 2);

    b2BodyDef bodyDef;
    bodyDef.position = physics::sfTob2(getPosition());
    bodyDef.allowSleep = true;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_kinematicBody;
    //create a box shape
    b2PolygonShape boxShape;

    // SetAsBox need the half-width and half-height, because... I don't know ?
    boxShape.SetAsBox(boundingBox.width / (2 * physics::SCALE), boundingBox.height / (2 * physics::SCALE));
    //create a fixture and provide the shape to the body
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.isSensor = true;
    Entity::createBody(bodyDef, fixtureDef);
}

void Enemy::update(sf::Time deltaTime) {
    moveDirection = physics::normalize(player.getPosition() - getPosition());
    setVelocity(moveDirection);
    Entity::update(deltaTime);
}


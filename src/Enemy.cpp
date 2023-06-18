#include "Enemy.h"

Enemy::Enemy(Player &p, const sf::Texture &texture, float x, float y) :
        Entity(texture, x, y),
        player(p),
        initPosition(x, y) {
    type = EntityType::ENEMY;
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


    body = std::unique_ptr<b2Body, physics::b2BodyDeleter>(PhysicWorld::GetInstance()->CreateBody(&bodyDef));
    body->CreateFixture(&fixtureDef);
    body->GetUserData().pointer = (uintptr_t) this;
}

void Enemy::update(sf::Time deltaTime) {
    if (respawnFlag) {
        body->SetTransform(physics::sfTob2(initPosition), 0);
        respawnFlag = false;
    }
    moveDirection = physics::normalize(player.getPosition() - getPosition());
    setVelocity(moveDirection);
    Entity::update(deltaTime);
}

void Enemy::respawn() {
    respawnFlag = true;
}


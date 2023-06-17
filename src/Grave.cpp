//
// Created by leo on 15/06/23.
//

#include "Grave.h"

Grave::Grave(const sf::Texture &graveTexture, sf::Texture &coinTexture, float x, float y,
             std::vector<std::unique_ptr<Coin>> &coins) :
        Entity(graveTexture, x, y), coins(&coins), coinTexture(coinTexture) {
    type = EntityType::GRAVE;
    sf::FloatRect boundingBox = sprite.getGlobalBounds();
    sf::FloatRect localBoundingBox = sprite.getLocalBounds();
    sprite.setOrigin(localBoundingBox.width / 2, localBoundingBox.height / 2);

    b2BodyDef bodyDef;
    bodyDef.position = physics::sfTob2(getPosition());
    bodyDef.allowSleep = true;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_staticBody;
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
    body->GetUserData().pointer = (uintptr_t) (this);
}

void Grave::dig() {
    float x = getPosition().x;
    float y = getPosition().y;
    coins->push_back(std::make_unique<Coin>(coinTexture, x, y));
}

//
// Created by leo on 14/06/23.
//

#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <box2d/b2_body.h>
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Time.hpp"
#include <memory>
#include "PhysicsUtil.h"

class Entity : public sf::Drawable, public sf::Transformable {
    float speed;
    b2Body* body;

    sf::Vector2f normalize(sf::Vector2f v) const;
protected:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f moveDirection = sf::Vector2f(0.f,0.f);
    sf::FloatRect boundingBox;
    void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
    void setVelocity(sf::Vector2f v);
public:
    ~Entity() override;
    Entity();
    void setSpeed(float speed);
    virtual void update(sf::Time deltaTime);

    virtual void createBody(b2BodyDef &bodyDef, b2World& world, b2FixtureDef& fixtureDef);
};

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
#include "PhysicWorld.h"


enum class EntityType {
    PLAYER, ENEMY, GRAVE, COIN
};

class Entity : public sf::Drawable, public sf::Transformable {
    float speed;

protected:

    sf::Sprite sprite;
    sf::Vector2f moveDirection = sf::Vector2f(0.f, 0.f);
    std::unique_ptr<b2Body, physics::b2BodyDeleter> body;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    EntityType type;

    ~Entity() override;

    Entity();

    Entity(const sf::Texture &texture, float x, float y);

    void setSpeed(float speed);

    virtual void update(sf::Time deltaTime);

    void setVelocity(sf::Vector2f v);
};

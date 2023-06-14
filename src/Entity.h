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

class Entity : public sf::Drawable, public sf::Transformable {
    float speed;

    sf::Vector2f normalize(sf::Vector2f v) const;
protected:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f moveDirection = sf::Vector2f(0.f,0.f);

    void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
public:
    ~Entity() override;
    Entity();
    void setSpeed(float speed);
    virtual void update(sf::Time deltaTime);
};

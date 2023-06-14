//
// Created by leo on 14/06/23.
//

#pragma once

#include "box2d/box2d.h"
#include <cmath>

namespace physics {

    const float SCALE = 30.f;

    struct b2BodyDeleter {
        void operator()(b2Body *body) const {
            body->GetWorld()->DestroyBody(body);
        }
    };

    inline float sfTob2(float x) {
        return x / SCALE;
    }

    inline float b2Tosf(float x) {
        return x * SCALE;
    }

    inline b2Color sfTob2(sf::Color c) {
        return {c.r / 255.f, c.g / 255.f, c.b / 255.f, c.a / 255.f};
    }

    inline sf::Color b2Tosf(b2Color c) {
        return sf::Color(c.r * 255, c.g * 255, c.b * 255, c.a * 255);
    }

    inline b2Vec2 sfTob2(sf::Vector2f v) {
        return {v.x / SCALE, v.y / SCALE};
    }

    inline sf::Vector2f b2Tosf(b2Vec2 v) {
        return {v.x * SCALE, v.y * SCALE};
    }

    inline sf::Vector2f normalize(sf::Vector2f v) {
        float norm = std::sqrt(v.x * v.x + v.y * v.y);
        if (norm != 0) return (v / norm);
        return v;
    }

    inline b2Vec2 normalize(b2Vec2 v) {
        if (float norm = std::sqrt(v.x * v.x + v.y * v.y); norm != 0)
            return {v.x / norm, v.y / norm};
        return v;
    }
}
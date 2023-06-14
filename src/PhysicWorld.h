//
// Created by leo on 14/06/23.
//

#pragma once

#include "box2d/b2_world.h"

class PhysicWorld : public b2World {

    explicit PhysicWorld(b2Vec2 gravity) : b2World(gravity) {};

    static PhysicWorld *world;

public:
    PhysicWorld(PhysicWorld &other) = delete;

    void operator=(const PhysicWorld &) = delete;

    static PhysicWorld *GetInstance();
};


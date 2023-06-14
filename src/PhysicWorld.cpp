//
// Created by leo on 14/06/23.
//

#include "PhysicWorld.h"

PhysicWorld *PhysicWorld::world = nullptr;

PhysicWorld *PhysicWorld::GetInstance() {
    if (world == nullptr) {
        world = new PhysicWorld(b2Vec2_zero);
    }
    return world;
}

#include <iostream>
#include "ContactListener.h"
#include "Player.h"
#include "Enemy.h"

void ContactListener::BeginContact(b2Contact* contact) {
	b2Fixture* f1 = contact->GetFixtureA();
	b2Fixture* f2 = contact->GetFixtureB();

	b2Body* b1 = f1->GetBody();
	b2Body* b2 = f2->GetBody();

	auto e1 = (Entity*)(b1->GetUserData().pointer);
	auto e2 = (Entity*)(b2->GetUserData().pointer);
    if(e1 && e2) {
        if(e1->type == EntityType::PLAYER && e2->type == EntityType::ENEMY){
            ((Player*)e1)->takeDamage();
        }
        if(e1->type == EntityType::ENEMY && e2->type == EntityType::PLAYER){
            ((Player*)e2)->takeDamage();
        }
    }
}

void ContactListener::EndContact(b2Contact* contact) {
}

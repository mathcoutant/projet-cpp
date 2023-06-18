#include <iostream>
#include "ContactListener.h"
#include "Player.h"
#include "Enemy.h"
#include "Grave.h"


void ContactListener::BeginContact(b2Contact *contact) {
    b2Fixture *f1 = contact->GetFixtureA();
    b2Fixture *f2 = contact->GetFixtureB();

    b2Body *b1 = f1->GetBody();
    b2Body *b2 = f2->GetBody();

    using
    enum EntityType;

    // We get the userData of the physic bodies, it's a pointer to the Entity that own the body.
    // By doing so, we can act on the entity according to what it is.
    auto e1 = (Entity *) (b1->GetUserData().pointer);
    auto e2 = (Entity *) (b2->GetUserData().pointer);
    if (e1 && e2) {
        if (e1->type == PLAYER && e2->type == ENEMY) {
            ((Player *) e1)->takeDamage();
            ((Enemy *) e2)->respawn();
        }
        if (e1->type == ENEMY && e2->type == PLAYER) {
            ((Player *) e2)->takeDamage();
            ((Enemy *) e1)->respawn();
        }
        if (e1->type == PLAYER && e2->type == GRAVE) {
            ((Player *) e1)->setGrave((Grave *) e2);
        }
        if (e1->type == GRAVE && e2->type == PLAYER) {
            ((Player *) e2)->setGrave((Grave *) e1);
        }
        if (e1->type == PLAYER && e2->type == COIN) {
            ((Player *) e1)->collectCoin((Coin *) e2);
        }
        if (e1->type == COIN && e2->type == PLAYER) {
            ((Player *) e2)->collectCoin((Coin *) e1);
        }
    }
}

void ContactListener::EndContact(b2Contact *contact) {
    b2Fixture *f1 = contact->GetFixtureA();
    b2Fixture *f2 = contact->GetFixtureB();

    b2Body *b1 = f1->GetBody();
    b2Body *b2 = f2->GetBody();

    auto e1 = (Entity *) (b1->GetUserData().pointer);
    auto e2 = (Entity *) (b2->GetUserData().pointer);

    using
    enum EntityType;
    if (e1 && e2) {
        if (e1->type == PLAYER && e2->type == GRAVE) {
            ((Player *) e1)->setGrave(nullptr);
        }
        if (e1->type == GRAVE && e2->type == PLAYER) {
            ((Player *) e2)->setGrave(nullptr);
        }
    }
}

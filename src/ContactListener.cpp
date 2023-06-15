#include "ContactListener.h"
#include "Player.h"
#include "Enemy.h"

void ContactListener::BeginContact(b2Contact* contact) {
	b2Fixture* f1 = contact->GetFixtureA();
	b2Fixture* f2 = contact->GetFixtureB();

	b2Body* b1 = f1->GetBody();
	b2Body* b2 = f2->GetBody();

	auto l1 = (Link*)b1->GetUserData().pointer;
	auto l2 = (Link*)b2->GetUserData().pointer;

	if (l1->type == 0 && l2->type == 1) {
		auto player = (Player*)l1;
		auto enemy = (Enemy*)l2;

		player->takeDamage();
	}
	else if (l2->type == 0 && l1->type == 1) {
		auto player = (Player*)l2;
		auto enemy = (Enemy*)l1;

		player->takeDamage();
	}
}

void ContactListener::EndContact(b2Contact* contact) {
}

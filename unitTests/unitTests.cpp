#include <gtest/gtest.h>
#include "Player.h"
#include "DigState.h"


TEST(StatePattern, BaseMove) {
	sf::Texture playerTexture;
	playerTexture.loadFromFile("resources/images/raider.png");
	auto player = Player(playerTexture, 0, 0);

	auto state = player.getState();
	ASSERT_EQ(typeid(MoveState), typeid(*state));
}

TEST(StatePattern, MoveToDig) {
	sf::Texture playerTexture;
	playerTexture.loadFromFile("resources/images/fantome.png");
	auto player = Player(playerTexture, 0, 0);
	auto state = player.getState();

	std::vector<std::unique_ptr<Coin>> coins;
	auto grave = Grave(playerTexture,playerTexture, playerTexture, 0, 0, coins);
	player.setGrave(&grave);
	state->handleInput(player, sf::Keyboard::Space, true);
	player.update(sf::seconds(1.f/60.f));
	state = player.getState();
	ASSERT_EQ(typeid(DigState), typeid(*state));
}

TEST(StatePattern, DigToMove) {
	sf::Texture playerTexture;
	playerTexture.loadFromFile("resources/images/fantome.png");
	auto player = Player(playerTexture, 0, 0);
	auto state = player.getState();

	std::vector<std::unique_ptr<Coin>> coins;
	auto grave = Grave(playerTexture,playerTexture,playerTexture, 0, 0, coins);
	player.setGrave(&grave);
	state->handleInput(player, sf::Keyboard::Space, true);
	player.update(sf::seconds(1.f / 60.f));
	state = player.getState();

	state->handleInput(player, sf::Keyboard::BackSpace, true);
	player.update(sf::seconds(1.f / 60.f));
	state = player.getState();

	ASSERT_EQ(typeid(MoveState), typeid(*state));
}

#include <iostream>
#include <vector>
#include <memory>

class BadGuy {
private:
	std::vector<std::shared_ptr<BadGuy>> enemies;
public:
	std::vector<std::shared_ptr<BadGuy>> getEnemies() {
		return enemies;
	}

	void addEnemy(std::shared_ptr<BadGuy> enemy) {
		enemies.push_back(enemy);
	}
};

#include "gmock/gmock.h"
#include <algorithm>



TEST(BadHorseSolver, EnemiesForPersonWithNoEnemiesIsEmpty) {
	BadGuy baddie;
	auto enemies = baddie.getEnemies();

	ASSERT_THAT(enemies.size(), testing::Eq(0));
}

TEST(BadHorseSolver, AddedEnemyIsReturnedInEnemies) {
	BadGuy baddie;
	std::shared_ptr<BadGuy> enemy;

	baddie.addEnemy(enemy);

	auto enemies = baddie.getEnemies();

	ASSERT_THAT(enemies.size(), testing::Eq(1));

	auto it = find(enemies.begin(), enemies.end(), enemy);
	if (it == enemies.end()) FAIL();
}

TEST(BadHorseSolver, AddingEnemyMoreThanOnceIsIgnored) {
	BadGuy baddie;
	std::shared_ptr<BadGuy> enemy;

	baddie.addEnemy(enemy);
	baddie.addEnemy(enemy);

	auto enemies = baddie.getEnemies();

	ASSERT_THAT(enemies.size(), testing::Eq(1));

	auto it = find(enemies.begin(), enemies.end(), enemy);
	if (it == enemies.end()) FAIL();
}

int main(int ac, char* av[])
{
	testing::InitGoogleTest(&ac, av);
	return RUN_ALL_TESTS();
}
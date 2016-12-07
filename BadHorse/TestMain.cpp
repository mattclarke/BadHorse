#include <iostream>
#include <vector>
#include <memory>
#include <set>


class BadGuy {
private:
	std::set<std::shared_ptr<BadGuy>> enemies;

public:
	static void addEnemyAndViceVersa(std::shared_ptr<BadGuy> enemy1, std::shared_ptr<BadGuy> enemy2);

	size_t getNumberEnemies() {
		return enemies.size();
	}

	void addEnemy(std::shared_ptr<BadGuy> enemy) {
		enemies.insert(enemy);
	}

	bool isEnemy(std::shared_ptr<BadGuy> enemy) {
		auto it = enemies.find(enemy);
		if (it != enemies.end()) {
			return true;
		}

		return false;
	}
};

void BadGuy::addEnemyAndViceVersa(std::shared_ptr<BadGuy> enemy1, std::shared_ptr<BadGuy> enemy2) {
	enemy1->addEnemy(enemy2);
	enemy2->addEnemy(enemy1);
}

#include "gmock/gmock.h"
#include <algorithm>


class BadGuyTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		baddie = std::make_shared<BadGuy>();
		enemy = std::make_shared<BadGuy>();
		BadGuy::addEnemyAndViceVersa(baddie, enemy);
	}

	std::shared_ptr<BadGuy> baddie;
	std::shared_ptr<BadGuy> enemy;
};


TEST(BadHorseSolver, NumberOfEnemiesForPersonWithNoEnemiesIsZero) {
	BadGuy baddie;

	ASSERT_EQ(baddie.getNumberEnemies(), 0);
}

TEST_F(BadGuyTest, AddedEnemyIsAnEnemy) {
	baddie->addEnemy(enemy);

	ASSERT_TRUE(baddie->isEnemy(enemy));
}

TEST_F(BadGuyTest, AddingEnemyMoreThanOnceIsIgnored) {
	baddie->addEnemy(enemy);

	ASSERT_EQ(baddie->getNumberEnemies(), 1);
}

TEST_F(BadGuyTest, AddingEnemyAlsoAddsMeToTheirEnemies) {
	ASSERT_TRUE(enemy->isEnemy(baddie));
}

int main(int ac, char* av[])
{
	testing::InitGoogleTest(&ac, av);
	return RUN_ALL_TESTS();
}
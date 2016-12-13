#include <vector>
#include <memory>
#include <set>
#include "BadGuy.h"


class Graph {
private:
	std::set<std::shared_ptr<BadGuy>> nodes;

public:
	int getNumberNodes() const {
		return nodes.size();
	}

	void addNode(std::shared_ptr<BadGuy> node) {
		nodes.insert(node);
	}
};

#include "gmock/gmock.h"
#include <algorithm>


class BadGuyTest : public ::testing::Test {
protected:
	virtual void SetUp() override {
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

TEST(GraphTest, EmptyGraphHasNoNodes) {
	Graph graph;
	ASSERT_EQ(graph.getNumberNodes(), 0);
}

TEST(GraphTest, AddingNodeIncreasesNodeCount) {
	Graph graph;
	std::shared_ptr<BadGuy> node = std::make_shared<BadGuy>();

	graph.addNode(node);
	ASSERT_EQ(graph.getNumberNodes(), 1);
}

int main(int ac, char* av[])
{
	testing::InitGoogleTest(&ac, av);
	return RUN_ALL_TESTS();
}
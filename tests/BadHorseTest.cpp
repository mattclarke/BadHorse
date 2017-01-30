#include <vector>
#include <memory>
#include <map>
#include "BadGuy.h"


class Graph {
private:
	std::map<std::string, std::shared_ptr<BadGuy>> nodes;

public:
	int getNumberNodes() const {
		return nodes.size();
	}

	void addPairing(std::string name, std::string enemy) {
		std::shared_ptr<BadGuy> node1 = std::make_shared<BadGuy>(name);
		std::shared_ptr<BadGuy> node2 = std::make_shared<BadGuy>(enemy);
		nodes[name] = node1;
		nodes[enemy] = node2;
		BadGuy::addEnemyAndViceVersa(node1, node2);
	}

	std::shared_ptr<BadGuy> getNodeByName(std::string name) {
		return nodes[name];
	}
};

#include "gmock/gmock.h"
#include <algorithm>


class BadGuyTest : public ::testing::Test {
protected:
	virtual void SetUp() override {
		baddie = std::make_shared<BadGuy>("Baddie");
		enemy = std::make_shared<BadGuy>("Enemy");
		BadGuy::addEnemyAndViceVersa(baddie, enemy);
	}

	std::shared_ptr<BadGuy> baddie;
	std::shared_ptr<BadGuy> enemy;
};


TEST(BadHorseSolver, NumberOfEnemiesForPersonWithNoEnemiesIsZero) {
	BadGuy baddie("Dave");

	ASSERT_EQ(baddie.getNumberEnemies(), 0);
}

TEST(BadHorseSolver, GettingNameReturnsName) {
	BadGuy baddie("Dave");

	ASSERT_EQ(baddie.getName(), "Dave");
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

TEST(GraphTest, AddingEnemyPairGivesNodeCountOfTwo) {
	Graph graph;

	graph.addPairing("Baddie", "Enemy");
	ASSERT_EQ(graph.getNumberNodes(), 2);
}

TEST(GraphTest, CanGetNodeNyName) {
	Graph graph;

	graph.addPairing("Baddie", "Enemy");
	ASSERT_EQ(graph.getNodeByName("Baddie")->getName(), "Baddie");
}

TEST(GraphTest, AddingEnemyPairGivesNodeWithOneEnemy) {
	Graph graph;

	graph.addPairing("Baddie", "Enemy");
	ASSERT_EQ(graph.getNodeByName("Baddie")->getNumberEnemies(), 1);
}

TEST(GraphTest, ForTwoPairsOfEnemiesGivesNodeCountOfFour) {
	Graph graph;
	graph.addPairing("Baddie", "Enemy");
	graph.addPairing("Naughty", "Nemesis");

	ASSERT_EQ(graph.getNumberNodes(), 4);
}

TEST(GraphTest, ForTwoPairsOfEnemiesWithOneSharedEnemyGivesNodeCountOfThree) {
	Graph graph;
	graph.addPairing("Baddie", "Enemy");
	graph.addPairing("Baddie", "Nemesis");

	ASSERT_EQ(graph.getNumberNodes(), 3);
}

TEST(GraphTest, ForTwoPairsOfEnemiesWithOneSharedEnemyTheSharedEnemyHasTwoEnemies) {
	Graph graph;
	graph.addPairing("Baddie", "Enemy");
	graph.addPairing("Baddie", "Nemesis");

	ASSERT_EQ(graph.getNodeByName("Baddie")->getNumberEnemies(), 2);
}

int main(int ac, char* av[])
{
	testing::InitGoogleTest(&ac, av);
	return RUN_ALL_TESTS();
}
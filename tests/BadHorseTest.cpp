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
		if (nodes.count(name) == 0) {
			std::shared_ptr<BadGuy> node1 = std::make_shared<BadGuy>(name);
			nodes[name] = node1;
		}
		if (nodes.count(enemy) == 0) {
			std::shared_ptr<BadGuy> node2 = std::make_shared<BadGuy>(enemy);
			nodes[enemy] = node2;
		}
		BadGuy::addEnemyAndViceVersa(nodes[name], nodes[enemy]);
	}

	std::shared_ptr<BadGuy> getNodeByName(std::string name) {
		return nodes[name];
	}

	void solve() {
		Colour first = red;

		for (auto const& n : nodes) {
			// Might as well start from the first node whatever it is
			if (n.second->getColour() == none) {
				n.second->setColour(first);

				if (first == red) {
					first = black;
				}
				else {
					first = red;
				}

				for (auto const& e : n.second->getEnemies()) {
					if (e->getColour() == none) {
						e->setColour(first);
					}
				}
			}
		}
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

TEST(BadHorseSolver, GettingColourWhenNotSetReturnsNone) {
	BadGuy baddie("Dave");

	ASSERT_EQ(baddie.getColour(), none);
}

TEST(BadHorseSolver, AfterSettingColourGettingColourReturnsSetValue) {
	BadGuy baddie("Dave");
	baddie.setColour(red);

	ASSERT_EQ(baddie.getColour(), red);
}

TEST_F(BadGuyTest, AddedEnemyIsAnEnemy) {
	baddie->addEnemy(enemy);

	ASSERT_TRUE(baddie->isEnemy(enemy));
}

TEST_F(BadGuyTest, AddingEnemyMoreThanOnceIsIgnored) {
	baddie->addEnemy(enemy);

	ASSERT_EQ(baddie->getNumberEnemies(), 1);
}

TEST_F(BadGuyTest, CanAccessEnemiesCollection) {
	baddie->addEnemy(enemy);

	auto enemies = baddie->getEnemies();

	// Get first (and, in this case only) enemy
	for (auto e : enemies) {
		ASSERT_EQ(e->getName(), enemy->getName());
	}
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

TEST(GraphTest, ForEnemyPairSolvingSetsColours) {
	Graph graph;

	graph.addPairing("Baddie", "Enemy");
	graph.solve();

	ASSERT_NE(graph.getNodeByName("Baddie")->getColour(), none);
	ASSERT_NE(graph.getNodeByName("Enemy")->getColour(), none);
}

TEST(GraphTest, ForEnemyPairSolvingSetsDifferentColours) {
	Graph graph;

	graph.addPairing("Baddie", "Enemy");
	graph.solve();

	ASSERT_EQ(graph.getNodeByName("Baddie")->getColour(), red);
	ASSERT_EQ(graph.getNodeByName("Enemy")->getColour(), black);
}

TEST(GraphTest, ForTwoPairsOfEnemiesWithOneSharedEnemyThenSharedEnemyIsDifferentColour) {
	Graph graph;
	graph.addPairing("Baddie", "Enemy");
	graph.addPairing("Baddie", "Nemesis");
	graph.solve();

	Colour shared = graph.getNodeByName("Baddie")->getColour();

	ASSERT_NE(graph.getNodeByName("Enemy")->getColour(), shared);
	ASSERT_NE(graph.getNodeByName("Nemesis")->getColour(), shared);
}

TEST(GraphTest, ForChainedEnemiesTheyAlternateColours) {
	Graph graph;
	graph.addPairing("Baddie", "Enemy");
	graph.addPairing("Enemy", "Nemesis");
	graph.solve();

	ASSERT_NE(graph.getNodeByName("Baddie")->getColour(), graph.getNodeByName("Enemy")->getColour());
	ASSERT_NE(graph.getNodeByName("Enemy")->getColour(), graph.getNodeByName("Nemesis")->getColour());
}

int main(int ac, char* av[])
{
	testing::InitGoogleTest(&ac, av);
	return RUN_ALL_TESTS();
}
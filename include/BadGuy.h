#pragma once

#include <vector>
#include <memory>
#include <set>


class BadGuy {
private:
	std::set<std::shared_ptr<BadGuy>> enemies;
	std::string name;

public:
	static void addEnemyAndViceVersa(std::shared_ptr<BadGuy> enemy1, std::shared_ptr<BadGuy> enemy2);

	BadGuy(std::string name) : name(name) {

	}

	std::string getName() {
		return name;
	}

	size_t getNumberEnemies() const {
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

inline void BadGuy::addEnemyAndViceVersa(std::shared_ptr<BadGuy> enemy1, std::shared_ptr<BadGuy> enemy2) {
	enemy1->addEnemy(enemy2);
	enemy2->addEnemy(enemy1);
}

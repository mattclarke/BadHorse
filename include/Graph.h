#pragma once

#include <vector>
#include <memory>
#include <map>
#include "BadGuy.h"

class Graph {
private:
	std::map<std::string, std::shared_ptr<BadGuy>> nodes;

	Colour switchColour(Colour colour) {
		if (colour == Colour::RED) {
			return Colour::BLACK;
		}
		else {
			return Colour::RED;
		}
	}

	bool colourConnections(std::shared_ptr<BadGuy> node, Colour colour) {
		for (auto const& e : node->getEnemies()) {
			if (e->getColour() == Colour::NONE) {
				e->setColour(colour);
				if (!colourConnections(e, switchColour(colour))) {
					return false;
				}
			}
			else if (e->getColour() != colour) {
				// We have a mismatch so the problem cannot be solved
				return false;
			}
		}

		return true;
	}

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

	bool canBeSolved() {
		Colour first = Colour::RED;

		for (auto const& n : nodes) {
			// Might as well start from the first node whatever it is
			// Only do a node if it has no colour - that means it hasn't be picked up by the recursion
			if (n.second->getColour() == Colour::NONE) {
				n.second->setColour(first);

				first = switchColour(first);

				// Start recusion
				if (!colourConnections(n.second, first)) {
					return false;
				}
			}
		}

		return true;
	}
};

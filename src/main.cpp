#include <fstream>
#include <sstream>
#include <iostream>
#include "Graph.h"

int main(int argc, char *argv[]) {
	std::ifstream infile(argv[1]);

	std::string line;

	// Get total number of sets
	std::getline(infile, line);
	std::istringstream iss(line);
	int totalSets;
	iss >> totalSets;
	
	int count = 0;

	while (std::getline(infile, line)) {
		// Get number of pairs
		std::istringstream iss(line);
		int numberPairs;
		iss >> numberPairs;

		// Construct the graph
		Graph graph;
		
		for (int i = 0; i < numberPairs; ++i) {
			std::getline(infile, line);
			std::istringstream iss(line);
			std::string first, second;
			iss >> first >> second;
			graph.addPairing(first, second);
		}

		// See if it is solvable
		if (graph.canBeSolved()) {
			std::cout << "Case #" << ++count << ": Yes" << std::endl;
		}
		else {
			std::cout << "Case #" << ++count << ": No" << std::endl;
		}
	}
}

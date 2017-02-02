#include <fstream>
#include <sstream>
#include <iostream>
#include "Graph.h"

int main() {
	std::ifstream infile("A-small-practice-1.in");

	std::string line;

	// Get total number of sets
	std::getline(infile, line);
	std::istringstream iss(line);
	int total_sets;
	iss >> total_sets;
	
	int count = 0;


	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		int numberPairs;
		iss >> numberPairs;

		//std::cout << "Number pairs: " << numberPairs << std::endl;
		Graph graph;
		
		for (int i = 0; i < numberPairs; ++i) {
			std::getline(infile, line);
			std::istringstream iss(line);
			std::string first, second;
			iss >> first >> second;
			graph.addPairing(first, second);
		}
		if (graph.canBeSolved()) {
			std::cout << "Case #" << ++count << ": Yes" << std::endl;
		}
		else {
			std::cout << "Case #" << ++count << ": No" << std::endl;
		}
	}

}
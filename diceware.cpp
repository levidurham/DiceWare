#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstdlib>
#include <fstream>
#include <random>
#include <string>
#include <vector>

int main(int argc, char* argv[]){
	int numWords = 0;
	std::vector<std::string> wordList;
	std::ifstream listFile("efflist.txt");

	if (argc != 2){
		std::cerr << "Usage: " << argv[0] << " NUM" << std::endl;
		return 1;
	}

	numWords = std::atoi(argv[1]);

	if(numWords < 0){
		std::cerr << "Usage: " << argv[0] << " NUM" << std::endl;
		return 1;
	}

	if(!listFile){
		std::cerr << "Error opening input file." << std::endl;
		return -1;
	}

	std::copy(std::istream_iterator<std::string>(listFile),
		  std::istream_iterator<std::string>(),
		  back_inserter(wordList));

	std::random_device rd;
	for(int i = 0; i < numWords; ++i)
		std::cout << wordList[(rd() % wordList.size())] << " ";
	std::cout << std::endl;

	return 0;
}


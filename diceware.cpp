#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <sodium.h>

#if defined(__linux__)
	#include <fcntl.h>
	#include <unistd.h>
	#include <sys/ioctl.h>
	#include <linux/random.h>
#endif

int main(int argc, char* argv[]){
	int numWords = 0;
	std::vector<std::string> wordList;
	std::ifstream listFile("eff_large_wordlist.txt");
	int listSize;

	// Exit if not exactly one argument
	if (argc != 2){
		std::cerr << "Usage: " << argv[0] << " NUM" << std::endl;
		return 1;
	}

	numWords = std::atoi(argv[1]);

	// Exit if argument isn't a positive integer
	if(numWords < 0){
		std::cerr << "Usage: " << argv[0] << " NUM" << std::endl;
		return 1;
	}

	// Test to ensure enough entropy has been collected
	// to seed the random number generator under Linux
	#if defined(__linux__) && defined(RNDGETENTCNT)
	int fd;
	int c;

	if ((fd = open("/dev/random", O_RDONLY)) != -1) {
    		if (ioctl(fd, RNDGETENTCNT, &c) == 0 && c < 160) {
			fputs("This system doesn't provide enough entropy to "
			      "quickly generate high-quality random numbers.\n"
			      "Installing the rng-utils/rng-tools or haveged "
			      "packages may help.\nOn virtualized Linux"
			      "environments, also consider using virtio-rng.\n"
			      "The service will not start until enough entropy"
			      "has been collected.\n", stderr);
		}
		(void) close(fd);
    	}
	#endif
	// Exit if sodium fails to initialize
	if (sodium_init() == -1) {
		std::cerr << "Failed to initialize RNG." << std::endl;
		return 1;
	}

	// Exit if we can't open the input file
	if(!listFile){
		std::cerr << "Error opening input file." << std::endl;
		return -1;
	}

	// Copy word list into a vector. This provides no error checking,
	// assumes a well formed file.
	std::copy_if(std::istream_iterator<std::string>(listFile),
		     std::istream_iterator<std::string>(),
		     back_inserter(wordList),
		     [](__attribute__((__unused__)) std::string s){
			     static bool state = true; return state=!state;
		     });

	// Prints the requested number of words at random form the vector.
	listSize = wordList.size();
	for(int i = 0; i < numWords; ++i)
		std::cout << wordList[randombytes_uniform(listSize)] << " ";
	std::cout << std::endl;

	return 0;
}


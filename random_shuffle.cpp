#include <iostream>
#include <numeric>
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <algorithm>    // std::random_shuffle
#include "uint40.hpp"

constexpr uint64_t MAX_LENGTH = 1ULL<<40;

static_assert(sizeof(uint40) == 5, "assume that uint40 needs 5 bytes.");
int main(const int argc, const char *const argv[]) {
	if(argc < 3) {
		fprintf(stderr, "Usage: %s length seed\n", argv[0]);
		return 1;
	}
	const uint64_t length = strtoul(argv[1], NULL, 10);
	if(length == 0 || length > MAX_LENGTH) {
		fprintf(stderr, "Length = %lu should be less than %lu\n", length, MAX_LENGTH);
		return 1;
	}
	const uint64_t seed = strtoul(argv[2], NULL, 10);
	srand(seed);
	uint40* arr = new uint40[length];
	std::iota(arr, arr+length, 0);
	std::random_shuffle(arr, arr+length);
	fwrite(arr, sizeof(uint40), length, stdout);
	delete [] arr;
	return 0;
}

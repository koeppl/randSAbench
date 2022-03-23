#include <iostream>
using namespace std;

int main() {
	uint64_t buf;
	while(true) {
		const size_t ret = fread(&buf, 5, 1, stdin);
		if(ret != 1) { break; }
		cout << buf << std::endl;
	}
	return 0;
}

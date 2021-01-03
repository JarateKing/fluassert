#include <iostream>

// use the `handleAsserts` method to print
// by default it's `std::cerr << (x) << '\n';
#define FLUASSERT_HANDLER(x) handleAsserts(x);
std::string handleAsserts(std::string s) {
	std::cerr << "handling " << s << '\n';
}
#include "../src/fluassert.h"

int main() {
	int testVariable = 1;
	fluassert(testVariable, should.be, 2);
}

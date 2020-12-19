#include "../src/fluassert.h"

int main() {
	int testVariable = 1;
	fluassert(testVariable, should.be, 2);
}

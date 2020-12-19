#include "../src/fluassert.h"

int main() {
	int testValue = 1;
	
	// can directly test a value
	fluassert(testValue, should.be, 1);
	
	// can assert an arbitrary boolean expression
	fluassert((testValue == 1), should.be, true);
	
	// can assert other properties
	fluassert(testValue, should.be_between, -100, 100);
	
	// can chain not
	fluassert(testValue, should.Not.be, 0);
	fluassert(testValue, should.Not.be, 2);
}
#define FLUASSERT_NOABORT
#include "../src/fluassert.h"

int main() {
	int testVariable = 1;
	fluassert(testVariable, should.be, 2);
	
	char testChar = 'a';
	fluassert(testChar, should.be, 'b');
	
	std::string testStr = "a";
	fluassert(testStr, should.be, "b");
	fluassert("a", should.Not.be, "a");
	
	fluassert(5, should.be_lesser_than, 3);
	fluassert(5, should.be_greater_than, 6);
}

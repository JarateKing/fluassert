#include "../src/fluassert.h"

bool should_match_keyword(std::string value) {
	return value == "hello";
}

int main() {
	std::string testVariable = "hello";
	fluassert(testVariable, should_match_keyword);
}

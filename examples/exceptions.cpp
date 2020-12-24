#define FLUASSERT_NOABORT
#include "../src/fluassert.h"

int main() {
	// zero-argument function
	auto lambda = [](){ throw "exception"; };
	fluassert(lambda, should.throw_error);
	
	// multiple-argument function, wrapped in a lambda
	auto lambda2 = [](std::vector<int> a, int b){ return a.at(b); };
	std::vector<int> arr(0);
	fluassert([&](){ return lambda2(arr, 100); }, should.throw_error);
}
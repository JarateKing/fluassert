#define FLUASSERT_NOABORT
#include "../src/fluassert.h"

int main() {
	// zero-argument lambda
	auto lambda = [](){ throw "exception"; };
	fluassert(lambda, should.throw_error);
	
	// zero-argument lambda directly inside fluassert
	fluassert([](){ throw "exception"; }, should.throw_error);
	
	// multiple-argument lambda, wrapped in a zero-argument lambda
	std::vector<int> arr(0);
	auto lambda2 = [](std::vector<int> a, int b){ return a.at(b); };
	fluassert([&](){ return lambda2(arr, 100); }, should.throw_error);
}

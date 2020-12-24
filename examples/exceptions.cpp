#include "../src/fluassert.h"

int main() {
	auto lambda = [](){ throw "exception"; };
	fluassert(lambda, should.Not.throw_error);
}
#include <iostream>
#include <algorithm>

#ifndef NDEBUG
#define fluassert(v,f,...) Fluassert::_test(__LINE__,__FILE__,__FUNCTION__,#v,#f,#__VA_ARGS__,v,f(v,__VA_ARGS__))
#define should Fluassert::Should(0)
#define Not _not()
#else
#define fluassert(v,f,...) ((void)0)
#endif

namespace Fluassert {
	void _testfail(int line, std::string file, std::string func, std::string assertv, std::string assertf, std::string assertc, std::string valprefix, auto v, std::string valpostfix) {
		std::string formatted = assertf;
		for (int i = 0; i < formatted.size(); i++) {
			if (formatted[i] == '.' || formatted[i] == '_') formatted[i] = ' ';
			if (formatted[i] >= 'A' && formatted[i] <= 'Z') formatted[i] += 'a' - 'A';
		}
		std::string assertion = assertv + " " + formatted + " " + assertc;
		std::string toprint = "FLUASSERT| " + file + "'s " + func + " (line " + std::to_string(line) + "): " + assertion;
		std::cerr << toprint;
		if (valprefix.size() > 0) std::cerr << valprefix << v << valpostfix;
		std::cerr << '\n';

#ifndef FLUASSERT_NOABORT
		std::abort();
#endif
	}

	void _test(int line, std::string file, std::string func, std::string assertv, std::string assertf, std::string assertc, auto v, bool f) {
		if (!f) _testfail(line, file, func, assertv, assertf, assertc, "", v, "");
	}
	void _test(int line, std::string file, std::string func, std::string assertv, std::string assertf, std::string assertc, int v, bool f) {
		if (!f) _testfail(line, file, func, assertv, assertf, assertc, " - but is ", v, "");
	}
	void _test(int line, std::string file, std::string func, std::string assertv, std::string assertf, std::string assertc, long v, bool f) {
		if (!f) _testfail(line, file, func, assertv, assertf, assertc, " - but is ", v, "");
	}
	void _test(int line, std::string file, std::string func, std::string assertv, std::string assertf, std::string assertc, long long v, bool f) {
		if (!f) _testfail(line, file, func, assertv, assertf, assertc, " - but is ", v, "");
	}
	void _test(int line, std::string file, std::string func, std::string assertv, std::string assertf, std::string assertc, float v, bool f) {
		if (!f) _testfail(line, file, func, assertv, assertf, assertc, " - but is ", v, "");
	}
	void _test(int line, std::string file, std::string func, std::string assertv, std::string assertf, std::string assertc, double v, bool f) {
		if (!f) _testfail(line, file, func, assertv, assertf, assertc, " - but is ", v, "");
	}
	void _test(int line, std::string file, std::string func, std::string assertv, std::string assertf, std::string assertc, char v, bool f) {
		if (!f) _testfail(line, file, func, assertv, assertf, assertc, " - but is '", v, "'");
	}
	void _test(int line, std::string file, std::string func, std::string assertv, std::string assertf, std::string assertc, std::string v, bool f) {
		if (!f) _testfail(line, file, func, assertv, assertf, assertc, " - but is \"", v, "\"");
	}
	void _test(int line, std::string file, std::string func, std::string assertv, std::string assertf, std::string assertc, const char* v, bool f) {
		if (!f) _testfail(line, file, func, assertv, assertf, assertc, " - but is \"", v, "\"");
	}

	struct Should {
		bool inverted;
		Should(bool invert) : inverted(invert) {}
		bool be(auto v, auto c) {
			return inverted ^ (v == c);
		}
		bool be_between(auto v, auto c1, auto c2) {
			if (c1 > c2) std::swap(c1, c2);
			return inverted ^ (c1 <= v && v <= c2);
		}
		Should _not() {
			return Should(!inverted);
		}
	};
}

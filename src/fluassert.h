#include <iostream>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <set>
#include <unordered_set>
#include <map>
#include <vector>

#ifndef NDEBUG
#define fluassert(v,f,...) Fluassert::_test(__LINE__,__FILE__,__FUNCTION__,#v,#f,#__VA_ARGS__,v,f(v,__VA_ARGS__))
#define should Fluassert::Should(0)
#define Not _not()
#else
#define fluassert(v,f,...) ((void)0)
#endif

#ifndef FLUASSERT_HANDLER
#define FLUASSERT_HANDLER(x) std::cerr << (x) << '\n';
#endif

namespace Fluassert {
	void _testfail(int line, std::string file, std::string func, std::string assertv, std::string assertf, std::string assertc, std::string post) {
		std::string formatted = assertf;
		for (int i = 0; i < formatted.size(); i++) {
			if (formatted[i] == '.' || formatted[i] == '_') formatted[i] = ' ';
			if (formatted[i] >= 'A' && formatted[i] <= 'Z') formatted[i] += 'a' - 'A';
		}
		
		std::string assertion = assertv + " " + formatted + " " + assertc;
		std::stringstream toprint;
		toprint << "FLUASSERT| " << file << "'s " << func << " (line " << line << "): " << assertion << post;
		
		FLUASSERT_HANDLER(toprint.str());

#ifndef FLUASSERT_NOABORT
		std::abort();
#endif
	}
	
	std::string _testfailpost(std::string pre, auto v, std::string post) {
		std::stringstream toprint;
		toprint << pre << v << post;
		return toprint.str();
	}

	void _test(int line, std::string file, std::string func, std::string assertv, std::string assertf, std::string assertc, auto v, bool f) {
		if (!f) _testfail(line, file, func, assertv, assertf, assertc, "");
	}
	void _test(int line, std::string file, std::string func, std::string assertv, std::string assertf, std::string assertc, int v, bool f) {
		if (!f) _testfail(line, file, func, assertv, assertf, assertc, _testfailpost(" - but is ", v, ""));
	}
	void _test(int line, std::string file, std::string func, std::string assertv, std::string assertf, std::string assertc, long v, bool f) {
		if (!f) _testfail(line, file, func, assertv, assertf, assertc, _testfailpost(" - but is ", v, ""));
	}
	void _test(int line, std::string file, std::string func, std::string assertv, std::string assertf, std::string assertc, long long v, bool f) {
		if (!f) _testfail(line, file, func, assertv, assertf, assertc, _testfailpost(" - but is ", v, ""));
	}
	void _test(int line, std::string file, std::string func, std::string assertv, std::string assertf, std::string assertc, float v, bool f) {
		if (!f) _testfail(line, file, func, assertv, assertf, assertc, _testfailpost(" - but is ", v, ""));
	}
	void _test(int line, std::string file, std::string func, std::string assertv, std::string assertf, std::string assertc, double v, bool f) {
		if (!f) _testfail(line, file, func, assertv, assertf, assertc, _testfailpost(" - but is ", v, ""));
	}
	void _test(int line, std::string file, std::string func, std::string assertv, std::string assertf, std::string assertc, char v, bool f) {
		if (!f) _testfail(line, file, func, assertv, assertf, assertc, _testfailpost(" - but is '", v, "'"));
	}
	void _test(int line, std::string file, std::string func, std::string assertv, std::string assertf, std::string assertc, std::string v, bool f) {
		if (!f) _testfail(line, file, func, assertv, assertf, assertc, _testfailpost(" - but is \"", v, "\""));
	}
	void _test(int line, std::string file, std::string func, std::string assertv, std::string assertf, std::string assertc, const char* v, bool f) {
		if (!f) _testfail(line, file, func, assertv, assertf, assertc, _testfailpost(" - but is \"", v, "\""));
	}

	struct Should {
		bool inverted;
		Should(bool invert) : inverted(invert) {}
		bool be(auto v, auto c) {
			return inverted ^ (v == c);
		}
		bool be_greater_than(auto v, auto c) {
			return inverted ^ (v > c);
		}
		bool be_lesser_than(auto v, auto c) {
			return inverted ^ (v < c);
		}
		bool be_greater_or_equal_to(auto v, auto c) {
			return inverted ^ (v >= c);
		}
		bool be_lesser_or_equal_to(auto v, auto c) {
			return inverted ^ (v <= c);
		}
		bool be_between(auto v, auto c1, auto c2) {
			if (c1 > c2) std::swap(c1, c2);
			return inverted ^ (c1 <= v && v <= c2);
		}
		bool be_between(std::string v, const char* c1, const char* c2) {
			int cmp1 = strcmp(v.c_str(), c1), cmp2 = strcmp(v.c_str(), c2);
			return inverted ^ (cmp1 == 0 || cmp1 != cmp2);
		}
		bool be_between(const char* v, const char* c1, const char* c2) {
			int cmp1 = strcmp(v, c1), cmp2 = strcmp(v, c2);
			return inverted ^ (cmp1 == 0 || cmp1 != cmp2);
		}
		bool contain(std::set<auto> v, auto c) {
			return inverted ^ (v.count(c) != 0);
		}
		bool contain(std::unordered_set<auto> v, auto c) {
			return inverted ^ (v.count(c) != 0);
		}
		bool contain(std::map<auto, auto> v, auto c) {
			return inverted ^ (v.count(c) != 0);
		}
		bool contain_key(std::map<auto, auto> v, auto c) {
			return inverted ^ (v.count(c) != 0);
		}
		bool contain_value(std::map<auto, auto> v, auto c) {
			for (auto e : v)
				if (e.second == c)
					return !inverted;
			return inverted;
		}
		bool contain(std::vector<auto> v, auto c) {
			for (auto e : v)
				if (e == c)
					return !inverted;
			return inverted;
		}
		bool contain(std::string v, auto c) {
			return inverted ^ (v.find(c) != std::string::npos);
		}
		Should _not() {
			return Should(!inverted);
		}
	};
}

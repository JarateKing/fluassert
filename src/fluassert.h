#include <iostream>
#include <algorithm>

#define fluassert(v,f,...) _test(__LINE__,__FILE__,__FUNCTION__,#v,#f,#__VA_ARGS__,v,f(v,__VA_ARGS__))
#define should Should(0)
#define Not _not()

std::string _testfail(int line, std::string file, std::string func, std::string assertv, std::string assertf, std::string assertc) {
    for (int i = 0; i < assertf.size(); i++) {
        if (assertf[i] == '.' || assertf[i] == '_') assertf[i] = ' ';
        if (assertf[i] >= 'A' && assertf[i] <= 'Z') assertf[i] += 'a' - 'A';
    }
    std::string assertion = assertv + " " + assertf + " " + assertc;
    return "FLUASSERT| " + file + "'s " + func + " (line " + std::to_string(line) + "): " + assertion;
}

void _test(int line, std::string file, std::string func, std::string assertv, std::string assertf, std::string assertc, auto v, bool f) {
    if (!f) std::cerr << _testfail(line, file, func, assertv, assertf, assertc) << '\n';
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

# Fluassert

This is a header-only assertions library for C++. The intention is provide more general assertions that offer multiple improvements over the standard asserts. These include improved debug information where applicable, greater customization options, greater readability, and a collection of functions to utilize with assertions.

## Usage

Including the header file via `#include "fluassert.h"` should be sufficient in order to make use of fluasserts. For example:

```cpp
#include "fluassert.h"

int main() {
	int x = 1;
	fluassert(x, should.be, 0);
}
```
Outputs: `FLUASSERT| example.cpp's main (line 5): x should be 0 - but is 1` before exiting the program early.

### Optional Defines

* `NDEBUG` can be defined in order to disable fluasserts
* `FLUASSERT_NOABORT` can be defined in order to continue program execution after a fluassert fails
* `FLUASSERT_HANDLER(x)` can be defined to determine how fluasserts are printed. By default this is `std::cerr << (x) << '\n';`
* `FLUASSERT_PRESERVE_ASSERT` can be defined in order to allow usage of `assert.h` alongside fluassert. Only matters when `assert.h` is included before `fluassert.h`, to avoid redefining the `assert(x)` macro.

### Conditionals

* `x should.be y` -- checks if `x == y`
* `x should.be_greater_than y` -- checks if `x > y`
* `x should.be_lesser_than y` -- checks if `x < y`
* `x should.be_greater_or_equal_to y` -- checks if `x >= y`
* `x should.be_lesser_or_equal_to y` -- checks if `x <= y`
* `x should.be_between y, z` -- checks if `y <= x <= z` or `z <= x <= y`
* `x should.be_positive` -- checks if `x > 0`
* `x should.be_negative` -- checks if `x < 0`
* `x should.contain y` -- checks that `x`, as a container (`std::set`, `std::unordered_set`, `std::map`, `std::unordered_map`, `std::vector`, `std::string`) contains `y` as a value
* `x should.contain_key y` -- for `std::map` and `std::unordered_map`, does the same as `should.contain`
* `x should.contain_value y` -- for `std::map` and `std::unordered_map`, checks if the value exists within the map
* `x should.begin_with y` -- for `std::string`, checks if `x` begins with the character or string `y`
* `x should.end_with y` -- for `std::string`, checks if `x` ends with the character or string `y`
* `x should.match_regex y` -- for `std::string`, checks if `x` fully matches the regular expression `y`
* `x should.contain_regex y` -- for `std::string`, checks if `x` has a substring (potentially the full string) that matches the regular expression `y`
* x should.throw_error` -- for a zero-argument function or lambda `x`, check if an exception gets thrown
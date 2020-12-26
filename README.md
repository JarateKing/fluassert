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

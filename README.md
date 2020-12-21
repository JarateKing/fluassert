# Fluassert

Header-only better assertions for C++.

## Usage

Including the header file via `#include "fluassert.h"` should be sufficient in order to make use of fluasserts. For example:

```cpp
#include "fluassert.h"

int main() {
	fluassert(1, should.be, 1);
}
```

### Optional Defines

* `NDEBUG` can be defined in order to disable fluasserts
* `FLUASSERT_NOABORT` can be defined in order to continue program execution after a fluassert fails
* `FLUASSERT_HANDLER(x)` can be defined to determine how fluasserts are printed. By default this is `std::cerr << (x) << '\n';`

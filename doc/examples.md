# Examples

## Basic

We can create simple fluasserts with a variety of methods.

```cpp
#include "../src/fluassert.h"

int main() {
	int testValue = 1;
	
	// can directly test a value
	fluassert(testValue, should.be, 1);
	
	// can assert an arbitrary boolean expression
	fluassert((testValue == 1), should.be, true);
	
	// can assert other properties
	fluassert(testValue, should.be_between, -100, 100);
	
	// can chain not
	fluassert(testValue, should.Not.be, 0);
	fluassert(testValue, should.Not.be, 2);
	
	// can do more complicated checks
	std::vector<int> stuff = {1, 2, 3, 4, 5, 6};
	fluassert(stuff, should.contain, 1);
}
```

The above code will pass fine without any problems (and by extension, produce no output), since all the fluasserts are true. An example of failing would look like:

```cpp
#include "../src/fluassert.h"

int main() {
	int testVariable = 1;
	fluassert(testVariable, should.be, 2);
	
	std::cout << "This code is unreachable\n";
}
```

Which would output to stderr:

```
FLUASSERT| ../examples/fail.cpp's main (line 5): testVariable should be 2 - but is 1
```

## Advanced

There are several additional options and capabilities of fluassert that should be mentioned, many of them beyond what standard asserts can supply.

### Disable

Much like with the traditional `assert.h` asserts, the `NDEBUG` define will disable all fluasserts:

```cpp
#define NDEBUG
#include "../src/fluassert.h"

int main() {
	int testVariable = 1;
	fluassert(testVariable, should.be, 2);
}
```

Because the fluassert was disabled via `NDEBUG`, this program produces no output. This also removes the code from the compiled binary entirely, much like traditional asserts, so there should be no penalty to using fluasserts when using `NDEBUG`.

### Continue Running After Failure

By default, the program will exit early when an assert fails. This behaviour can be disabled with the `FLUASSERT_NOABORT` define, like so:

```cpp
#define FLUASSERT_NOABORT
#include "../src/fluassert.h"

int main() {
	int testVariable = 1;
	fluassert(testVariable, should.be, 2);
	
	char testChar = 'a';
	fluassert(testChar, should.be, 'b');
	
	std::string testStr = "a";
	fluassert(testStr, should.be, "b");
	fluassert("a", should.Not.be, "a");
	
	fluassert(5, should.be_lesser_than, 3);
	fluassert(5, should.be_greater_than, 6);
}
```

```
FLUASSERT| ../examples/fail_multiple.cpp's main (line 6): testVariable should be 2 - but is 1
FLUASSERT| ../examples/fail_multiple.cpp's main (line 9): testChar should be 'b' - but is 'a'
FLUASSERT| ../examples/fail_multiple.cpp's main (line 12): testStr should be "b" - but is "a"
FLUASSERT| ../examples/fail_multiple.cpp's main (line 13): "a" should not be "a" - but is "a"
FLUASSERT| ../examples/fail_multiple.cpp's main (line 15): 5 should be lesser than 3 - but is 5
FLUASSERT| ../examples/fail_multiple.cpp's main (line 16): 5 should be greater than 6 - but is 5
```

### Custom Output

By changing the define `FLUASSERT_HANDLER(x)` where `x` is the fluassert fail message as a string, we can intercept and/or modify how the fluassert fail message is printed.

```cpp
#include <iostream>

// use the `handleAsserts` method to print
// by default it's `std::cerr << (x) << '\n';
#define FLUASSERT_HANDLER(x) handleAsserts(x);
std::string handleAsserts(std::string s) {
	std::cerr << "handling " << s << '\n';
}
#include "../src/fluassert.h"

int main() {
	int testVariable = 1;
	fluassert(testVariable, should.be, 2);
}
```

```
handling FLUASSERT| ../examples/custom_handler.cpp's main (line 13): testVariable should be 2 - but is 1
```

### Compatibility with assert.h

By default, `assert()` calls are defined by including `fluassert.h`. This is incompatible with the default `assert.h` defines:

```cpp
#define FLUASSERT_NOABORT
#include "../src/fluassert.h"

int main() {
	fluassert((1 == 0), should.be, true);
	assert(1 == 0);
}
```

```
FLUASSERT| ../examples/without_assert.cpp's main (line 5): (1 == 0) should be true
FLUASSERT| ../examples/without_assert.cpp's main (line 6): (1 == 0) should be true
```

However, it is possible to use both simultaneously via usage of `FLUASSERT_PRESERVE_ASSERT`

```cpp
#include <assert.h>

#define FLUASSERT_PRESERVE_ASSERT
#define FLUASSERT_NOABORT
#include "../src/fluassert.h"

int main() {
	fluassert((1 == 0), should.be, true);
	assert(1 == 0);
}
```

```
FLUASSERT| ../examples/with_assert.cpp's main (line 8): (1 == 0) should be true
Assertion failed!
Program: C:\programming\fluassert\doc\a.exe
File: ../examples/with_assert.cpp, Line 9
Expression: 1 == 0
```


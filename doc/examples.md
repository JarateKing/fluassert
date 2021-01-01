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

The above code will pass fine without any problems, since all the fluasserts are true. An example of failing would look like:

```cpp
#include "../src/fluassert.h"

int main() {
	int testVariable = 1;
	fluassert(testVariable, should.be, 2);
	
	std::cout << "This code is unreachable\n";
}
```

Which would output:

```
FLUASSERT| ../examples/fail.cpp's main (line 5): testVariable should be 2 - but is 1
```

## Advanced

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

Because the fluassert was disabled via `NDEBUG`, this program produces no output.

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


# Examples

## Basic

We can create simple fluasserts with a variety of methods.

```python
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

```python
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

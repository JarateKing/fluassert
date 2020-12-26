#include <assert.h>

#define FLUASSERT_PRESERVE_ASSERT
#define FLUASSERT_NOABORT
#include "../src/fluassert.h"

int main() {
	fluassert((1 == 0), should.be, true);
	assert(1 == 0);
}

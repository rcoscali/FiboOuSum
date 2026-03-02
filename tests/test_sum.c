#include <assert.h>
#include <stdio.h>
#include "sum.h"

int main(void) {
    assert(compute_sum(1) == 1);
    assert(compute_sum(5) == 15);
    assert(compute_sum(0) == 0);
    assert(compute_sum(-3) == 0);

    assert(fibo(1) == 1);
    assert(fibo(2) == 1);
    assert(fibo(10) == 55);
    assert(fibo(0) == 0);
    assert(fibo(-5) == 0);

    printf("All tests passed\n");
    return 0;
}

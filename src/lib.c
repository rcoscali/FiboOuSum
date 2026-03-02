#include "sum.h"

long long compute_sum(long long n) {
    if (n <= 0) return 0;
    return n * (n + 1) / 2;
}

long long fibo(long long n) {
    if (n <= 0) return 0;
    if (n <= 2) return 1;
    long long a = 1, b = 1, c;
    for (long long i = 3; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

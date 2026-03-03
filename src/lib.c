#include "sum.h"

// Compute the sum of integers from 1 to n
// Formula: sum = n * (n + 1) / 2
// @param n: Upper limit of summation
// @return: Sum of integers from 1 to n, or 0 if n <= 0
long long compute_sum(long long n) {
    // Return 0 for non-positive values
    if (n <= 0) return 0;
    // Apply Gauss formula for sum: n*(n+1)/2
    return n * (n + 1) / 2;
}

// Compute the n-th Fibonacci number using iteration
// Sequence: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, ...
// @param n: Position in Fibonacci sequence
// @return: n-th Fibonacci number, or 0 if n <= 0
long long fibo(long long n) {
    // Base case: return 0 for non-positive values
    if (n <= 0) return 0;
    // Base case: fibo(1) = 1 and fibo(2) = 1
    if (n <= 2) return 1;
    // Iterative computation: maintain two consecutive Fibonacci numbers (a, b)
    long long a = 1, b = 1, c;
    // Compute from position 3 to n
    for (long long i = 3; i <= n; ++i) {
        // Compute c = a + b (next Fibonacci number)
        c = a + b;
        // Shift: a moves to b, b moves to c
        a = b;
        b = c;
    }
    // Return the n-th Fibonacci number
    return b;
}

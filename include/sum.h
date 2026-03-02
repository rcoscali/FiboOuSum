#ifndef SUM_H
#define SUM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* renvoie la somme 1+2+...+n, ou 0 si n <= 0 */
long long compute_sum(long long n);

/* calcule le n-ieme terme de la suite de Fibonacci (F1=1,F2=1)
   retourne 0 pour n <= 0 */
long long fibo(long long n);

#ifdef __cplusplus
}
#endif

#endif /* SUM_H */

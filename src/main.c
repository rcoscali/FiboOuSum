#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>
#include "sum.h"

static void usage(const char *prog) {
    fprintf(stderr,
            "Usage: %s [OPTION] entier\n"
            "Calculer la somme des entiers (option par défaut) ou\n"
            "la suite de Fibonacci.\n\n"
            "  -s, --sum       calculer la somme 1+2+...+n\n"
            "  -f, --fibo      calculer le n-ieme terme de Fibonacci\n"
            "  -h, --help      afficher cette aide\n",
            prog);
}

int main(int argc, char *argv[]) {
    int opt;
    enum { MODE_SUM, MODE_FIBO } mode = MODE_SUM;

    static struct option long_opts[] = {
        {"sum", no_argument, 0, 's'},
        {"fibo", no_argument, 0, 'f'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "sfh", long_opts, NULL)) != -1) {
        switch (opt) {
        case 's':
            mode = MODE_SUM;
            break;
        case 'f':
            mode = MODE_FIBO;
            break;
        case 'h':
            usage(argv[0]);
            return 0;
        default:
            usage(argv[0]);
            return 1;
        }
    }

    if (optind >= argc) {
        usage(argv[0]);
        return 1;
    }

    char *endptr = NULL;
    errno = 0;
    long long n = strtoll(argv[optind], &endptr, 10);
    if (errno != 0 || endptr == argv[optind] || *endptr != '\0') {
        fprintf(stderr, "Argument non valide: %s\n", argv[optind]);
        return 1;
    }

    if (mode == MODE_SUM) {
        printf("%lld\n", compute_sum(n));
    } else {
        printf("%lld\n", fibo(n));
    }

    return 0;
}

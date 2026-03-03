#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>
#include "sum.h"

// Display usage information to stderr
// @param prog: Program name (argv[0])
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

// Main entry point of the program
// Parses command-line arguments and executes sum or Fibonacci computation
// @param argc: Argument count
// @param argv: Argument vector
// @return: 0 on success, 1 on error
int main(int argc, char *argv[]) {
    int opt;
    // Mode enumeration: default is sum calculation
    enum { MODE_SUM, MODE_FIBO } mode = MODE_SUM;

    // Long options for getopt_long
    static struct option long_opts[] = {
        {"sum", no_argument, 0, 's'},    // -s or --sum: calculate sum
        {"fibo", no_argument, 0, 'f'},  // -f or --fibo: calculate Fibonacci
        {"help", no_argument, 0, 'h'},  // -h or --help: display help
        {0, 0, 0, 0}                     // Terminator
    };

    // Parse command-line options
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

    // Check if argument is provided
    if (optind >= argc) {
        usage(argv[0]);
        return 1;
    }

    // Parse the numeric argument
    char *endptr = NULL;
    errno = 0;
    long long n = strtoll(argv[optind], &endptr, 10);
    // Validate that the argument is a valid integer
    if (errno != 0 || endptr == argv[optind] || *endptr != '\0') {
        fprintf(stderr, "Argument non valide: %s\n", argv[optind]);
        return 1;
    }

    // Execute computation based on selected mode
    if (mode == MODE_SUM) {
        printf("%lld\n", compute_sum(n));
    } else {
        printf("%lld\n", fibo(n));
    }

    return 0;
}

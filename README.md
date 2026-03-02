# Fibo

Petit projet en C fournissant deux fonctionnalités :

- calcul de la sommation des entiers de 1 à *n* (`--sum` / `-s`)
- calcul du *n*-ième terme de la suite de Fibonacci (`--fibo` / `-f`)

Le binaire s'appelle `SumOuFibo` et utilise `--sum` si aucune option n'est spécifiée.

## Structure

```
Fibo/
├── CMakeLists.txt        # configuration du build
├── include/sum.h         # prototypes des fonctions
├── src/
│   ├── lib.c             # implémentation des fonctions
│   └── main.c            # interface en ligne de commande
└── tests/
    └── test_sum.cpp      # tests unitaires (googletest)
```

## Prérequis

- un compilateur C (gcc, clang, ...)
- CMake (>= 3.10)

## Compilation

```sh
mkdir build && cd build
cmake ..
cmake --build .
```

Le binaire `SumOuFibo` et le programme de test `test_sum` seront générés dans `build`.

## Exemples d'utilisation

```sh
./SumOuFibo 5           # somme par défaut : 1+2+3+4+5 = 15
./SumOuFibo -s 5        # même résultat
./SumOuFibo -f 10       # 10ème terme de Fibonacci = 55
./SumOuFibo --fibo 20   # 6765
```

## Tests

- la bibliothèque utilise [googletest](https://github.com/google/googletest) ;
  installez `libgtest-dev` (ou équivalent) si nécessaire.
- les tests couvrent les fonctions et l'interface CLI (cas nominal/erreur).

Depuis `build` :

```sh
ctest -V
```

Tous les tests doivent réussir (2 suites + 4 cas CLI).
## Licence

Ce projet est libre de droits. Utilisez-le comme bon vous semble.
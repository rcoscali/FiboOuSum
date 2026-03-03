# Fibo

Petit projet en C fournissant deux fonctionnalités :

- calcul de la sommation des entiers de 1 à *n* (`--sum` / `-s`)
- calcul du *n*-ième terme de la suite de Fibonacci (`--fibo` / `-f`)

Le binaire s'appelle `SumOuFibo` et utilise `--sum` si aucune option n'est spécifiée.

### Rationnel

Ce projet a été généré avec Github Copilot et Claude Haiku 4.5 afin de tester la génération de tests unitaire pour l'interface CLI. La totalité du code, du projet cmake et des tests unitaires on été généré avec 3 ou 4 prompts. Le résultat est une fonction runCommand dans google test qui permet de capturer le code de retour et le flux stdout. Un dernier prompt va ajouter la capture de stderr pour vérifier le report d'erreur:
```
> Ajoute dans les tests d'erreur la capture du flux d'erreur standard et sa vérification.
Lire [](file:///home/rcoscali/Sources/Fibo/tests/test_sum.cpp)

Voyons le contenu actuel du test pour voir comment améliorer la capture de stderr. 

Remplacement de 35 lignes par 65 lignes dans [](file:///home/rcoscali/Sources/Fibo/tests/test_sum.cpp)


```

```
Rebuild the project to verify the updated tests. 

Ran terminal command:  cd /home/rcoscali/Sources/Fibo && cmake --build build
Completed with input:  cd /home/rcoscali/Sources/Fibo && cmake --build build

I need to add the gmock matcher header for `HasSubstr`. 

Using "Remplacer une chaîne dans un fichier"

Using "Remplacer une chaîne dans un fichier"

Lire [](file:///home/rcoscali/Sources/Fibo/tests/test_sum.cpp#1-1), lignes 1 à 10

Using "Remplacer une chaîne dans un fichier"

Remplacement de 4 lignes par 5 lignes dans [](file:///home/rcoscali/Sources/Fibo/tests/test_sum.cpp)


```

```


Ran terminal command:  cd /home/rcoscali/Sources/Fibo && cmake --build build

Ran terminal command:  cd /home/rcoscali/Sources/Fibo/build && ctest -V

✅ **Tests d'erreur renforcés avec capture de stderr**

Les tests d'erreur capturent et valident maintenant le flux d'erreur standard.

### 🔧 Améliorations apportées

- **Structure `CmdResult`** étendue pour inclure un champ `err` (contient stderr capturé).
- **Fonction `runCommand()`** mise à jour pour capturer stderr dans un fichier temporaire, puis en lisant le contenu.
- **Ajout du header gmock** pour accéder aux matchers comme `HasSubstr()`.
- **Tests d'erreur améliorés** :
  - `ErrorMissingArg` – vérifie que stderr contient `"Usage:"` et `"entier"`.
  - `ErrorInvalidNum` – vérifie que stderr contient `"Argument non valide"` et le paramètre passé (`"abc"`).

### 📊 Résultats

```
```bash
6/6 tests passed (100% success rate)
```
```

Chaque test d'erreur confirme non seulement un code de sortie non-zéro, mais aussi que les messages d'erreur appropriés sont affichés sur stderr.

Made changes.
```

Au niveau des tests unitaires, l'utilisation que fait le modèle de HasSubStr permet de vérifier que les messages d'erreur contiennent des éléments clés, sans nécessiter une correspondance exacte. Cela rend les tests plus robustes face à de légères variations dans les messages d'erreur tout en assurant que les informations essentielles sont présentes.
Cela prouve que le modèle est capable de générer des tests unitaires plus complets et réalistes, en capturant à la fois les codes de retour et les messages d'erreur, ce qui est crucial pour tester une interface en ligne de commande de manière efficace.

*Il a une réelle compréhension de ce qu'est une stratégie de test et comment elle doit être mise en œuvre pour couvrir les différents scénarios d'utilisation et d'erreur.*

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

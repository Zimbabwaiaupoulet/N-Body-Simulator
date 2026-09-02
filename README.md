# N-Body-Simulator

Simulateur de dynamique N-Corps en 2D pour la simulation d'interactions gravitationnelles. Ce projet de rattrapage d'ECTS valide la deuxième année de bachelor à l'ISEN Méditerranée.

## 📋 Vue d'ensemble

Le projet implémente plusieurs approches pour résoudre le problème des N corps :

- **Méthode Brute Force** : O(N²) - calcul exact
- **Algorithme de Barnes-Hut** : O(N log N) - optimisé avec quadtree
- **Intégration Leapfrog** : schéma numérique plus précis qu'Euler

### Fichiers principaux

#### Programmes de simulation

- **main.cpp** : Système 2-corps simple (Soleil-Terre) - intégration Euler
- **mainA2.cpp** : Système 2-corps avec intégration Leapfrog
- **mainN.cpp** : Système solaire complet (5 corps) avec Leapfrog
- **mainBrute.cpp** : Benchmark approche brute force O(N²)
- **mainB2.cpp** : Analyse d'erreur avec différentes valeurs de θ (Barnes-Hut)
- **mainB3.cpp** : Benchmark comparatif : Brute Force vs Barnes-Hut

#### Tests

- **testVector2D.cpp** : Tests des opérations vectorielles 2D
- **testB1.cpp** : Tests supplémentaires

#### Structures de données

- **Vector2D.hpp/cpp** : Vecteurs 2D avec opérations (addition, soustraction, multiplication, norme)
- **Corps.hpp** : Structure représentant un corps (position, vitesse, accélération, masse)
- **Node.hpp** : Nœud de quadtree pour l'algorithme de Barnes-Hut

## 🔧 Compiler le projet

Depuis le répertoire `2D/` :

```bash
make              # Compile tous les programmes
make clean        # Supprime les fichiers compilés
```

Ou manuellement :

```bash
g++ src/main.cpp src/Vector2D.cpp -Iheaders -o bin/main
```

## ▶️ Lancer les programmes

### Simulations

| Commande        | Description                                        |
| --------------- | -------------------------------------------------- |
| `make run`      | Simulation 2-corps Euler → `trajectoire_A1.csv`    |
| `make runA2`    | Simulation 2-corps Leapfrog → `trajectoire_A2.csv` |
| `make runA3`    | Système solaire → `trajectoire_A3.csv`             |
| `make runBrute` | Benchmark brute force → CSV temps                  |
| `make runB2`    | Tests erreur Barnes-Hut (différents θ)             |
| `make runB3`    | Benchmark Brute vs Barnes-Hut → `benchmark.csv`    |

Exemple :

```bash
cd 2D
make runB3         # Lance le benchmark
```

### Visualisation

Les résultats CSV sont générés dans `2D/csv/`. Pour visualiser :

```bash
python traceur.py
```

Ce script génère des graphiques à partir des fichiers CSV.

## 📊 Structure du projet

```
N-Body-Simulator/
├── 2D/
│   ├── src/                    # Fichiers source C++
│   │   ├── main.cpp           # Simulation de base
│   │   ├── mainA2.cpp         # Leapfrog 2-corps
│   │   ├── mainN.cpp          # Système solaire
│   │   ├── mainBrute.cpp      # Benchmark brute force
│   │   ├── mainB2.cpp         # Tests d'erreur
│   │   ├── mainB3.cpp         # Benchmark comparatif
│   │   ├── Vector2D.cpp       # Implémentation vecteurs
│   │   └── testVector2D.cpp   # Tests vecteurs
│   ├── headers/               # Fichiers headers
│   │   ├── Vector2D.hpp       # Définition vecteurs 2D
│   │   ├── Corps.hpp          # Structure Corps
│   │   └── Node.hpp           # Arbre quadtree (Barnes-Hut)
│   ├── csv/                   # Fichiers de sortie
│   ├── bin/                   # Exécutables compilés
│   └── Makefile              # Règles de compilation
├── traceur.py                 # Script de visualisation
└── README.md                  # Ce fichier
```

## 🧮 Algorithmes implémentés

### Barnes-Hut (O(N log N))

- Construction d'un quadtree partitionnant l'espace
- Calcul du centre de masse par nœud
- Approximation des forces lointaines (contrôlée par θ)
- θ = paramètre d'accuracy (plus petit = plus précis)

### Leapfrog (Intégration numérique)

- Schéma semi-implicite plus stable qu'Euler
- Meilleure conservation de l'énergie
- Erreur locale O(dt³), erreur globale O(dt²)

## 📈 Résultats attendus

### Fichiers de sortie CSV

- **trajectoire_A1.csv** : Orbite terrestre simple
- **trajectoire_A2.csv** : Orbite elliptique (e=0.2)
- **trajectoire_A3.csv** : Trajectoires 5 planètes
- **benchmark.csv** : Comparaison temps d'exécution

## 💡 Notes sur la mise en œuvre

- Toutes les dépendances de `std::` sont qualifiées complètement (`std::vector`, `std::cout`, etc.)
- Utilise C++14+ pour `std::make_unique`
- Pas de dépendances externes (stdlib uniquement)
- Compilé avec g++ sur Windows/Linux

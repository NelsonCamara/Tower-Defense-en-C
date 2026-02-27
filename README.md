# Tower Defense en C

Jeu de Tower Defense développé en **C** avec rendu graphique via la bibliothèque **MLV**. Le joueur place des tours, y insère des gemmes élémentaires, et défend un chemin généré procéduralement contre des vagues de monstres aux caractéristiques variées.

---

## 📖 À propos du projet

Le jeu repose sur un système de **gemmes élémentaires** (Pyro 🔥, Dendro 🌿, Hydro 💧) avec des réactions croisées entre éléments, un système économique de **mana** avec progression exponentielle, et une génération procédurale de carte basée sur l'**algorithme de Manhattan**. Les vagues de monstres (Boss, Agile, Foule, Base) se succèdent automatiquement ou peuvent être forcées par le joueur pour gagner du mana bonus.

---

## Architecture & Structure

```
Tower-Defense-en-C/
├── include/               → Headers (.h)
│   ├── Utils.h            → Structures de base (Point, Direction, TimedEvent, ElementalEvent)
│   ├── Tint.h             → Système de couleurs et éléments (Color, Element)
│   ├── Gem.h              → Gemmes élémentaires et fusion
│   ├── Shoot.h            → Projectiles et calcul de dégâts
│   ├── Monster.h          → Monstres, vagues, liste chaînée de WaveNode
│   ├── Tower.h            → Tours et zones de tir
│   ├── Map.h              → Grille, joueur, génération procédurale
│   ├── Game.h             → Boucle de jeu et spawn
│   ├── Graphic.h          → Rendu graphique MLV
│   ├── PlayerEvents.h     → Événements joueur, économie, effets élémentaires
│   ├── EntityMovements.h  → Déplacements monstres et projectiles
│   └── Inventory.h        → Inventaire
├── src/                   → Sources (.c) — 14 fichiers
├── Makefile               → Compilation GCC avec MLV
└── bin/                   → Exécutable compilé
```

**27 fichiers** (headers + sources) | **~2700 lignes de code** (headers inclus)

---

## Compétences techniques démontrées

### Programmation C avancée

- **Gestion manuelle de la mémoire** — `malloc`, `realloc`, `free` systématiques avec vérification d'allocation et `perror` / `exit(EXIT_FAILURE)` en cas d'échec
- **Tableaux dynamiques génériques** — Structures `MonsterArray` et `ShootArray` avec `size`, `sizeMax`, redimensionnement automatique (×2) via `realloc`, ajout/suppression par index avec décalage
- **Liste chaînée triée** — `WaveNode` pour les vagues de monstres avec insertion ordonnée (`insertWaveSorted`), recherche du point d'insertion (`findInsertionPoint`), suppression de nœuds, et nettoyage des vagues expirées (`removeExpiredWaves`)
- **Pointeurs et indirections multiples** — `Grid` contient `Point **grid` (grille 2D allouée dynamiquement), `Tower*` (tableau dynamique), `MonsterArray*`, `Player*`
- **Structures imbriquées complexes** — Chaque `Monster` contient un `ShootArray*`, un `ElementalEvent*`, lui-même contenant un `TimedEvent*`

### Génération procédurale — Algorithme de Manhattan

- **Génération du chemin** — Algorithme complet en plusieurs phases : point de départ aléatoire (`caseAleat`), direction initiale probabiliste (`getDir`), extension du chemin (`growway`), changement de direction (`detNewDir`)
- **Détection de collisions** — `colisionWithWayOrEndOfMap` vérifie la distance de Manhattan aux bords et aux segments existants du chemin
- **Probabilités pondérées** — Les directions sont choisies avec une probabilité proportionnelle à leur étendue (`extent`), le nombre de cases ajoutées suit une loi de Bernoulli (75%)
- **Validation** — Le chemin doit atteindre ≥75 cases avec ≥7 virages, sinon régénération complète (`checkway`)
- **Gestion mémoire** — Allocation dynamique du chemin avec `realloc` progressif, libération complète via `deletegrid`

### Système élémentaire & Réactions croisées

- **3 éléments de base** — Pyro (dégâts de zone), Dendro (poison DoT), Hydro (ralentissement)
- **Réactions combinées** — 3 réactions : Pyro×Dendro (burst ×2), Pyro×Hydro (zone + slow), Dendro×Hydro (immobilisation)
- **Événements temporisés** — Structure `TimedEvent` avec `frequency`, `duration`, `elapsed_since_last_event`, `elapsed_total` pour gérer les effets dans le temps (DoT, slow, freeze)
- **Système de teintes** — Dégâts calculés via `d × 2^level × (1 - cos(tintShoot - tintTarget) / 2)` utilisant les teintes de couleur (0-359°) pour un avantage/désavantage élémentaire

### Moteur de jeu

- **Game loop à 60 FPS** — Boucle principale avec `clock_gettime(CLOCK_REALTIME)` pour le delta time, compensation du frametime excédentaire via `MLV_wait_milliseconds`
- **Machine à états** — Variable `gameState` (0-4) pour gérer les modes d'interaction : navigation, création de gemme, saisie de niveau, placement de tour, sélection inventaire
- **Système de vagues** — 4 types (`BOSS`, `AGILE`, `FOULE`, `BASE`) avec probabilités pondérées, spawn automatique toutes les 35s ou forcé (touche `M`) avec bonus de mana
- **Économie exponentielle** — Coûts et gains en mana suivent des courbes `pow(1.2, wave)`, `pow(1.3, level)`, `pow(2, gemLevel)` pour un scaling progressif
- **Ciblage intelligent** — Les tours ciblent le monstre avec le plus de HP dans leur zone de portée (rayon 3 cases)

### Interface graphique (MLV)

- **Rendu complet** — Grille colorée, sidebar avec boutons interactifs, barres de vie dynamiques, projectiles animés, inventaire 3×3 avec gemmes colorées
- **Gestion événementielle** — Clics souris (boutons, grille, inventaire) et clavier (M pour vague, P pour level up mana)
- **Input box** — Saisie textuelle pour le niveau des gemmes avec validation (`isAllDigits`)
- **Hit detection** — Conversion coordonnées pixel → case grille via `clickOnGridCase`, détection de zone via `posFlInZone`

### Bonnes pratiques C

- **Séparation header/source** — Chaque module a son `.h` avec guards (`#ifndef`) et son `.c`
- **Makefile** — Compilation automatique avec `gcc -Wall -lMLV -lm -O1`, gestion des dépendances
- **Vérification systématique** — Tous les `malloc` sont suivis d'un test de nullité
- **Libération mémoire** — `freeMonsterArray`, `freeShotArray`, `deletegrid` pour éviter les fuites

---

## Lancement

### Prérequis
- **GCC** 
- **Bibliothèque MLV** (libMLV)
- **Linux** (Ubuntu/Debian recommandé)

### Installation de MLV (Debian/Ubuntu)
```bash
sudo apt-get install libmlv3-dev
```

### Compilation
```bash
make
```

### Exécution
```bash
./bin/towerdefense
```

### Nettoyage
```bash
make clean
```

---

## Contrôles

| Action | Contrôle |
|--------|----------|
| Créer une gemme | Bouton "New Gem" → saisir le niveau → "Confirm level" |
| Placer une tour | Bouton "New Tower" → cliquer sur la grille |
| Placer une gemme sur une tour | Cliquer sur une gemme dans l'inventaire → cliquer sur une tour |
| Fusionner deux gemmes | Cliquer sur une gemme → cliquer sur une autre (même niveau) |
| Forcer une nouvelle vague | Touche `M` (bonus mana proportionnel au temps restant) |
| Augmenter le niveau de mana | Touche `P` |

---

## Technologies

| Technologie | Usage |
|-------------|-------|
| C (C99) | Langage principal |
| Bibliothèque MLV | Rendu graphique et événements |
| GCC | Compilation avec `-Wall -O1` |
| Make | Automatisation de build |
| `math.h` | Calculs trigonométriques (dégâts, distances) |
| `time.h` / `clock_gettime` | Gestion du framerate et événements temporisés |

---

## Auteur

**Nelson Camara** — Étudiant en Master Informatique

---

*Projet académique — Tower Defense avec génération procédurale et système élémentaire.*

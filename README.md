# Railway Signaling System

[![Test Report](https://github.com/GeorgeSixth/SimpleRailwaySignals/actions/workflows/test-report.yml/badge.svg)](https://github.com/GeorgeSixth/SimpleRailwaySignals/actions/workflows/test-report.yml)

## Description
Ce système de signalisation ferroviaire est un exemple d'implémentation conforme à la norme CENELEC 50128 (SIL2). Il démontre la gestion des signaux ferroviaires simples avec support complet pour les changements d'états, les commandes réversibles et la gestion d'événements asynchrones. La simplicité de ce projet, fait qu'il est techniquement conforme à SIL4 sous la CENELEC 50128.

## Caractéristiques Principales
- 🚦 Gestion complète des aspects des signaux (Rouge, Vert, Jaune)
- ⏱️ Traitement asynchrone des commandes
- ↩️ Support complet undo/redo des commandes
- 🔒 Implémentation conforme SIL2
- 🧪 Tests unitaires exhaustifs

## Prérequis
- Compilateur C++23
- CMake 3.15+
- Conan 2.8
- Boost 1.84.0
- GTest 1.14.0
- Linux pour la simplicité, mais Conan le projet est compatible sur Windows avec Conan

## Installation

### 1. Cloner le dépôt
```bash
git clone https://github.com/your-org/railway-signaling.git
cd railway-signaling
```

### 2. Configuration de Conan
```bash
conan profile detect
mkdir build && cd build
conan install .. --output-folder . --build=missing
```

### 3. Configuration et compilation
```bash
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

### 4. Exécution des tests
```bash
ctest --output-on-failure
```

## Architecture

### Patron de conception: Command
Le système utilise le pattern Command pour encapsuler toutes les opérations sur les signaux :
- Permet la réversibilité des opérations
- Garantit la traçabilité des changements
- Facilite l'audit de sécurité

### Gestion d'État
Les changements d'état suivent un workflow strict :
```
Rouge ⟷ Jaune ⟷ Vert
```
Chaque transition est validée selon les règles de sécurité définies.

### Événements Asynchrones
Utilisation de Boost.Asio et Boost.Signals2 pour :
- La gestion des commandes asynchrones
- La notification des changements d'état
- La surveillance du système

## Documentation
La documentation complète est disponible dans le dossier `docs/` :
- [Exigences CENELEC et SIL](docs/REQUIREMENTS.MD)
- [Référence des Classes](docs/CLASS_REFERENCE.md)
- [Documentation de Sécurité](docs/SAFETY.md)
- [Documentation de Conception](docs/DESIGN.md)

## Tests
Le projet inclut plusieurs niveaux de tests :
- Tests unitaires (GTest)
- Tests d'intégration
- Tests de validation de sécurité

Pour exécuter un test spécifique :
```bash
./build/bin/railway_signaling_test --gtest_filter=RailwaySignalTest.AspectChange
```

## Sécurité et Conformité
Ce projet suit les directives de la norme CENELEC 50128 à titre d'exemple :
- Développement basé sur les exigences de sécurité
- Documentation exhaustive
- Traçabilité complète
- Validation indépendante

## Contribution
1. Fork le projet
2. Créer une branche (`git checkout -b feature/AmazingFeature`)
3. Commit les changements (`git commit -m 'Add AmazingFeature'`)
4. Push vers la branche (`git push origin feature/AmazingFeature`)
5. Ouvrir une Pull Request

## Licence
Distribué sous la licence MIT. Voir `LICENSE` pour plus d'informations.

## Contact
Votre Nom - [@votretwitter](https://twitter.com/votretwitter)
Lien du projet: [https://github.com/your-org/railway-signaling](https://github.com/your-org/railway-signaling)

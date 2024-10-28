#!/bin/bash
# Fichier: build.sh

# Couleurs pour une meilleure lisibilité
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Fonction pour afficher les messages d'erreur et quitter
error_exit() {
    echo -e "${RED}Erreur: $1${NC}" >&2
    exit 1
}

# Fonction pour afficher les messages d'information
info() {
    echo -e "${BLUE}Info: $1${NC}"
}

# Fonction pour afficher les succès
success() {
    echo -e "${GREEN}Succès: $1${NC}"
}

# Fonction pour afficher les avertissements
warning() {
    echo -e "${YELLOW}Attention: $1${NC}"
}

# Vérification de la présence de Conan
if ! command -v conan &> /dev/null; then
    error_exit "Conan n'est pas installé. Veuillez l'installer avec 'pip install conan==2.8.0'"
fi

# Vérification de la présence de CMake
if ! command -v cmake &> /dev/null; then
    error_exit "CMake n'est pas installé"
fi

# Création du répertoire build s'il n'existe pas
if [ ! -d "build" ]; then
    info "Création du répertoire build..."
    mkdir build
fi

# Nettoyage du répertoire build si demandé
if [ "$1" == "clean" ]; then
    warning "Nettoyage du répertoire build..."
    rm -rf build/*
fi

# Passage dans le répertoire build
cd build || error_exit "Impossible d'accéder au répertoire build"

# Créer un sous-répertoire pour les fichiers Conan
mkdir -p conan

# Configuration de Conan pour utiliser le bon répertoire
info "Configuration de Conan..."
conan profile detect

# Installation des dépendances avec Conan
info "Installation des dépendances avec Conan..."
conan install .. \
    --output-folder=conan \
    --build=missing \
    || error_exit "Échec de l'installation des dépendances"

# Configuration avec CMake
info "Configuration avec CMake..."
cmake .. \
    -DCMAKE_TOOLCHAIN_FILE=conan/conan_toolchain.cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_PREFIX_PATH=conan \
    || error_exit "Échec de la configuration CMake"

# Compilation
info "Compilation du projet..."
cmake --build . -j$(nproc) || error_exit "Échec de la compilation"

# Exécution des tests
info "Exécution des tests..."
ctest --output-on-failure || error_exit "Échec des tests"

# Si tout s'est bien passé
success "Build et tests terminés avec succès!"

# Afficher le chemin vers l'exécutable
if [ -f "bin/railway_signal_demo" ]; then
    info "L'exécutable de démonstration est disponible ici: ${PWD}/bin/railway_signal_demo"
    
    # Demander si l'utilisateur veut exécuter la démo
    read -p "Voulez-vous exécuter la démo maintenant? (o/N) " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Oo]$ ]]; then
        echo "Lancement de la démo..."
        ./bin/railway_signal_demo
    fi
fi

exit 0

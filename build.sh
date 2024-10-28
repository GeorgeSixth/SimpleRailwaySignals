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

# Vérification de GCC 13
if ! command -v gcc-13 &> /dev/null; then
    error_exit "GCC 13 n'est pas installé. Veuillez l'installer avec: sudo apt install gcc-13 g++-13"
fi

# Vérification de la présence de Conan
if ! command -v conan &> /dev/null; then
    error_exit "Conan n'est pas installé. Veuillez l'installer avec 'pip install conan==2.8.0'"
fi

# Vérification de la présence de CMake
if ! command -v cmake &> /dev/null; then
    error_exit "CMake n'est pas installé"
fi

# Définition du type de build
BUILD_TYPE=Release

# Configuration des compilateurs
export CC=gcc-13
export CXX=g++-13

# Nettoyage si demandé
if [ "$1" == "clean" ]; then
    warning "Nettoyage complet..."
    rm -rf build
fi

# Création du répertoire build s'il n'existe pas
if [ ! -d "build" ]; then
    info "Création du répertoire build..."
    mkdir build
fi

# Passage dans le répertoire build
cd build || error_exit "Impossible d'accéder au répertoire build"

# Configuration de Conan
info "Configuration de Conan..."
conan profile detect --force || error_exit "Échec de la détection du profil Conan"

# Mettre à jour le profil Conan pour utiliser GCC 13
CONAN_DEFAULT_PROFILE=~/.conan2/profiles/default
if [ -f "$CONAN_DEFAULT_PROFILE" ]; then
    info "Configuration du profil Conan..."
    # Créer une copie de sauvegarde
    cp "$CONAN_DEFAULT_PROFILE" "${CONAN_DEFAULT_PROFILE}.bak"
    # Mettre à jour le compilateur
    sed -i 's/compiler=gcc/compiler=gcc/g' "$CONAN_DEFAULT_PROFILE"
    sed -i 's/compiler.version=[0-9]*/compiler.version=13/g' "$CONAN_DEFAULT_PROFILE"
    sed -i 's/compiler.libcxx=.*/compiler.libcxx=libstdc++11/g' "$CONAN_DEFAULT_PROFILE"
fi

# Installation des dépendances avec Conan
info "Installation des dépendances avec Conan..."
conan install .. \
    --output-folder=. \
    --build=missing \
    -s build_type=$BUILD_TYPE \
    -s compiler.version=13 \
    -s compiler.libcxx=libstdc++11 \
    || error_exit "Échec de l'installation des dépendances"

# Configuration avec CMake
info "Configuration avec CMake..."
cmake .. \
    -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake \
    -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
    -DCMAKE_C_COMPILER=gcc-13 \
    -DCMAKE_CXX_COMPILER=g++-13 \
    || error_exit "Échec de la configuration CMake"

# Compilation
info "Compilation du projet..."
cmake --build . --config $BUILD_TYPE -j$(nproc) || error_exit "Échec de la compilation"

# Exécution des tests
info "Exécution des tests..."
ctest --output-on-failure -C $BUILD_TYPE || error_exit "Échec des tests"

# Si tout s'est bien passé
success "Build et tests terminés avec succès!"

# Afficher le chemin vers l'exécutable
DEMO_PATH="bin/railway_signal_demo"
if [ -f "$DEMO_PATH" ]; then
    info "L'exécutable de démonstration est disponible ici: ${PWD}/${DEMO_PATH}"
    
    # Demander si l'utilisateur veut exécuter la démo
    read -p "Voulez-vous exécuter la démo maintenant? (o/N) " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Oo]$ ]]; then
        echo "Lancement de la démo..."
        ./"$DEMO_PATH"
    fi
fi

exit 0

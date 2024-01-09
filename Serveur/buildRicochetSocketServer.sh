#!/bin/bash

# Répertoire source du code
source_dir="/home/ricochet/RobotRicochetSolver"

# Répertoire de build
build_dir="/home/ricochet/buildServeur"

# Répertoire du serveur
server_dir="${source_dir}/Serveur/Socket/StdSocketsServ"

# Nom de l'exécutable
executable_name="serveurSocketRicochet"

# Assurez-vous que le répertoire de build existe
mkdir -p "${build_dir}"

# Pull du code depuis le répertoire source
cd "${source_dir}" || exit
git pull

# Compilation avec cmake
cd "${server_dir}" || exit
cmake -S . -B "${build_dir}"
make -C "${build_dir}"

# Vérification si la compilation a réussi
if [ -e "${build_dir}/${executable_name}" ]; then
    echo "Compilation réussie. L'exécutable se trouve dans : ${build_dir}/${executable_name}"
else
    echo "Erreur lors de la compilation."
fi

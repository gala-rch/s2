# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.10)

# La version du C++ que l'on souhaite utiliser (dans notre cas C++17)
set(CMAKE_CXX_STANDARD 17)

# Le nom du projet
project(TD4)

# On indique que l'on veut créer un exécutable "helloImac" compilé à partir du fichier helloImac.cpp
add_executable(exo1 src/exo1.cpp)
add_executable(exo2 src/exo2.cpp)
add_executable(exo3 src/exo3.cpp)
add_executable(pourallerplusloin src/papl.cpp)




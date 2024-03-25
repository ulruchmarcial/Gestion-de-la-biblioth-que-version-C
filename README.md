# Guide d'Utilisation du Makefile

## Introduction

Le Makefile fourni simplifie le processus de compilation et de gestion des dépendances pour un projet C. Il compile un programme principal (`main`) et un programme de tests unitaires (`test_unit`). La structure du projet est organisée avec des répertoires distincts pour les sources principales (`src`), les bibliothèques (`lib`), et les tests unitaires (`test`).

## Contenu du Projet

Assurez-vous que vos fichiers sources (`main.c`, `tools.c`) et en-têtes (`tools.h`) sont dans le dossier `src`, les fichiers de tests (`test_unit.c`, `test_unit.h`) dans le dossier `test`, et les fichiers de bibliothèque dans le dossier `lib`.

project_folder/
│
├── lib/
│ └── (fichiers sources et en-têtes des bibliothèques)
│
├── src/
│ ├── main.c
│ └── tools.c
│ └── tools.h
│
├── test/
│ ├── test_unit.c
│ └── test_unit.h
│
└── Makefile



## Utilisation du Makefile

### Compilation de l'exécutable principal (`main`)

1. **Commande de Compilation :**
   ```bash
   make main

   Exécution du Programme Principal :
   ./main
2. **Compilation des Tests Unitaires (test_unit):**
make test_unit
Exécution du Programme de test :
./test_unit

3. **Nettoyage des Fichiers Générés**
Pour supprimer les fichiers objets et les exécutables générés :
make clean


4. **Personnalisation du Projet**
Ajout de Nouvelles Fonctionnalités :

Ajoutez de nouveaux fichiers source et en-têtes dans les dossiers appropriés (src, lib, test).
Mettez à jour le Makefile pour inclure les nouveaux fichiers.
Personnalisation des Options de Compilation :

Modifiez les variables CFLAGS et CXXFLAGS dans le Makefile pour ajuster les options de compilation

En suivant ce guide, vous pourrez compiler votre programme principal, exécuter des tests unitaires, et nettoyer les fichiers générés à l'aide du Makefile fourni. Assurez-vous d'organiser votre projet selon la structure suggérée pour une gestion efficace des fichiers source et des dépendances
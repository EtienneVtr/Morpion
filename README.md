# Morpion : premier projet d'IA

**Auteur** : Etienne VATRY  
**Date** : Janvier 2024

## Description

Application d'un algorithme alpha-beta sur un jeu de Morpion. Pas d'interface graphique, celui-ci se fait par ligne de commande. L'algorithme est optimisé grâce à l'utilisation d'une table de hashage pour stocker les coups déjà joués. L'algorithme est relativement performant pour les tailles allant jusqu'à 4x4. Cependant, pour des tailles supérieures, une erreur ressort disant que la taille d'allocation est trop grande.

## Utilisation

Pour lancer le programme, il suffit de lancer l'exécutable à la racine du projet. Tout est ensuite indiqué. Vous pouvez aussi le lancer à l'aide de la commande ```make run```.

## Compilation

Pour compiler le projet, il suffit de lancer la commande ```make``` à la racine du projet. Cela va créer un exécutable ```Main``` à la racine du projet, puis le lancera. Vous pouvez aussi le compiler à l'aide de la commande ```make compil``` ce qui permet de compiler sans lancer l'exécution du programme.

## Organisation

Le projet est organisé de la manière suivante :  
```
.  
├── Main  
├── makefile  
├── README.md  
└── src  
    ├── Main.c  
    ├── Morpion.c  
    └── Morpion.h  
```
- ```Main``` est le fichier exécutable, 
- ```makefile``` est le fichier permettant de compiler le projet,
- ```README.md``` est le fichier que vous êtes en train de lire,
- ```src``` est le dossier contenant les fichiers sources du projet : 
    - ```Main.c``` est le fichier contenant la fonction ```main()```. Il contient la logique de jeu à deux joueurs.
    - ```Morpion.c``` est le fichier contenant les fonctions relatives au jeu de Morpion. Il contient la logique de jeu contre l'ordinateur.
    - ```Morpion.h``` est le fichier contenant les prototypes des fonctions du fichier ```Morpion.c```.

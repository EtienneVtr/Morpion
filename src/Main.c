#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "Morpion.h"

int main(void) {
    bool jeu = true;
    bool partie = true;
    // joueur choisi aléatoirement
    srand(time(NULL));
    bool joueur = rand() % 2;

    bool vsOrdinateur = false;

    char input[100];
    int ligne, colonne;
    int read;

    Grille_t* grille = initGrille();

    char nomJ1[100];
    char nomJ2[100];

    printf("Entrez le nom du joueur 1 :\n");
    fgets(nomJ1, 100, stdin);
    printf("Voulez vous jouer contre l'ordinateur ? (1 pour oui, 0 pour non)\n");
    fgets(input, 100, stdin);
    read = sscanf(input, "%d", &ligne);

    if (read == 1 && ligne == 1) {
        strcpy(nomJ2, "Ordinateur ");
        vsOrdinateur = true;
    } else if (read == 1 && ligne == 0) {
        printf("Entrez le nom du joueur 2 :\n");
        fgets(nomJ2, 100, stdin);
    } else {
        printf("Entrée invalide, veuillez entrer un nombre.\n");
        return EXIT_FAILURE;
    }

    nomJ1[strlen(nomJ1)-1] = '\0'; 
    nomJ2[strlen(nomJ2)-1] = '\0';

    grille->nomJ1 = nomJ1;
    grille->nomJ2 = nomJ2;

    printf("Les deux joueurs sont donc %s et %s !\n", grille->nomJ1, grille->nomJ2);
    printf("%s aura les 'X' et %s aura les 'O' !\n", grille->nomJ1, grille->nomJ2);

    while(jeu) {
        printf("\nLancement de la partie !\n");

        while (partie){
            printf("\n");
            affichageGrille(grille);
            printf("\nC'est à %s de jouer !\n", joueur ? grille->nomJ2 : grille->nomJ1);

            if(!vsOrdinateur){
                bool test = false;
                while (!test) {
                    printf("Entrez la ligne et la colonne de votre choix :\n");
                    fgets(input, 100, stdin);
                    read = sscanf(input, "%d %d", &ligne, &colonne);

                    if (read == 2) { // Si deux nombres ont été lus correctement
                        test = jouer(grille, ligne - 1, colonne - 1, joueur);
                        if (!test) {
                            printf("Coup invalide, veuillez réessayer.\n");
                        }
                    } else {
                        printf("Entrée invalide, veuillez entrer deux nombres.\n");
                    }
                }
            }else{
                if (!joueur){
                    bool test = false;
                    while (!test) {
                        printf("Entrez la ligne et la colonne de votre choix :\n");
                        fgets(input, 100, stdin);
                        read = sscanf(input, "%d %d", &ligne, &colonne);

                        if (read == 2) { // Si deux nombres ont été lus correctement
                            test = jouer(grille, ligne - 1, colonne - 1, joueur);
                            if (!test) {
                                printf("Coup invalide, veuillez réessayer.\n");
                            }
                        } else {
                            printf("Entrée invalide, veuillez entrer deux nombres.\n");
                        }
                    }
                }else{
                    jouerOrdi(grille);
                }
            }
            

            if (victoire(grille) == 0){
                joueur = !joueur;
            } else if (victoire(grille) < 3){
                printf("\n%s gagne la partie !\n", (victoire(grille) == 1) ? grille->nomJ1 : grille->nomJ2);
                if (victoire(grille) == 1) grille->scoreJ1++;
                else grille->scoreJ2++;
                partie = false;
                affichageGrille(grille);
            } else {
                printf("\nMatch nul !\n");
                partie = false;
            }
        }

        printf("Affichage des scores : %s : %d, %s : %d\n", grille->nomJ1, grille->scoreJ1, grille->nomJ2, grille->scoreJ2);

        printf("Voulez-vous rejouer ? (1 pour oui, 0 pour non)\n");
        int choix;
        fgets(input, 100, stdin);
        read = sscanf(input, "%d", &choix);
        if (read == 1){
            if (choix == 0) jeu = false;
            else {
                partie = true;
                joueur = rand() % 2;
                for (int i = 0 ; i < TAILLE*TAILLE ; i++) grille->grille[i] = 0;
            }
        } else {
            printf("Entrée invalide, veuillez entrer 1 ou 0.\n");
        }
    }

    free(grille);

    return EXIT_SUCCESS;
}

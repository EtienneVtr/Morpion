#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Morpion.h"

Grille_t* initGrille(){
    Grille_t* grille = malloc(sizeof(Grille_t));
    for (int i = 0 ; i < TAILLE*TAILLE ; i++) grille->grille[i] = 0;
    grille->nomJ1 = "";
    grille->nomJ2 = "";
    grille->scoreJ1 = 0;
    grille->scoreJ2 = 0;

    return grille;
}

void affichageGrille(Grille_t* grille){
    char symboles[3];
    symboles[0] = '.';
    symboles[1] = 'X';
    symboles[2] = 'O';

    // on adapte l'affichage en fonction de la taille de la grille
    printf("  ");
    for (int i = 0 ; i < TAILLE ; i++) printf("----");
    printf("\n");
    for (int i = 0 ; i < TAILLE ; i++){
        printf("  |");
        for (int j = 0 ; j < TAILLE ; j++){
            printf(" %c |", symboles[grille->grille[i*TAILLE + j]]);
        }
        printf("\n");
        printf("  ");
        for (int i = 0 ; i < TAILLE ; i++) printf("----");
        printf("\n");
    }
}

bool jouer(Grille_t* grille, int i, int j, bool joueur){
    if (i < 0 || i > TAILLE - 1 || j < 0 || j > TAILLE - 1){
        printf("Coordonnées invalides !\n");
        return false;
    } else{ 
        if (grille->grille[i*TAILLE + j] == 0) {
            grille->grille[i*TAILLE + j] = joueur + 1;
            return true;
        } else {
            printf("Case déjà prise !\n");
            return false;
        }
    }
}

int victoire(Grille_t* grille){
    int victoire = 0;
    int g[TAILLE*TAILLE];
    for (int i = 0 ; i < TAILLE*TAILLE ; i++) g[i] = grille->grille[i];

    // Vérification des lignes
    for (int i = 0 ; i < TAILLE ; i++){
        bool test = true;
        for (int j = 0 ; j < TAILLE - 1 ; j++){
            if (g[i*TAILLE + j] != g[i*TAILLE + j + 1] || g[i*TAILLE + j] == 0) test = false;
        }
        if (test) {victoire = g[i*TAILLE]; return victoire;}
    }

    // Vérification des colonnes
    for (int i = 0 ; i < TAILLE ; i++){
        bool test = true;
        for (int j = 0 ; j < TAILLE - 1 ; j++){
            if (g[j*TAILLE + i] != g[(j + 1)*TAILLE + i] || g[j*TAILLE + i] == 0) test = false;
        }
        if (test) {victoire = g[i]; return victoire;}
    }

    // Vérification des diagonales
    int diag[TAILLE];
    int antiDiag[TAILLE];
    for (int i = 0 ; i < TAILLE ; i++){
        diag[i] = g[i + TAILLE*i];
        antiDiag[i] = g[TAILLE - (i+1) + TAILLE*i];
    }
    bool testDiag = true;
    bool testAntiDiag = true;
    for (int i = 0 ; i < TAILLE - 1 ; i++){
        if (diag[i] != diag[i+1] || diag[i] == 0) testDiag = false;
        if (antiDiag[i] != antiDiag [i+1] || antiDiag[i] == 0) testAntiDiag = false;
    }
    if (testDiag) {victoire = diag[0]; return victoire;}
    if (testAntiDiag) {victoire = antiDiag[0] ; return victoire;}

    int i = 0;
    while (i < TAILLE*TAILLE && g[i] != 0) i++;
    if (i == TAILLE*TAILLE) victoire = 3;

    return victoire;
}

int victoire_aux(int g[TAILLE*TAILLE]){
    int victoire = 0;

    // Vérification des lignes
    for (int i = 0 ; i < TAILLE ; i++){
        bool test = true;
        for (int j = 0 ; j < TAILLE - 1 ; j++){
            if (g[i*TAILLE + j] != g[i*TAILLE + j + 1] || g[i*TAILLE + j] == 0) test = false;
        }
        if (test) {victoire = g[i*TAILLE]; return victoire;}
    }

    // Vérification des colonnes
    for (int i = 0 ; i < TAILLE ; i++){
        bool test = true;
        for (int j = 0 ; j < TAILLE - 1 ; j++){
            if (g[j*TAILLE + i] != g[(j + 1)*TAILLE + i] || g[j*TAILLE + i] == 0) test = false;
        }
        if (test) {victoire = g[i]; return victoire;}
    }

    // Vérification des diagonales
    int diag[TAILLE];
    int antiDiag[TAILLE];
    for (int i = 0 ; i < TAILLE ; i++){
        diag[i] = g[i + TAILLE*i];
        antiDiag[i] = g[TAILLE - (i+1) + TAILLE*i];
    }
    bool testDiag = true;
    bool testAntiDiag = true;
    for (int i = 0 ; i < TAILLE - 1 ; i++){
        if (diag[i] != diag[i+1] || diag[i] == 0) testDiag = false;
        if (antiDiag[i] != antiDiag [i+1] || antiDiag[i] == 0) testAntiDiag = false;
    }
    if (testDiag) {victoire = diag[0]; return victoire;}
    if (testAntiDiag) {victoire = antiDiag[0] ; return victoire;}

    int i = 0;
    while (i < TAILLE*TAILLE && g[i] != 0) i++;
    if (i == TAILLE*TAILLE) victoire = 3;

    return victoire;
}

void jouerOrdi(Grille_t* grille){
    // on commence par construire le premier noeud de l'arbre
    noeud_t* racine = malloc(sizeof(noeud_t));
    for (int i = 0 ; i < TAILLE*TAILLE ; i++) racine->etatGrille[i] = grille->grille[i];
    racine->nbFils = 0;
    racine->fils = malloc(TAILLE*TAILLE*sizeof(noeud_t));
    racine->max = true;

    // on construit l'arbre
    construireArbre(racine, false, 0);

    // on met ensuite à jour les valeurs des noeuds
    evaluerArbre(racine);

    // on choisit le meilleur coup
    int max = -2;
    int indiceMax = -1;
    for (int i = 0 ; i < racine->nbFils ; i++){
        if (racine->fils[i]->valeur > max){
            max = racine->fils[i]->valeur;
            indiceMax = i;
        }
    }
    for (int i = 0 ; i < TAILLE*TAILLE ; i++) grille->grille[i] = racine->fils[indiceMax]->etatGrille[i];

    // on libère la mémoire
    detruireArbre(racine);
}

void construireArbre(noeud_t* racine, bool joueur, int profondeur){
    int victoire = victoire_aux(racine->etatGrille);
    if (victoire == 0){
        for (int i = 0 ; i < TAILLE*TAILLE ; i++){
            if (racine->etatGrille[i] == 0){// on crée un fils
                noeud_t* fils = malloc(sizeof(noeud_t));
                if (racine->max) fils->max = false;
                else fils->max = true;
                for (int j = 0 ; j < TAILLE*TAILLE ; j++) fils->etatGrille[j] = racine->etatGrille[j];
                fils->etatGrille[i] = !joueur + 1;
                fils->nbFils = 0;
                fils->fils = malloc((TAILLE*TAILLE - profondeur)*sizeof(noeud_t));

                // on ajoute le fils à la racine
                racine->nbFils++;
                racine->fils[racine->nbFils - 1] = fils;

                // on vérifie si le fils est une feuille
                if (victoire_aux(fils->etatGrille) == 0) construireArbre(fils, !joueur, profondeur + 1);
                else if (victoire_aux(fils->etatGrille) == 1) fils->valeur = -1;
                else if (victoire_aux(fils->etatGrille) == 2) fils->valeur = 1;
                else fils->valeur = 0;
            }
        }
    } else if (victoire == 1){
        racine->valeur = -1;
    } else if (victoire == 2){
        racine->valeur = 1;
    } else {
        racine->valeur = 0;
    }
}

void detruireArbre(noeud_t* noeud){
    if (noeud->nbFils > 0){
        for (int i = 0 ; i < noeud->nbFils ; i++){
            detruireArbre(noeud->fils[i]);
        }
    }
    free(noeud->fils);
    free(noeud);
}

bool estFeuille(noeud_t* noeud){
    return noeud->nbFils == 0;
}

void evaluerArbre(noeud_t* racine){
    if (!estFeuille(racine)) {
        for (int i = 0 ; i < racine->nbFils ; i++){
            evaluerArbre(racine->fils[i]);
        }
        if (racine->max){
            int max = -999;
            for (int i = 0 ; i < racine->nbFils ; i++){
                if (racine->fils[i]->valeur > max) max = racine->fils[i]->valeur;
            }
            racine->valeur = max;
        } else {
            int min = 999;
            for (int i = 0 ; i < racine->nbFils ; i++){
                if (racine->fils[i]->valeur < min) min = racine->fils[i]->valeur;
            }
            racine->valeur = min;
        }
    }
}

void afficherArbre(noeud_t* racine, int profondeur){
    if (!estFeuille(racine)){
        for (int i = 0 ; i < racine->nbFils ; i++){
            afficherArbre(racine->fils[i], profondeur + 1);
        }
    }
    printf("Profondeur : %d - Valeur : %d -", profondeur, racine->valeur);
    for (int i = 0 ; i < TAILLE*TAILLE ; i++) printf(" %d ", racine->etatGrille[i]);
    printf("\n");
}

char* creerCle(int grille[TAILLE*TAILLE]){
    char* str = malloc((TAILLE*TAILLE + 1)*sizeof(char));
    for (int i = 0 ; i < TAILLE*TAILLE ; i++){
        str[i] = '0' + grille[i];
    }
    str[TAILLE*TAILLE] = '\0';
    return str;
}

unsigned int hash(char* cle, int tailleTable) {
    unsigned long hash = 5381;
    int c;
    while ((c = *cle++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % tailleTable;
}

table_t* initTable(int taille) {
    table_t* table = malloc(sizeof(table_t));
    table->taille = taille;
    table->nbElements = 0;
    table->elements = malloc(taille * sizeof(hache_t*));

    for (int i = 0; i < taille; i++) {
        table->elements[i] = NULL;
    }

    return table;
}

void ajouterElement(table_t* table, char* cle, noeud_t* noeud) {
    if ( (float) table->nbElements / table->taille > 0.7 ) {
        int index = hash(cle, table->taille);
        hache_t* nouvelElement = malloc(sizeof(hache_t));
        nouvelElement->cle = strdup(cle); // Duplique la clé
        free(cle);
        nouvelElement->noeud = noeud;

        // Gestion des collisions
        nouvelElement->suivant = table->elements[index];
        table->elements[index] = nouvelElement;
        table->nbElements++;
    } else {
        redimensionnerTable(table, table->taille * 2);
        ajouterElement(table, cle, noeud);
    }
}

void redimensionnerTable(table_t* table, int nouvelleTaille) {
    hache_t** elements = table->elements;
    int taille = table->taille;

    table->elements = malloc(nouvelleTaille * sizeof(hache_t*));
    table->taille = nouvelleTaille;
    table->nbElements = 0;

    for (int i = 0; i < nouvelleTaille; i++) {
        table->elements[i] = NULL;
    }

    for (int i = 0; i < taille; i++) {
        hache_t* element = elements[i];
        while (element != NULL) {
            ajouterElement(table, element->cle, element->noeud);
            hache_t* suivant = element->suivant;
            free(element);
            element = suivant;
        }
    }

    free(elements);
}

bool existe(table_t* table, char* cle) {
    int index = hash(cle, table->taille);
    hache_t* element = table->elements[index];

    while (element != NULL) {
        if (strcmp(element->cle, cle) == 0) {
            return true; // Clé trouvée
        }
        element = element->suivant;
    }
    return false; // Clé non trouvée
}

void supprimerTable(table_t* table) {
    for (int i = 0; i < table->taille; i++) {
        hache_t* element = table->elements[i];
        while (element != NULL) {
            hache_t* suivant = element->suivant;
            free(element->cle);
            free(element);
            element = suivant;
        }
    }
    free(table->elements);
    free(table);
}

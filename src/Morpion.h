#ifndef __MORPION_H__
#define __MORPION_H__

#define TAILLE 4

typedef struct {
    int grille[TAILLE*TAILLE];
    char* nomJ1;
    char* nomJ2;
    int scoreJ1;
    int scoreJ2;
} Grille_t;

typedef struct noeud_t noeud_t;

struct noeud_t{
    int valeur;
    int etatGrille[TAILLE*TAILLE];
    int nbFils;
    bool max; // true si c'est un noeud max, false sinon
    noeud_t** fils;
};

extern Grille_t* initGrille();
extern void affichageGrille(Grille_t* grille);
extern bool jouer(Grille_t* grille, int i, int j, bool joueur);
extern int victoire(Grille_t* grille);
extern void jouerOrdi(Grille_t* grille);
extern void construireArbre(noeud_t* noeud, bool joueur);
extern void detruireArbre(noeud_t* noeud);
extern bool estFeuille(noeud_t* noeud);
extern void evaluerArbre(noeud_t* racine);
extern void afficherArbre(noeud_t* racine, int profondeur);

#endif

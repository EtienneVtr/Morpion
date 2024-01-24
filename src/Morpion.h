#ifndef __MORPION_H__
#define __MORPION_H__

#define TAILLE 3

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

typedef struct hache_t hache_t;

struct hache_t{
    noeud_t* noeud;
    char* cle;
    hache_t* suivant;
};

typedef struct table_t{
    int taille;
    int nbElements;
    hache_t** elements;
} table_t;

extern Grille_t* initGrille();
extern void affichageGrille(Grille_t* grille);
extern bool jouer(Grille_t* grille, int i, int j, bool joueur);
extern int victoire(Grille_t* grille);
extern void jouerOrdi(Grille_t* grille);
extern void construireArbre(noeud_t* noeud, bool joueur, int profondeur, table_t* table);
extern bool estFeuille(noeud_t* noeud);
extern void evaluerArbre(noeud_t* racine);
extern void afficherArbre(noeud_t* racine, int profondeur);
extern char* creerCle(int grille[TAILLE*TAILLE]);
extern unsigned int hash(char* cle, int tailleTable);
extern table_t* initTable(int taille);
extern void ajouterElement(table_t* table, char* cle, noeud_t* noeud);
extern void redimensionnerTable(table_t* table, int nouvelleTaille);
extern bool existe(table_t* table, char* cle);
extern noeud_t* trouve(table_t* table, char* cle);
extern void supprimerTable(table_t* table);
extern bool estPremier(int n);
extern int premierPremier(int n);
extern bool grillesEgales(int grille1[TAILLE*TAILLE], int grille2[TAILLE*TAILLE]);

#endif

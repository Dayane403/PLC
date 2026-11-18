#ifndef CARTE_H
#define CARTE_H

#include "perso.h"

#define CARTE_LARGEUR_MAX 40
#define CARTE_HAUTEUR_MAX 20

/* Symboles : # mur, . sol, H herbe (combat sauvage), D dresseur, Z zone a niveau minimum */
typedef struct {
    char grille[CARTE_HAUTEUR_MAX][CARTE_LARGEUR_MAX + 1];
    int largeur;
    int hauteur;
    int niveau_min_zone;
} Carte;

typedef enum {
    MOVE_OK,
    MOVE_BLOQUE,
    MOVE_NIVEAU_INSUFFISANT,
    MOVE_COMBAT_SAUVAGE,
    MOVE_COMBAT_DRESSEUR
} ResultatMove;

/* Fichier : "largeur hauteur niveau_min" puis la grille. Retourne 1 si OK */
int carte_charger(Carte *carte, const char *chemin);
void carte_afficher(const Carte *carte, int x, int y);
int perso_niveau_max(const Perso *perso);

/* dir : z haut, s bas, q gauche, d droite */
ResultatMove carte_deplacer(const Carte *carte, const Perso *perso, int *x, int *y, char dir);

#endif

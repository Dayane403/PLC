#include <stdio.h>
#include <string.h>
#include "carte.h"

int carte_charger(Carte *carte, const char *chemin) {
    FILE *f = fopen(chemin, "r");
    if (f == NULL) return 0;

    memset(carte, 0, sizeof(Carte));
    if (fscanf(f, "%d %d %d", &carte->largeur, &carte->hauteur, &carte->niveau_min_zone) != 3
        || carte->largeur <= 0 || carte->largeur > CARTE_LARGEUR_MAX
        || carte->hauteur <= 0 || carte->hauteur > CARTE_HAUTEUR_MAX) {
        fclose(f);
        return 0;
    }

    for (int y = 0; y < carte->hauteur; y++) {
        char ligne[CARTE_LARGEUR_MAX + 2];
        if (fscanf(f, "%41s", ligne) != 1 || (int)strlen(ligne) != carte->largeur) {
            fclose(f);
            return 0;
        }
        strcpy(carte->grille[y], ligne);
    }
    fclose(f);
    return 1;
}

void carte_afficher(const Carte *carte, int x, int y) {
    for (int j = 0; j < carte->hauteur; j++) {
        for (int i = 0; i < carte->largeur; i++)
            putchar((i == x && j == y) ? '@' : carte->grille[j][i]);
        putchar('\n');
    }
}

int perso_niveau_max(const Perso *perso) {
    int max = 0;
    for (int i = 0; i < perso->nb_creature_equipe; i++)
        if (perso->equipe_creature[i].niveau > max)
            max = perso->equipe_creature[i].niveau;
    return max;
}

ResultatMove carte_deplacer(const Carte *carte, const Perso *perso, int *x, int *y, char dir) {
    int nx = *x, ny = *y;
    switch (dir) {
        case 'z': ny--; break;
        case 's': ny++; break;
        case 'q': nx--; break;
        case 'd': nx++; break;
        default: return MOVE_BLOQUE;
    }

    if (nx < 0 || ny < 0 || nx >= carte->largeur || ny >= carte->hauteur)
        return MOVE_BLOQUE;

    char bloc = carte->grille[ny][nx];
    if (bloc == '#') return MOVE_BLOQUE;
    if (bloc == 'Z' && perso_niveau_max(perso) < carte->niveau_min_zone)
        return MOVE_NIVEAU_INSUFFISANT;

    *x = nx;
    *y = ny;
    if (bloc == 'H') return MOVE_COMBAT_SAUVAGE;
    if (bloc == 'D') return MOVE_COMBAT_DRESSEUR;
    return MOVE_OK;
}

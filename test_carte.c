#include <stdio.h>
#include <assert.h>
#include "carte.h"

int main(void) {
    Carte carte;
    Perso joueur;
    Creature c;
    int x = 1, y = 1;

    assert(carte_charger(&carte, "carte1.txt"));
    assert(carte.largeur == 12 && carte.hauteur == 7 && carte.niveau_min_zone == 5);

    CreerPerso(&joueur, "Rayan");
    creer_flamby(&c);
    AddCreatureToTeam(&joueur, &c);

    carte_afficher(&carte, x, y);

    assert(carte_deplacer(&carte, &joueur, &x, &y, 'z') == MOVE_BLOQUE);
    assert(carte_deplacer(&carte, &joueur, &x, &y, 'd') == MOVE_OK);
    assert(carte_deplacer(&carte, &joueur, &x, &y, 'd') == MOVE_COMBAT_SAUVAGE);

    x = 9; y = 1;
    assert(carte_deplacer(&carte, &joueur, &x, &y, 'd') == MOVE_NIVEAU_INSUFFISANT);
    assert(x == 9);

    joueur.equipe_creature[0].niveau = 5;
    assert(carte_deplacer(&carte, &joueur, &x, &y, 'd') == MOVE_OK);
    assert(x == 10);

    x = 7; y = 1;
    assert(carte_deplacer(&carte, &joueur, &x, &y, 'd') == MOVE_COMBAT_DRESSEUR);

    printf("\nTous les tests passent.\n");
    return 0;
}

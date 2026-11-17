#include <stdio.h>
#include <string.h>
#include "perso.h"

void CreerPerso(Perso * perso, const char * nom) {
    memset(perso, 0, sizeof(Perso));
    snprintf(perso->nom, TAILLE_NOM_PERSO, "%s", nom);
}


int AddCreatureToTeam(Perso * perso, const Creature * creature) {
    if(creature == NULL || perso == NULL) {
        return 0;
    }

    if(perso->nb_creature_equipe == NB_CREATURE_MAX) {
        printf("%s ne peut pas être ajouté.\nEquipe de %s pleine.\n", creature->nom, perso->nom);
        return 0;
    }

    perso->equipe_creature[perso->nb_creature_equipe] = *creature;
    perso->nb_creature_equipe++;
    printf("%s a été ajouté.\nEquipe de %s : %d/%d.\n",
    creature->nom, perso->nom, perso->nb_creature_equipe, NB_CREATURE_MAX);
    return 1;
}

int AddCreatureToStockage(Perso * perso, const Creature * creature) {
    if(creature == NULL || perso == NULL) {
        return 0;
    }
    else {
        if(perso->nb_creature_stockage == NB_CREATURE_STOCKAGE_MAX) {
        printf("%s ne peut pas être ajouter au stockage de %s.\nCapacité du stockage %d/%d\n", 
            creature->nom, perso->nom, perso->nb_creature_stockage, NB_CREATURE_STOCKAGE_MAX);
        return 0;
    }
    else {
        perso->stockage_creature[perso->nb_creature_stockage] = *creature;
        perso->nb_creature_stockage++;
        printf("%s a été ajouter au stockage de %s.\nCapacité du stockage %d/%d\n", 
            creature->nom, perso->nom, perso->nb_creature_stockage, NB_CREATURE_STOCKAGE_MAX);
        return 1;
    }
    }
}

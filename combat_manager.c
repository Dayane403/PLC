#include <stdio.h>
#include <string.h>
#include "combat_manager.h"

Combat * CreerCombat(Perso * perso1, Perso * perso2, TypeCombat type_combat) {
    if(perso1 == NULL || (perso2 == NULL && type_combat == COMBAT_DRESSEUR)) {
        printf("Erreur avec un des deux perso...");
        return NULL;
    }

    Combat newcombat;
    newcombat.type = type_combat;
    newcombat.nb_round = 0;
    newcombat.joueur1 = perso1;
    newcombat.current_creature_joueur1 = GetCreatureReady(perso1);
    newcombat.joueur2 = perso2;
    newcombat.current_creature_joueur2 = GetCreatureReady(perso2);
    return &newcombat;
}

Creature * GetCreatureReady(Perso * perso) {
    if(perso == NULL) {
        printf("Erreur avec le perso...\n");
        return NULL;
    }
    int i = 0;
    while(EstKO(&perso->equipe_creature[i]) == 1){
        if(i > perso->nb_creature_equipe) {
            printf("aucune creature n'est disponible pour le combat");
            return NULL;
        }
        i++;
    }
    return &perso->equipe_creature[i];
}

void InfligerDegats(Creature * cible, int degats) {
    if(cible == NULL) {
        printf("Erreur, cible introuvable...\n");
        return;
    }
    if(degats <= 0) {
        printf("L'attaque n'a pas fait de dégats.\n");
        return;
    }
    cible->pv -= degats;
    if(cible->pv < 0) {
        cible->pv = 0;
        return;
    }
}

int EstKO(const Creature * creature) {
    if(creature == NULL) {
        printf("Erreur, cible introuvable...\n");
        return 1;
    }
    return (creature->pv <= 0);
}
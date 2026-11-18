#include <stdio.h>
#include <string.h>
#include "combat_manager.h"

int CreerCombat(Combat * combat, Perso * perso1, Perso * perso2,
                Creature * creature_sauvage, TypeCombat type_combat) {
    if(combat == NULL || perso1 == NULL) {
        printf("Erreur avec le combat ou le joueur...\n");
        return 0;
    }
    if(type_combat == COMBAT_DRESSEUR && perso2 == NULL) {
        printf("Erreur : un combat de dresseur a besoin de deux perso.\n");
        return 0;
    }
    if(type_combat == COMBAT_SAUVAGE && creature_sauvage == NULL) {
        printf("Erreur : un combat sauvage a besoin d'une creature sauvage.\n");
        return 0;
    }

    combat->type = type_combat;
    combat->nb_round = 0;
    combat->joueur1 = perso1;
    combat->current_creature_joueur1 = GetCreatureReady(perso1);

    if(type_combat == COMBAT_SAUVAGE) {
        combat->joueur2 = NULL;
        combat->current_creature_joueur2 = creature_sauvage;
    }
    else {
        combat->joueur2 = perso2;
        combat->current_creature_joueur2 = GetCreatureReady(perso2);
    }

    if(combat->current_creature_joueur1 == NULL || combat->current_creature_joueur2 == NULL) {
        printf("Erreur : un des deux camps n'a aucune creature en etat de se battre.\n");
        return 0;
    }
    return 1;
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
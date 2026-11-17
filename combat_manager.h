#ifndef COMBAT_MANAGER_H
#define COMBAT_MANAGER_H


typedef enum TypeCombat TypeCombat;
enum TypeCombat {
    COMBAT_SAUVAGE,
    COMBAT_DRESSEUR
};

typedef enum RoundAction RoundAction;
enum RoundAction {
    CREATURE_ATK,
    CREATURE_SWITCH,
    LEAVE_FIGHT,
    CREATURE_RECRUIT
};

typedef struct Combat Combat;
struct Combat {
    TypeCombat type;
    int nb_round;
    /*Perso * joueur;
    Creature * current_creature_joueur1;
    Perso * joueur2;
    Creature * current_creature_joueur2;*/
    
};

void CreatureAttaque(Combat current_combat);
void CreatureSwitch(Combat current_combat);
void LeaveFight(Combat current_combat);
void CreatureRecruit(Combat current_combat);

void ChoseAttaque(/*Perso perso*/);
void ChoseNextCreature(/*Perso perso*/);

#endif
#ifndef PERSO_H
#define PERSO_H
#include "creature.h"

#define NB_CREATURE_MAX 8
#define NB_CREATURE_STOCKAGE_MAX 100
#define TAILLE_NOM_PERSO 30


typedef struct Perso Perso;
struct Perso {
  Creature equipe_creature[NB_CREATURE_MAX];
  int nb_creature_equipe;
  Creature stockage_creature[NB_CREATURE_STOCKAGE_MAX];
  int nb_creature_stockage;
  char nom[TAILLE_NOM_PERSO];
};

void CreerPerso(Perso * perso, const char * nom);
int AddCreatureToTeam(Perso * perso, const Creature * creature);
int AddCreatureToStockage(Perso * perso, const Creature * creature);

#endif
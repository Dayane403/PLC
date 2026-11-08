#ifndef CAPACITE_H
#define CAPACITE_H

struct Creature;

typedef struct Capacite
{
    char nom[30];
    char description[100];
    void (*effet)(struct Creature *attaquant, struct Creature *cible);
} Capacite;

const Capacite *trouver_capacite(const char *nom);

#endif
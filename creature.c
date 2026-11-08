#include <stdio.h>
#include <string.h>
#include "creature.h"

const char *nom_du_type(TypeCreature type)
{
    switch (type)
    {
    case TYPE_FEU:
        return "Feu";
    case TYPE_EAU:
        return "Eau";
    case TYPE_PLANTE:
        return "Plante";
    case TYPE_ELECTRIQUE:
        return "Electrique";
    }
    return "Inconnu";
}

void creer_creature(Creature *c, const char *nom, TypeCreature type,
                    int pv, int attaque, int defense,
                    char symbole, const char *dessin)
{
    memset(c, 0, sizeof(Creature));
    snprintf(c->nom, TAILLE_NOM, "%s", nom);
    c->type = type;
    c->niveau = 1;
    c->xp = 0;
    c->pv = pv;
    c->pv_max = pv;
    c->attaque = attaque;
    c->defense = defense;
    c->symbole = symbole;
    snprintf(c->dessin_combat, TAILLE_DESSIN, "%s", dessin);
}

void afficher_creature(const Creature *c)
{
    int i;
    printf("=== %s (%s) ===\n", c->nom, nom_du_type(c->type));
    printf("Niveau : %d   XP : %d\n", c->niveau, c->xp);
    printf("PV : %d/%d   Attaque : %d   Defense : %d\n",
           c->pv, c->pv_max, c->attaque, c->defense);
    printf("Symbole sur la carte : %c\n", c->symbole);
    printf("Capacites :");
    if (c->nb_capacites == 0)
        printf(" aucune");
    for (i = 0; i < c->nb_capacites; i++)
        printf(" [%s]", c->capacites[i]);
    printf("\n");
}

void afficher_dessin_combat(const Creature *c)
{
    printf("%s", c->dessin_combat);
}

void ajouter_apprentissage(Creature *c, int niveau, const char *nom_capacite)
{
    if (c->nb_apprentissages >= NB_APPRENTISSAGES_MAX)
    {
        printf("Table d'apprentissage pleine pour %s\n", c->nom);
        return;
    }
    c->apprentissages[c->nb_apprentissages].niveau = niveau;
    snprintf(c->apprentissages[c->nb_apprentissages].nom_capacite,
             TAILLE_NOM, "%s", nom_capacite);
    c->nb_apprentissages++;
}

void apprendre_capacite(Creature *c, const char *nom_capacite)
{
    int i;

    for (i = 0; i < c->nb_capacites; i++)
    {
        if (strcmp(c->capacites[i], nom_capacite) == 0)
            return;
    }
    if (c->nb_capacites >= NB_CAPACITES_MAX)
    {
        printf("%s ne peut plus apprendre de capacite (%d max)\n",
               c->nom, NB_CAPACITES_MAX);
        return;
    }
    snprintf(c->capacites[c->nb_capacites], TAILLE_NOM, "%s", nom_capacite);
    c->nb_capacites++;
    printf("%s apprend %s !\n", c->nom, nom_capacite);
}

void verifier_apprentissages(Creature *c)
{
    int i;

    for (i = 0; i < c->nb_apprentissages; i++)
    {
        if (c->apprentissages[i].niveau == c->niveau)
            apprendre_capacite(c, c->apprentissages[i].nom_capacite);
    }
}

void creer_flamby(Creature *c)
{
    creer_creature(c, "Flamby", TYPE_FEU, 40, 12, 8, 'F',
                   "    ( )\n"
                   "   (   )\n"
                   "  ( o o )\n"
                   "   (  v )\n"
                   "    ~~~\n");
    ajouter_apprentissage(c, 1, "Charge");
    ajouter_apprentissage(c, 5, "Flammeche");
    ajouter_apprentissage(c, 10, "Lance-flammes");
    verifier_apprentissages(c);
}

void creer_aquali(Creature *c)
{
    creer_creature(c, "Aquali", TYPE_EAU, 45, 10, 10, 'A',
                   "    ___\n"
                   "   (o o)\n"
                   "  ~(   )~\n"
                   "   ~~~~~\n");
    ajouter_apprentissage(c, 1, "Charge");
    ajouter_apprentissage(c, 5, "Pistolet a eau");
    ajouter_apprentissage(c, 10, "Hydrocanon");
    verifier_apprentissages(c);
}

void creer_feuillu(Creature *c)
{
    creer_creature(c, "Feuillu", TYPE_PLANTE, 50, 9, 12, 'P',
                   "    &&&\n"
                   "   &&&&&\n"
                   "   (o.o)\n"
                   "    |_|\n");
    ajouter_apprentissage(c, 1, "Charge");
    ajouter_apprentissage(c, 5, "Fouet lianes");
    ajouter_apprentissage(c, 10, "Tempete de feuilles");
    verifier_apprentissages(c);
}
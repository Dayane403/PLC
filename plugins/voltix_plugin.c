#include <stdio.h>
#include <string.h>
#include "../creature.h"

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

static void ajouter_appr(Creature *c, int niveau, const char *nom)
{
    c->apprentissages[c->nb_apprentissages].niveau = niveau;
    snprintf(c->apprentissages[c->nb_apprentissages].nom_capacite,
             TAILLE_NOM, "%s", nom);
    c->nb_apprentissages++;
}

EXPORT void charger_creature(Creature *c)
{
    memset(c, 0, sizeof(Creature));
    snprintf(c->nom, TAILLE_NOM, "%s", "Voltix");
    c->type = TYPE_ELECTRIQUE;
    c->niveau = 1;
    c->pv = 35;
    c->pv_max = 35;
    c->attaque = 14;
    c->defense = 6;
    c->symbole = 'V';
    snprintf(c->dessin_combat, TAILLE_DESSIN, "%s",
             "   /\\_/\\\n"
             "  ( ^.^ )\n"
             "   > Z <\n"
             "   /___\\\n");

    ajouter_appr(c, 1, "Charge");
    ajouter_appr(c, 5, "Eclair");
    ajouter_appr(c, 10, "Foudre");

    snprintf(c->capacites[0], TAILLE_NOM, "%s", "Charge");
    c->nb_capacites = 1;
}
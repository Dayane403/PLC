#include <stdio.h>
#include "creature.h"
#include "plugin_loader.h"

#ifdef _WIN32
#define CHEMIN_PLUGIN "plugins/voltix.dll"
#else
#define CHEMIN_PLUGIN "plugins/voltix.so"
#endif

int main(void)
{
    Creature flamby, aquali, feuillu, voltix;

    printf("----- Creatures codees en dur -----\n");
    creer_flamby(&flamby);
    creer_aquali(&aquali);
    creer_feuillu(&feuillu);

    afficher_creature(&flamby);
    afficher_dessin_combat(&flamby);
    printf("\n");
    afficher_creature(&aquali);
    afficher_dessin_combat(&aquali);
    printf("\n");
    afficher_creature(&feuillu);
    afficher_dessin_combat(&feuillu);

    printf("\n----- Test de l'apprentissage -----\n");
    while (flamby.niveau < 5)
    {
        flamby.niveau++;
        verifier_apprentissages(&flamby);
    }
    afficher_creature(&flamby);

    printf("\n----- Test du plugin -----\n");
    if (charger_plugin_creature(CHEMIN_PLUGIN, &voltix))
    {
        afficher_creature(&voltix);
        afficher_dessin_combat(&voltix);
    }

    return 0;
}
#ifndef CREATURE_H
#define CREATURE_H

#define TAILLE_NOM 30
#define TAILLE_DESSIN 400
#define NB_CAPACITES_MAX 4
#define NB_APPRENTISSAGES_MAX 10

typedef enum
{
    TYPE_FEU,
    TYPE_EAU,
    TYPE_PLANTE,
    TYPE_ELECTRIQUE
} TypeCreature;

typedef struct
{
    int niveau;
    char nom_capacite[TAILLE_NOM];
} Apprentissage;

typedef struct
{
    char nom[TAILLE_NOM];
    TypeCreature type;

    int niveau;
    int xp;
    int pv;
    int pv_max;
    int attaque;
    int defense;

    char dessin_combat[TAILLE_DESSIN];
    char symbole;

    char capacites[NB_CAPACITES_MAX][TAILLE_NOM];
    int nb_capacites;

    Apprentissage apprentissages[NB_APPRENTISSAGES_MAX];
    int nb_apprentissages;
} Creature;

void creer_creature(Creature *c, const char *nom, TypeCreature type,
                    int pv, int attaque, int defense,
                    char symbole, const char *dessin);
void afficher_creature(const Creature *c);
void afficher_dessin_combat(const Creature *c);
const char *nom_du_type(TypeCreature type);

void ajouter_apprentissage(Creature *c, int niveau, const char *nom_capacite);
void apprendre_capacite(Creature *c, const char *nom_capacite);
void verifier_apprentissages(Creature *c);

void creer_flamby(Creature *c);
void creer_aquali(Creature *c);
void creer_feuillu(Creature *c);

#endif
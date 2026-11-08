#include <stdio.h>
#include "plugin_loader.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

int charger_plugin_creature(const char *chemin, Creature *c)
{
    void (*fonction)(Creature *);

#ifdef _WIN32
    HMODULE lib = LoadLibraryA(chemin);
    if (lib == NULL)
    {
        printf("Erreur : impossible de charger %s\n", chemin);
        return 0;
    }
    fonction = (void (*)(Creature *))GetProcAddress(lib, "charger_creature");
#else
    void *lib = dlopen(chemin, RTLD_NOW);
    if (lib == NULL)
    {
        printf("Erreur : %s\n", dlerror());
        return 0;
    }
    fonction = (void (*)(Creature *))dlsym(lib, "charger_creature");
#endif

    if (fonction == NULL)
    {
        printf("Erreur : charger_creature introuvable dans %s\n", chemin);
        return 0;
    }

    fonction(c);

#ifdef _WIN32
    FreeLibrary(lib);
#else
    dlclose(lib);
#endif
    return 1;
}
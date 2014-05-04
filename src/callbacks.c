#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "callbacks.h"
#include "pokemon.h"

// plist is actually a GSList** to save the new pointer to the list
int callbackIdFromName(void *plist, int argc, char **argv, char **azColName){

    GSList** pokeList = (GSList**) plist;
	POKEMON* pokemon = NULL;

	pokemon = pokeCreate();

    pokemon->id = atoi(argv[0]);
    pokemon->realId = atoi(argv[1]);
	pokemon->name = strdup(argv[2]);
	pokemon->identifier = strdup(argv[3]);

	fixMegaName(pokemon);

	*pokeList = g_slist_prepend(*pokeList, pokemon);

	return 0;

}

int callbackTypesFromId(void *pokemon, int argc, char **argv, char **azColName){

	POKEMON* poke = (POKEMON*) pokemon;

	poke->types[atoi(argv[1]) - 1] = strdup(argv[0]);

	return 0;

}

int callbackTypesFromName(void *param, int argc, char **argv, char **azColName){

    PARAM* parameters = (PARAM *) param;
    POKEMON* pokemon = NULL;

    pokemon = (POKEMON *) g_slist_nth_data(parameters->pokeList, parameters->current);

    if(pokemon->id != atoi(argv[2]))
        pokemon = (POKEMON *) g_slist_nth_data(parameters->pokeList, ++(parameters->current));

    pokemon->types[atoi(argv[1]) - 1] = strdup(argv[0]);

    return 0;
}

int callbackAbilitiesFromId(void *pokemon, int argc, char **argv, char **azColName){

	POKEMON* poke = (POKEMON*) pokemon;

    poke->abilities[atoi(argv[1]) - 1] = strdup(argv[0]);

	return 0;
}

int callbackAbilitiesFromName(void *param, int argc, char **argv, char **azColName){

    PARAM* parameters = (PARAM *) param;
    POKEMON* pokemon = NULL;

    pokemon = (POKEMON *) g_slist_nth_data(parameters->pokeList, parameters->current);

    if(pokemon->id != atoi(argv[2]))
        pokemon = (POKEMON *) g_slist_nth_data(parameters->pokeList, ++(parameters->current));

    pokemon->abilities[atoi(argv[1]) - 1] = strdup(argv[0]);

    return 0;
}

int callbackStatsFromId(void *pokemon, int argc, char **argv, char **azColName){

    POKEMON* poke = (POKEMON*) pokemon;

    poke->stats[atoi(argv[1]) - 1] = atoi(argv[0]);

	return 0;
}

int callbackStatsFromName(void *param, int argc, char **argv, char **azColName){

    PARAM* parameters = (PARAM *) param;
    POKEMON* pokemon = NULL;

    pokemon = (POKEMON *) g_slist_nth_data(parameters->pokeList, parameters->current);

    if(pokemon->id != atoi(argv[2]))
        pokemon = (POKEMON *) g_slist_nth_data(parameters->pokeList, ++(parameters->current));

    pokemon->stats[atoi(argv[1]) - 1] = atoi(argv[0]);

    return 0;
}

int callbackEggsFromId(void *pokemon, int argc, char **argv, char **azColName){

    POKEMON* poke = (POKEMON*) pokemon;

    if(poke->eggGroups[0] == NULL)
        poke->eggGroups[0] = strdup(argv[0]);
    else
        poke->eggGroups[1] = strdup(argv[0]);

	return 0;
}

int callbackLangIdFromName(void *id, int argc, char **argv, char **azColName){

    int* retValue = (int*) id;

    *retValue = atoi(argv[0]);

    return 0;
}

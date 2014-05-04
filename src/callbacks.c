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

int callbackAbilitiesFromId(void *pokemon, int argc, char **argv, char **azColName){

	POKEMON* poke = (POKEMON*) pokemon;

    poke->abilities[atoi(argv[1]) - 1] = strdup(argv[0]);

	return 0;
}

int callbackStatsFromId(void *pokemon, int argc, char **argv, char **azColName){

    POKEMON* poke = (POKEMON*) pokemon;

    poke->stats[atoi(argv[1]) - 1] = atoi(argv[0]);

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

int callbackGenderRatesFromId(void *pokemon, int argc, char **argv, char **azColName){

    POKEMON* poke = (POKEMON*) pokemon;

    poke->genderRates[0] = atof(argv[0]);
    poke->genderRates[1] = atof(argv[1]);

	return 0;
}

int callbackLangIdFromName(void *id, int argc, char **argv, char **azColName){

    int* retValue = (int*) id;

    *retValue = atoi(argv[0]);

    return 0;
}

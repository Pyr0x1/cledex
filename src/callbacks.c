#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "callbacks.h"
#include "pokemon.h"

int callbackIdFromName(void *pokemon, int argc, char **argv, char **azColName){

	POKEMON* poke = (POKEMON *) pokemon;

	/*int i;

	for(i = 0; i < argc; i++)
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

	printf("\n");*/

    poke->id = atoi(argv[0]);
    poke->realId = atoi(argv[1]);
	poke->name = strdup(argv[2]);

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

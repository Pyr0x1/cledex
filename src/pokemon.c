#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sqlite3.h>
#include "pokemon.h"
#include "colors.h"
#include "queries.h"
#include "callbacks.h"

POKEMON* pokeCreate(){

	POKEMON *pokemon = NULL;

	pokemon = calloc(1, sizeof(POKEMON));

	pokemon->name = NULL;
	pokemon->types[0] = NULL;
	pokemon->types[1] = NULL;
	pokemon->abilities[0] = NULL;
	pokemon->abilities[1] = NULL;
	pokemon->abilities[2] = NULL;
	pokemon->eggGroups[0] = NULL;
	pokemon->eggGroups[1] = NULL;

	return pokemon;
}

GSList* pokeListInit(sqlite3* db, char name[]){

    char* zErrMsg = NULL;
    int retCode;
    char* query = NULL;
    GSList* pokeList = NULL;

    query = QPokeIdFromName(name);

    retCode = sqlite3_exec(db, query, callbackIdFromName, &pokeList, &zErrMsg);
    free(query);
	if(retCode != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		g_slist_free_full(pokeList, (GDestroyNotify) freePoke);
		sqlite3_close(db);
		return NULL;
	}
	if(g_slist_length(pokeList) == 0){
        fprintf(stderr, "Entry not found, make sure the name is correct.\n");

		return NULL;
	}

	pokeList = g_slist_reverse(pokeList);

    return pokeList;
}

void pokePrint(POKEMON* pokemon){

    printf("\n");
    printf("--------------------\n\n");
	printf("\t[%d]\t%s\t\t", pokemon->realId, pokemon->name);
	printf("%s", pokemon->types[0]);

	if(pokemon->types[1] != NULL)
        printf(" / %s", pokemon->types[1]);
    printf("\n\n");

    if(pokemon->abilities[0] != NULL)
        printf("\t\t%s\n", pokemon->abilities[0]);

    if(pokemon->abilities[1] != NULL)
        printf("\t\t%s\n", pokemon->abilities[1]);

    if(pokemon->abilities[2] != NULL)
        printf("\t\t%s (HA)\n", pokemon->abilities[2]);

    printf("\n");

    printf(KRED "\t\tPS: %d\n" KNRM, pokemon->stats[0]);
    printf(KBLU "\t\tAtk: %d\n" KNRM, pokemon->stats[1]);
    printf(KYEL "\t\tDef: %d\n" KNRM, pokemon->stats[2]);
	printf(KCYN "\t\tSpAtk: %d\n" KNRM, pokemon->stats[3]);
	printf(KGRN "\t\tSpDef: %d\n" KNRM, pokemon->stats[4]);
    printf(KMAG "\t\tSpeed: %d\n" KNRM, pokemon->stats[5]);

    printf("\n");

	if(pokemon->eggGroups[0] != NULL)
        printf("\t\t%s\n", pokemon->eggGroups[0]);

    if(pokemon->eggGroups[1] != NULL)
        printf("\t\t%s\n", pokemon->eggGroups[1]);

	return ;
}

void convertLineToSpace(char* str){

    int i;

    str[0] = toupper(str[0]);

    for(i = 0; i < strlen(str); i++){
        if(str[i] == '-'){
            str[i] = ' ';
            if(str[i + 1] != '\0')
                str[i + 1] = toupper(str[i + 1]);
        }
    }

    if(strcmp(str, "Ho Oh") == 0) // handle Ho-Oh case that needs line instead of space
        sprintf(str, "%s", "Ho-Oh");

    return ;
}

void convertSpaceToLine(char* str){

    int i;

    str[0] = tolower(str[0]);

    for(i = 0; i < strlen(str); i++){
        if(str[i] == ' ')
            str[i] = '-';
        else
            str[i] = tolower(str[i]);
    }

    return ;
}

void convertAllStrings(POKEMON* pokemon){

    convertLineToSpace(pokemon->name);

    if(pokemon->abilities[0] != NULL)
        convertLineToSpace(pokemon->abilities[0]);

    if(pokemon->abilities[1] != NULL)
        convertLineToSpace(pokemon->abilities[1]);

    if(pokemon->abilities[2] != NULL)
        convertLineToSpace(pokemon->abilities[2]);

    if(pokemon->eggGroups[0] != NULL)
        convertLineToSpace(pokemon->eggGroups[0]);

    if(pokemon->eggGroups[1] != NULL)
        convertLineToSpace(pokemon->eggGroups[1]);

    return ;
}

int getPokeTypes(POKEMON* pokemon, gpointer sqldb){

    sqlite3* db = (sqlite3*) sqldb;
    char* query = NULL;
    char* zErrMsg = NULL;
    int retCode;

    query = QPokeTypesFromId(pokemon->id);

    retCode = sqlite3_exec(db, query, callbackTypesFromId, pokemon, &zErrMsg);
    free(query);
	if(retCode != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
        return EXIT_FAILURE;
	}

    return EXIT_SUCCESS;
}

int getPokeAbilities(POKEMON* pokemon, gpointer sqldb){

    sqlite3* db = (sqlite3*) sqldb;
    char* query = NULL;
    char* zErrMsg = NULL;
    int retCode;

    query = QPokeAbilitiesFromId(pokemon->id);

    retCode = sqlite3_exec(db, query, callbackAbilitiesFromId, pokemon, &zErrMsg);
    free(query);
	if(retCode != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return EXIT_FAILURE;
	}

    return EXIT_SUCCESS;
}

int getPokeStats(POKEMON* pokemon, gpointer sqldb){

    sqlite3* db = (sqlite3*) sqldb;
    char* query = NULL;
    char* zErrMsg = NULL;
    int retCode;

    query = QPokeStatsFromId(pokemon->id);

    retCode = sqlite3_exec(db, query, callbackStatsFromId, pokemon, &zErrMsg);
    free(query);
	if(retCode != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return EXIT_FAILURE;
	}

    return EXIT_SUCCESS;
}

int getPokeEggs(POKEMON* pokemon, gpointer sqldb){

    sqlite3* db = (sqlite3*) sqldb;
    char* query = NULL;
    char* zErrMsg = NULL;
    int retCode;

    query = QPokeEggsFromId(pokemon->id);

    retCode = sqlite3_exec(db, query, callbackEggsFromId, pokemon, &zErrMsg);
    free(query);
	if(retCode != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return EXIT_FAILURE;
	}

    return EXIT_SUCCESS;
}

void freeInnerPoke(POKEMON* pokemon){

	free(pokemon->name);
	free(pokemon->types[0]);
	free(pokemon->types[1]);
	free(pokemon->abilities[0]);
	free(pokemon->abilities[1]);
	free(pokemon->abilities[2]);
	free(pokemon->eggGroups[0]);
	free(pokemon->eggGroups[1]);

	return ;
}

void freePoke(POKEMON* pokemon){

	freeInnerPoke(pokemon);
	free(pokemon);

	return ;
}

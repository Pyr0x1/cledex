#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include "queries.h"
#include "callbacks.h"
#include "pokemon.h"

int main(int argc, char* argv[]) {

	sqlite3 *db; 			// SQLite database
	char *zErrMsg = NULL;	// string to hold errors
	int retCode;			// return code used for various functions
	char *query = NULL;
	POKEMON *pokemon = NULL;

    if(argc != 2){
        fprintf(stderr, "Invalid Argument.\nUsage: cldex \"pokemon name\"\n");
        return EXIT_FAILURE;
    }

	pokemon = pokeCreate();

	retCode = sqlite3_open("/usr/local/share/cledex/Database/pokemon.sqlite", &db);

	if(retCode){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		freePoke(pokemon);
		return(EXIT_FAILURE);
	}

    convertSpaceToLine(argv[1]);

	query = QPokeIdFromName(argv[1]);

	retCode = sqlite3_exec(db, query, callbackIdFromName, pokemon, &zErrMsg);
	if(retCode!=SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		freePoke(pokemon);
		free(query);
		return(EXIT_FAILURE);
	}
	if(pokemon->id == 0){
        fprintf(stderr, "Entry not found, make sure the name is correct.\n");
        freePoke(pokemon);
		free(query);
		return(EXIT_FAILURE);
	}


	free(query);

	query = QPokeTypesFromId(pokemon->id);

	retCode = sqlite3_exec(db, query, callbackTypesFromId, pokemon, &zErrMsg);
	if(retCode!=SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		freePoke(pokemon);
		free(query);
		return(EXIT_FAILURE);
	}

	free(query);

    query = QPokeAbilitiesFromId(pokemon->id);

    retCode = sqlite3_exec(db, query, callbackAbilitiesFromId, pokemon, &zErrMsg);
	if(retCode!=SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		freePoke(pokemon);
		free(query);
		return(EXIT_FAILURE);
	}

    free(query);

    query = QPokeStatsFromId(pokemon->id);

    retCode = sqlite3_exec(db, query, callbackStatsFromId, pokemon, &zErrMsg);
	if(retCode!=SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		freePoke(pokemon);
		free(query);
		return(EXIT_FAILURE);
	}

	sqlite3_close(db);

    convertAllStrings(pokemon);

	pokePrint(pokemon);

	freePoke(pokemon);

	return EXIT_SUCCESS;
}

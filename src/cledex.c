#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <glib.h>
#include "queries.h"
#include "callbacks.h"
#include "pokemon.h"

int main(int argc, char* argv[]) {

	sqlite3* db; 			// SQLite database
	int retCode;			// return code used for various functions
    GSList* pokeList = NULL;

    if(argc != 2){
        fprintf(stderr, "Invalid Argument.\nUsage: cldex \"pokemon name\"\n");
        return EXIT_FAILURE;
    }

	retCode = sqlite3_open("/usr/local/share/cledex/database/pokemon.sqlite", &db);

	if(retCode){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return(EXIT_FAILURE);
	}

    convertSpaceToLine(argv[1]);
    convertStarToPerc(argv[1]);

    if((pokeList = pokeListInit(db, argv[1])) == NULL){ // error, free DB and List and exit
        g_slist_free_full(pokeList, (GDestroyNotify) freePoke);
		sqlite3_close(db);
        return EXIT_FAILURE;
    }

    g_slist_foreach(pokeList, (GFunc) getPokeTypes, (gpointer) db);
    g_slist_foreach(pokeList, (GFunc) getPokeAbilities, (gpointer) db);
    g_slist_foreach(pokeList, (GFunc) getPokeStats, (gpointer) db);
    g_slist_foreach(pokeList, (GFunc) getPokeEggs, (gpointer) db);

	sqlite3_close(db);

    g_slist_foreach(pokeList, (GFunc) convertAllStrings, NULL);
    g_slist_foreach(pokeList, (GFunc) pokePrint, NULL);
    printf("\n");
    printf("--------------------\n\n");

	g_slist_free_full(pokeList, (GDestroyNotify) freePoke);

	return EXIT_SUCCESS;
}

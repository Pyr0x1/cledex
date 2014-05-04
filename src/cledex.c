#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <glib.h>
#include "queries.h"
#include "callbacks.h"
#include "pokemon.h"
#include "languages.h"

int main(int argc, char* argv[]) {

	sqlite3* db;
	int retCode, lang, argIndex = 1;
    GSList* pokeList = NULL;
    LOCALDB ldb;

    if(argc < 2){
        fprintf(stderr, "Invalid Argument.\nUsage: cldex [-l language] \"pokemon name\"\n");
        return EXIT_FAILURE;
    }

	retCode = sqlite3_open("/usr/local/share/cledex/database/pokemon.sqlite", &db);

	if(retCode){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return(EXIT_FAILURE);
	}

    if(argc == 2 && argv[1][0] != '-'){
        lang = 9;
        argIndex = 1; // argvalue containing pokemon name, in this case the second one (no language choice)
    }
    else if(argc == 4 && ((strcmp(argv[1], "-l") == 0))){
        if((lang = isValidLang(argv[2], db)) == 0) // if language isn't valid set it to default
            lang = 9;
        argIndex = 3;
    }

    convertSpaceToLine(argv[argIndex]);
    convertStarToPerc(argv[argIndex]);

    if((pokeList = pokeListInit(db, lang, argv[argIndex])) == NULL){ // error, free DB and List and exit
        g_slist_free_full(pokeList, (GDestroyNotify) freePoke);
		sqlite3_close(db);
        return EXIT_FAILURE;
    }

    ldb.db = db; // created to pass more values to g_slist_foreach
    ldb.lang = lang;
    ldb.queryFunc = QPokeTypesFromId;
    ldb.callbackFunc = callbackTypesFromId;

    g_slist_foreach(pokeList, (GFunc) getPokeValues, (gpointer) &ldb);

    ldb.queryFunc = QPokeAbilitiesFromId; // every time we need to pass query and callback function
    ldb.callbackFunc = callbackAbilitiesFromId;

    g_slist_foreach(pokeList, (GFunc) getPokeValues, (gpointer) &ldb);

    ldb.queryFunc = QPokeStatsFromId;
    ldb.callbackFunc = callbackStatsFromId;

    g_slist_foreach(pokeList, (GFunc) getPokeValues, (gpointer) &ldb);

    ldb.queryFunc = QPokeEggsFromId;
    ldb.callbackFunc = callbackEggsFromId;

    g_slist_foreach(pokeList, (GFunc) getPokeValues, (gpointer) &ldb);

    ldb.queryFunc = QPokeGenderRatesFromId;
    ldb.callbackFunc = callbackGenderRatesFromId;

    g_slist_foreach(pokeList, (GFunc) getPokeValues, (gpointer) &ldb);

	sqlite3_close(db);

    g_slist_foreach(pokeList, (GFunc) convertAllStrings, NULL);
    g_slist_foreach(pokeList, (GFunc) pokePrint, NULL);
    printf("\n");
    printf("--------------------\n\n");

	g_slist_free_full(pokeList, (GDestroyNotify) freePoke);

	return EXIT_SUCCESS;
}

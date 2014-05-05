#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <glib.h>
#include <pthread.h>
#include "queries.h"
#include "callbacks.h"
#include "pokemon.h"
#include "languages.h"
#include "tparam.h"

void* threadFunc(void* param){

    TPARAM* tParam = (TPARAM*) param;

    g_slist_foreach(tParam->pokeList, (GFunc) getPokeValues, (gpointer) tParam);

    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {

	sqlite3* db;
	int i, arraySize, retCode, lang, argIndex = 1;
    GSList* pokeList = NULL;
    TPARAM* tParam = NULL;
    pthread_t* threads = NULL;

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

    if(argc == 2 && (strcmp(argv[1], "-l")) != 0){
        lang = 9;
        argIndex = 1; // argvalue containing pokemon name, in this case the second one (no language choice)
    }
    else if(argc == 4 && ((strcmp(argv[1], "-l") == 0))){
        if((lang = isValidLang(argv[2], db)) == 0) // if language isn't valid set it to default
            lang = 9;
        argIndex = 3;
    }

    //convertSpaceToLine(argv[argIndex]); //not used anymore since now we search by local language name, not by identifier
    convertStarToPerc(argv[argIndex]);

    if((pokeList = pokeListInit(db, lang, argv[argIndex])) == NULL){ // error, free DB and List and exit
        g_slist_free_full(pokeList, (GDestroyNotify) freePoke);
		sqlite3_close(db);
        return EXIT_FAILURE;
    }

    tParam = tParamInit(db, lang, pokeList, &arraySize);
    threads = calloc(arraySize, sizeof(pthread_t));

    for(i = 0; i < arraySize; i++)
        pthread_create(&(threads[i]), NULL, threadFunc, &(tParam[i]));

    for(i = 0; i < arraySize; i++)
        pthread_join(threads[i], NULL);

	sqlite3_close(db);

    g_slist_foreach(pokeList, (GFunc) convertAllStrings, NULL);
    g_slist_foreach(pokeList, (GFunc) pokePrint, NULL);
    printf("\n");
    printf("--------------------\n\n");

	g_slist_free_full(pokeList, (GDestroyNotify) freePoke);
	free(threads);
	free(tParam);

	return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include "queries.h"
#include "callbacks.h"
#include "languages.h"

int isValidLang(char* lang, sqlite3* sqldb){

    sqlite3* db = (sqlite3*) sqldb;
    char* query = NULL;
    char* zErrMsg = NULL;
    int retCode, retValue = 0;

    query = QPokeLangIdFromName(lang);

    retCode = sqlite3_exec(db, query, callbackLangIdFromName, &retValue, &zErrMsg);
    free(query);
	if(retCode != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
        return 0;
	}

    return retValue;
}

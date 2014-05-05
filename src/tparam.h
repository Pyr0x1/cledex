#include <glib.h>
#include <sqlite3.h>

typedef struct tparam{
    GSList* pokeList;
    sqlite3* db;
    int lang;
    char* (*queryFunc)(unsigned int id, int lang);
    int (*callbackFunc)(void *pokemon, int argc, char **argv, char **azColName);
}TPARAM;

TPARAM* tParamInit(sqlite3* db, int lang, GSList* pokeList, int *size);

#include <stdio.h>
#include <stdlib.h>
#include "queries.h"
#include "callbacks.h"
#include "tparam.h"

TPARAM* tParamInit(sqlite3* db, int lang, GSList* pokeList, int *size){

    TPARAM* tParam = calloc(5, sizeof(TPARAM));

    tParam[0].db = db;
    tParam[0].lang = lang;
    tParam[0].pokeList = pokeList;
    tParam[0].queryFunc = QPokeTypesFromId;
    tParam[0].callbackFunc = callbackTypesFromId;

    tParam[1].db = db;
    tParam[1].lang = lang;
    tParam[1].pokeList = pokeList;
    tParam[1].queryFunc = QPokeAbilitiesFromId;
    tParam[1].callbackFunc = callbackAbilitiesFromId;

    tParam[2].db = db;
    tParam[2].lang = lang;
    tParam[2].pokeList = pokeList;
    tParam[2].queryFunc = QPokeStatsFromId;
    tParam[2].callbackFunc = callbackStatsFromId;

    tParam[3].db = db;
    tParam[3].lang = lang;
    tParam[3].pokeList = pokeList;
    tParam[3].queryFunc = QPokeEggsFromId;
    tParam[3].callbackFunc = callbackEggsFromId;

    tParam[4].db = db;
    tParam[4].lang = lang;
    tParam[4].pokeList = pokeList;
    tParam[4].queryFunc = QPokeGenderRatesFromId;
    tParam[4].callbackFunc = callbackGenderRatesFromId;

    *size = 5;

    return tParam;
}

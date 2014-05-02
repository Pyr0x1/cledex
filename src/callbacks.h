typedef struct param{

    GSList* pokeList;
    unsigned int current;

}PARAM;

PARAM* paramCreate();

int callbackIdFromName(void *plist, int argc, char **argv, char **azColName);
int callbackTypesFromId(void *pokemon, int argc, char **argv, char **azColName);
int callbackTypesFromName(void *pokeList, int argc, char **argv, char **azColName);
int callbackAbilitiesFromId(void *pokemon, int argc, char **argv, char **azColName);
int callbackAbilitiesFromName(void *pokemon, int argc, char **argv, char **azColName);
int callbackStatsFromId(void *pokemon, int argc, char **argv, char **azColName);
int callbackStatsFromName(void *pokemon, int argc, char **argv, char **azColName);
int callbackEggsFromId(void *pokemon, int argc, char **argv, char **azColName);

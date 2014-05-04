#include <glib.h>
#include <sqlite3.h>

typedef struct pokemon{

	int id;
	int realId;
    char* identifier;
	char* name;
	char* types[2];
	char* abilities[3];
	char* eggGroups[2];
	int stats[6];

}POKEMON;

POKEMON* pokeCreate();
GSList* pokeListInit(sqlite3* db, int lang, char name[]); // initializes list with IDs resulting from name search, if it returns NULL there was an error
void pokePrint(POKEMON* pokemon);
void convertLineToSpace(char* str);
void convertSpaceToLine(char* str);
void convertStarToPerc(char* str);
void convertAllStrings(POKEMON* pokemon);
void fixMegaName(POKEMON* pokemon);
int getPokeTypes(POKEMON* pokemon, gpointer sqldb); // these functions return int, but the value is really never used since it is called in a foreach (anyway if the list is initialized they shouldn't fail)
int getPokeAbilities(POKEMON* pokemon, gpointer sqldb);
int getPokeStats(POKEMON* pokemon, gpointer sqldb);
int getPokeEggs(POKEMON* pokemon, gpointer sqldb);
void freeInnerPoke(POKEMON* pokemon);
void freePoke(POKEMON* pokemon);

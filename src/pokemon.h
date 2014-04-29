typedef struct pokemon{

	int id;
	int realId;
	char* name;
	char* types[2];
	char* abilities[3];
	int stats[6];

}POKEMON;

POKEMON* pokeCreate();
void pokePrint(POKEMON* pokemon);
void convertLineToSpace(char* str);
void convertSpaceToLine(char* str);
void convertAllStrings(POKEMON* pokemon);
void freeInnerPoke(POKEMON* pokemon);
void freePoke(POKEMON* pokemon);

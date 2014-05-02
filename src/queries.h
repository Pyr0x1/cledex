// all query strings must be freed

#define QBUF 1024

char* QPokeNameFromId (unsigned int id);
char* QPokeIdFromName (char name[]);
char* QPokeAbilitiesFromId (unsigned int id);
char* QPokeTypesFromId (unsigned int id);
char* QPokeStatsFromId (unsigned int id);
char* QPokeEggsFromId (unsigned int id);
char* QPokeAbilitiesFromName (char name[]);
char* QPokeTypesFromName (char name[]);
char* QPokeStatsFromName (char name[]);

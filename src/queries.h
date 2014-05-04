// all query strings must be freed

#define QBUF 1024

char* QPokeNameFromId (unsigned int id);
char* QPokeIdFromName (char name[], int lang);
char* QPokeAbilitiesFromId (unsigned int id, int lang);
char* QPokeTypesFromId (unsigned int id, int lang);
char* QPokeStatsFromId (unsigned int id);
char* QPokeEggsFromId (unsigned int id, int lang);
char* QPokeAbilitiesFromName (char name[]);
char* QPokeTypesFromName (char name[], int lang);
char* QPokeStatsFromName (char name[]);
char* QPokeLangIdFromName (char name[]);

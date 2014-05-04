// all query strings must be freed

#define QBUF 1024

char* QPokeIdFromName (char name[], int lang);
char* QPokeAbilitiesFromId (unsigned int id, int lang);
char* QPokeTypesFromId (unsigned int id, int lang);
char* QPokeStatsFromId (unsigned int id, int lang); // lang isn't needed, but prototype must be equal to other ones
char* QPokeEggsFromId (unsigned int id, int lang);
char* QPokeLangIdFromName (char name[]);

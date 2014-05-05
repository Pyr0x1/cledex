#include <sqlite3.h>

int isValidLang(char* lang, sqlite3* sqldb); // returns lang-id or 0 if there was an error or if lang-id isn't found

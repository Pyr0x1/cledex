#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "pokemon.h"
#include "colors.h"

POKEMON* pokeCreate(){

	POKEMON *pokemon = NULL;

	pokemon = calloc(1, sizeof(POKEMON));

	pokemon->name = NULL;
	pokemon->types[0] = NULL;
	pokemon->types[1] = NULL;
	pokemon->abilities[0] = NULL;
	pokemon->abilities[1] = NULL;
	pokemon->abilities[2] = NULL;

	return pokemon;
}

void pokePrint(POKEMON* pokemon){

    printf("\n");
	printf("[%d]\t%s\t\t", pokemon->realId, pokemon->name);
	printf("%s", pokemon->types[0]);

	if(pokemon->types[1] != NULL)
        printf(" / %s", pokemon->types[1]);
    printf("\n\n");

    if(pokemon->abilities[0] != NULL)
        printf("\t%s\n", pokemon->abilities[0]);

    if(pokemon->abilities[1] != NULL)
        printf("\t%s\n", pokemon->abilities[1]);

    if(pokemon->abilities[2] != NULL)
        printf("\t%s (HA)\n", pokemon->abilities[2]);

    printf("\n");

    printf(KRED "\tPS: %d\n" KNRM, pokemon->stats[0]);
    printf(KBLU "\tAtk: %d\n" KNRM, pokemon->stats[1]);
    printf(KYEL "\tDef: %d\n" KNRM, pokemon->stats[2]);
	printf(KCYN "\tSpAtk: %d\n" KNRM, pokemon->stats[3]);
	printf(KGRN "\tSpDef: %d\n" KNRM, pokemon->stats[4]);
	printf(KMAG "\tSpeed: %d\n" KNRM, pokemon->stats[5]);

	printf("\n");

	return ;
}

void convertLineToSpace(char* str){

    int i;

    str[0] = toupper(str[0]);

    for(i = 0; i < strlen(str); i++){
        if(str[i] == '-'){
            str[i] = ' ';
            if(str[i + 1] != '\0')
                str[i + 1] = toupper(str[i + 1]);
        }
    }

    if(strcmp(str, "Ho Oh") == 0) // handle Ho-Oh case that needs line instead of space
        sprintf(str, "%s", "Ho-Oh");

    return ;
}

void convertSpaceToLine(char* str){

    int i;

    str[0] = tolower(str[0]);

    for(i = 0; i < strlen(str); i++){
        if(str[i] == ' ')
            str[i] = '-';
        else
            str[i] = tolower(str[i]);
    }

    return ;
}

void convertAllStrings(POKEMON* pokemon){

    convertLineToSpace(pokemon->name);

    if(pokemon->abilities[0] != NULL)
        convertLineToSpace(pokemon->abilities[0]);

    if(pokemon->abilities[1] != NULL)
        convertLineToSpace(pokemon->abilities[1]);

    if(pokemon->abilities[2] != NULL)
        convertLineToSpace(pokemon->abilities[2]);

    return ;
}

void freeInnerPoke(POKEMON* pokemon){

	free(pokemon->name);
	free(pokemon->types[0]);
	free(pokemon->types[1]);
	free(pokemon->abilities[0]);
	free(pokemon->abilities[1]);
	free(pokemon->abilities[2]);

	return ;
}

void freePoke(POKEMON* pokemon){

	freeInnerPoke(pokemon);
	free(pokemon);

	return ;
}

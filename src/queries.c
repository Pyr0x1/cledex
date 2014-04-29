#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queries.h"

char* QPokeNameFromId (unsigned int id){

	char buf[1024], *query = NULL;

	sprintf(buf, "%s%d%s", "SELECT id, identifier "
						   "FROM pokemon "
						   "WHERE id = ", id, ";");

	query = strdup(buf);

	return query;
}

char* QPokeIdFromName (char name[]){

	char buf[1024], *query = NULL;

	sprintf(buf, "%s%s%s", "SELECT id, species_id, identifier "
						   "FROM pokemon "
						   "WHERE identifier = '", name, "';");

	query = strdup(buf);

	return query;
}

char* QPokeAbilitiesFromId (unsigned int id){

	char buf[1024], *query = NULL;

	sprintf(buf, "%s%d%s", "SELECT A.identifier, PA.slot "
						   "FROM abilities A, pokemon P, pokemon_abilities PA "
						   "WHERE P.id = PA.pokemon_id "
						   "AND PA.ability_id = A.id "
						   "AND P.id = ", id, ";");

	query = strdup(buf);

	return query;
}

char* QPokeTypesFromId (unsigned int id){

	char buf[1024], *query = NULL;

	sprintf(buf, "%s%d%s", "SELECT name, slot "
						   "FROM type_names T, pokemon_types PT "
						   "WHERE T.type_id = PT.type_id "
						   "AND T.local_language_id = 9 "
						   "AND PT.pokemon_id = ", id, ";");

	query = strdup(buf);

	return query;

}

char* QPokeStatsFromId (unsigned int id){

	char buf[1024], *query = NULL;

	sprintf(buf, "%s%d%s", "SELECT base_stat, stat_id "
						   "FROM pokemon P, pokemon_stats PS "
						   "WHERE P.id = PS.pokemon_id "
						   "AND P.id = ", id, ";");

	query = strdup(buf);

	return query;
}


char* QPokeAbilitiesFromName (char name[]){

	char buf[1024], *query = NULL;

	sprintf(buf, "%s%s%s", "SELECT A.identifier "
						   "FROM abilities A, pokemon P, pokemon_abilities PA "
						   "WHERE P.id = PA.pokemon_id "
						   "AND PA.ability_id = A.id "
						   "AND P.identifier = '", name, "';");

	query = strdup(buf);

	return query;
}

char* QPokeTypesFromName (char name[]){

	char buf[1024], *query = NULL;

	sprintf(buf, "%s%s%s", "SELECT name "
						   "FROM type_names T, pokemon_types PT "
						   "WHERE T.type_id = PT.type_id "
						   "AND T.local_language_id = 9 "
						   "AND PT.pokemon_id = '", name, "';");

	query = strdup(buf);

	return query;
}

char* QPokeStatsFromName (char name[]){

	char buf[1024], *query = NULL;

	sprintf(buf, "%s%s%s", "SELECT base_stat "
						   "FROM pokemon P, pokemon_stats PS "
						   "WHERE P.id = PS.pokemon_id "
						   "AND P.identifier = '", name, "';");

	query = strdup(buf);

	return query;

}

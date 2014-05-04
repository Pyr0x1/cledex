#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queries.h"

char* QPokeNameFromId (unsigned int id){

	char buf[QBUF], *query = NULL;

	sprintf(buf, "%s%d%s", "SELECT id, identifier "
						   "FROM pokemon "
						   "WHERE id = ", id, ";");

	query = strdup(buf);

	return query;
}

char* QPokeIdFromName (char name[], int lang){

	char buf[QBUF], *query = NULL;

	sprintf(buf, "%s%s%s%d%s", "SELECT id, species_id, name, identifier "
                               "FROM pokemon P, pokemon_species_names PN "
                               "WHERE P.species_id = PN.pokemon_species_id "
                               "AND P.identifier LIKE '", name, "' "
                               "AND PN.local_language_id = ", lang, ";");

	query = strdup(buf);

	return query;
}

char* QPokeAbilitiesFromId (unsigned int id, int lang){

	char buf[QBUF], *query = NULL;

	sprintf(buf, "%s%d%s%d%s", "SELECT A.name, PA.slot, P.id "
                                "FROM ability_names A, pokemon P, pokemon_abilities PA "
                                "WHERE P.id = PA.pokemon_id "
                                "AND PA.ability_id = A.ability_id "
                                "AND P.id = ", id, " "
                                "AND A.local_language_id = ", lang, " "
                                "ORDER BY P.species_id, P.id, PA.slot;");

	query = strdup(buf);

	return query;
}

char* QPokeTypesFromId (unsigned int id, int lang){

	char buf[QBUF], *query = NULL;

	sprintf(buf, "%s%d%s%d%s", "SELECT name, slot "
                               "FROM type_names T, pokemon_types PT "
                               "WHERE T.type_id = PT.type_id "
                               "AND T.local_language_id = ", lang, " "
                               "AND PT.pokemon_id = ", id, ";");

	query = strdup(buf);

	return query;

}

char* QPokeStatsFromId (unsigned int id){

	char buf[QBUF], *query = NULL;

	sprintf(buf, "%s%d%s", "SELECT base_stat, stat_id "
						   "FROM pokemon P, pokemon_stats PS "
						   "WHERE P.id = PS.pokemon_id "
						   "AND P.id = ", id, ";");

	query = strdup(buf);

	return query;
}

char* QPokeEggsFromId (unsigned int id, int lang){

    char buf[QBUF], *query = NULL;

	sprintf(buf, "%s%d%s%d%s", "SELECT name "
                               "FROM pokemon_egg_groups PEG, egg_group_prose EG "
                               "WHERE EG.egg_group_id = PEG.egg_group_id "
                               "AND PEG.species_id = ", id, " "
                               "AND EG.local_language_id = ", lang, " "
                               "ORDER BY PEG.species_id, PEG.egg_group_id;");

	query = strdup(buf);

    return query;
}

char* QPokeAbilitiesFromName (char name[]){

	char buf[QBUF], *query = NULL;

		sprintf(buf, "%s%s%s", "SELECT A.identifier, PA.slot, P.id "
                               "FROM abilities A, pokemon P, pokemon_abilities PA "
                               "WHERE P.id = PA.pokemon_id "
                               "AND PA.ability_id = A.id "
                               "AND P.identifier LIKE '", name, "' "
                               "ORDER BY P.species_id, P.id, PA.slot;");

	query = strdup(buf);

	return query;
}

char* QPokeTypesFromName (char name[], int lang){

	char buf[QBUF], *query = NULL;

	sprintf(buf, "%s%id%s%s%s", "SELECT name, slot, P.id "
                                "FROM type_names T, pokemon_types PT, pokemon P "
                                "WHERE T.type_id = PT.type_id "
                                "AND P.id = PT.pokemon_id "
                                "AND T.local_language_id = ", lang, " "
                                "AND P.identifier LIKE '", name,"' "
                                "ORDER BY P.species_id, P.id, slot;");

	query = strdup(buf);

	return query;
}

char* QPokeStatsFromName (char name[]){

	char buf[QBUF], *query = NULL;

	sprintf(buf, "%s%s%s", "SELECT base_stat, stat_id, pokemon_id "
						   "FROM pokemon P, pokemon_stats PS "
						   "WHERE P.id = PS.pokemon_id "
						   "AND P.identifier LIKE '", name, "'"
						   "ORDER BY P.species_id, P.id, stat_id;");

	query = strdup(buf);

	return query;

}

char* QPokeLangIdFromName (char name[]){

	char buf[QBUF], *query = NULL;

	sprintf(buf, "%s%s%s", "SELECT id "
                           "FROM languages "
                           "WHERE identifier = '", name, "';");

	query = strdup(buf);

	return query;

}

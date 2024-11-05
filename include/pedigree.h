/*
 * pedigree.h
 *
 *  Created on: 28 Oct 2024
 *      Author: billy
 */

#ifndef SERVICES_ACCESSION_SERVICE_INCLUDE_PEDIGREE_H_
#define SERVICES_ACCESSION_SERVICE_INCLUDE_PEDIGREE_H_


typedef struct PedigreeParent
{
	char *pp_nam_store_code_s;

	char *pp_nam_synonym_1_s;

	char *pp_nam_synonym_2_s;
	char *pp_nam_synonym_3_s;

} PedigreeParent;


typedef struct PedigreeGrandparent
{

	char *pg_watkins_synonym_0_s;

	char *pg_watkins_country_s;

	char *pg_watkins_growth_habit_s;

	char *pg_watkins_ancestral_group_s;

} PedigreeGrandparent;




#endif /* SERVICES_ACCESSION_SERVICE_INCLUDE_PEDIGREE_H_ */

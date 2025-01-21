/*
 * pedigree.h
 *
 *  Created on: 28 Oct 2024
 *      Author: billy
 */

#ifndef SERVICES_ACCESSION_SERVICE_INCLUDE_PEDIGREE_H_
#define SERVICES_ACCESSION_SERVICE_INCLUDE_PEDIGREE_H_


#include "accession_service_library.h"

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





#ifdef __cplusplus
extern "C"
{
#endif




ACCESSION_SERVICE_LOCAL PedigreeParent *AllocatePedigreeParent (const char * const store_code_s, const char * const synonym_1_s,
																																const char * const synonym_2_s, const char * const synonym_3_s);

ACCESSION_SERVICE_LOCAL void FreePedigreeParent (PedigreeParent *parent_p);


ACCESSION_SERVICE_LOCAL json_t *GetPedigreeParentAsJSON (const PedigreeParent * const parent_p);


ACCESSION_SERVICE_LOCAL PedigreeParent *GetPedigreeParentAsJSON (const json_t * const parent_data_p);


#ifdef __cplusplus
}
#endif


#endif /* SERVICES_ACCESSION_SERVICE_INCLUDE_PEDIGREE_H_ */

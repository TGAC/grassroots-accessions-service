/*
 * academic_toolkit.h
 *
 *  Created on: 28 Oct 2024
 *      Author: billy
 */

#ifndef SERVICES_ACCESSION_SERVICE_INCLUDE_ACADEMIC_TOOLKIT_H_
#define SERVICES_ACCESSION_SERVICE_INCLUDE_ACADEMIC_TOOLKIT_H_



#include "accession_service_library.h"

#include "jansson.h"


typedef struct AcademicToolkitRecord
{
	char *atr_accession_s;

	char *atr_store_code_s;

	char *atr_synonym_1_s;

	char *atr_synonym_2_s;

} AcademicToolkitRecord;





#ifdef __cplusplus
extern "C"
{
#endif


ACCESSION_SERVICE_LOCAL int CreateAcademicToolkitRecordFromTabularJSON (const json_t * const json_p, AcademicToolkitRecord **btk_pp);


ACCESSION_SERVICE_LOCAL AcademicToolkitRecord *AllocateAcademicToolkitRecord (const char * const store_code_s, const char * const accession_s, const char * const syn_1_s, const char * const syn_2_s);


ACCESSION_SERVICE_LOCAL void FreeAcademicToolkitRecord (AcademicToolkitRecord *parent_p);


ACCESSION_SERVICE_LOCAL json_t *GetAcademicToolkitRecordAsJSON (const AcademicToolkitRecord * const btk_p);


ACCESSION_SERVICE_LOCAL AcademicToolkitRecord *GetAcademicToolkitRecordFromJSON (const json_t * const json_p);


#ifdef __cplusplus
}
#endif


#endif /* SERVICES_ACCESSION_SERVICE_INCLUDE_ACADEMIC_TOOLKIT_H_ */

/*
 * breeders_toolkit.h
 *
 *  Created on: 28 Oct 2024
 *      Author: billy
 */

#ifndef SERVICES_ACCESSION_SERVICE_INCLUDE_BREEDERS_TOOLKIT_H_
#define SERVICES_ACCESSION_SERVICE_INCLUDE_BREEDERS_TOOLKIT_H_


#include "accession_service_library.h"

#include "jansson.h"



typedef struct BreedersToolkitRecord
{
	char *btr_accession_s;

	char *btr_store_code_s;

} BreedersToolkitRecord;




#ifdef __cplusplus
extern "C"
{
#endif


ACCESSION_SERVICE_LOCAL int CreateBreedersToolkitRecordFromTabularJSON (const json_t * const json_p, BreedersToolkitRecord **btk_pp);


ACCESSION_SERVICE_LOCAL BreedersToolkitRecord *AllocateBreedersToolkitRecord (const char * const store_code_s, const char * const accession_s);


ACCESSION_SERVICE_LOCAL void FreeBreedersToolkitRecord (BreedersToolkitRecord *parent_p);


ACCESSION_SERVICE_LOCAL json_t *GetBreedersToolkitRecordAsJSON (const BreedersToolkitRecord * const btk_p);


ACCESSION_SERVICE_LOCAL BreedersToolkitRecord *GetBreedersToolkitRecordFromJSON (const json_t * const json_p);


#ifdef __cplusplus
}
#endif


#endif /* SERVICES_ACCESSION_SERVICE_INCLUDE_BREEDERS_TOOLKIT_H_ */

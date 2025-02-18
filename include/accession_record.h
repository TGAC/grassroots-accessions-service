/*
 * accession.h
 *
 *  Created on: 28 Oct 2024
 *      Author: billy
 */

#ifndef SERVICES_ACCESSION_SERVICE_INCLUDE_ACCESSION_H_
#define SERVICES_ACCESSION_SERVICE_INCLUDE_ACCESSION_H_


#include "accession_service_library.h"

#include "jansson.h"


typedef struct AccessionRecord
{
	char *ar_id_s;

	char *ar_group_s;

	char *ar_subcollection_s;

} AccessionRecord;




#ifdef __cplusplus
extern "C"
{
#endif


ACCESSION_SERVICE_LOCAL int CreateAccessionRecordFromTabularJSON (const json_t * const json_p, AccessionRecord **ar_pp);


ACCESSION_SERVICE_LOCAL AccessionRecord *AllocateAccessionRecord (const char * const store_code_s, const char * const accession_s);


ACCESSION_SERVICE_LOCAL void FreeAccessionRecord (AccessionRecord *parent_p);


ACCESSION_SERVICE_LOCAL json_t *GetAccessionRecordAsJSON (const AccessionRecord * const btk_p);


ACCESSION_SERVICE_LOCAL AccessionRecord *GetAccessionRecordFromJSON (const json_t * const json_p);


#ifdef __cplusplus
}
#endif



#endif /* SERVICES_ACCESSION_SERVICE_INCLUDE_ACCESSION_H_ */

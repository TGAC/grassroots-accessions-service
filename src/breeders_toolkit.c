/*
 * breeders_toolkit.c
 *
 *  Created on: 21 Jan 2025
 *      Author: tyrrells
 */


#include "breeders_toolkit.h"

#include "memory_allocations.h"
#include "string_utils.h"


BreedersToolkitRecord *AllocateBreedersToolkitRecord (const char * const store_code_s, const char * const accession_s);s


void FreeBreedersToolkitRecord (BreedersToolkitRecord *btk_p)
{
	if (btk_p -> btr_accession_s)
		{
			FreeCopiedString (btk_p -> btr_accession_s);
		}

	if (btk_p -> btr_store_code_s)
		{
			FreeCopiedString (btk_p -> btr_store_code_s);
		}

	FreeMemory (btk_p);
}


json_t *GetBreedersToolkitRecordAsJSON (const BreedersToolkitRecord * const btk_p);


BreedersToolkitRecord *GetBreedersToolkitRecordAsJSON (const json_t * const btk_jsons_p);

/*
 * breeders_toolkit.c
 *
 *  Created on: 21 Jan 2025
 *      Author: tyrrells
 */


#include "breeders_toolkit.h"

#include "memory_allocations.h"
#include "string_utils.h"


BreedersToolkitRecord *AllocateBreedersToolkitRecord (const char * const store_code_s, const char * const accession_s)
{

}


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



int CreateBreedersToolkitRecordFromTabularJSON (const json_t * const json_p, BreedersToolkitRecord **btk_pp)
{
	int res = 0;
	const char * const BTK_STORE_CODE_KEY_S = "BTK_StoreCode";
	const char * const BTK_ACCESSION_KEY_S = "BTK_AccessionName";
	const char *store_code_s = GetJSONString (json_p, BTK_STORE_CODE_KEY_S);
	const char *accession_s = GetJSONString (json_p, BTK_ACCESSION_KEY_S);

	if (!IsStringEmpty (store_code_s))
		{
			if (!IsStringEmpty (accession_s))
				{
					BreedersToolkitRecord *btk_p = AllocateBreedersToolkitRecord (store_code_s, accession_s);

					if (btk_p)
						{
							*btk_pp = btk_p;
							res = 1;
						}
					else
						{
							res = -1;
						}

				}		/* if (!IsStringEmpty (accession_s)) */

		}		/* if (!IsStringEmpty (store_code_s)) */

	return res;
}



json_t *GetBreedersToolkitRecordAsJSON (const BreedersToolkitRecord * const btk_p);


BreedersToolkitRecord *GetBreedersToolkitRecordAsJSON (const json_t * const btk_jsons_p);

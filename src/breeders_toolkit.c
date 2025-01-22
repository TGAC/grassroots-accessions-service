/*
 * breeders_toolkit.c
 *
 *  Created on: 21 Jan 2025
 *      Author: tyrrells
 */


#include "breeders_toolkit.h"

#include "memory_allocations.h"
#include "string_utils.h"
#include "streams.h"
#include "schema_keys.h"


static const char * const S_ACCESSION_S = CONTEXT_PREFIX_SCHEMA_ORG_S "name";
static const char * const S_STORE_CODE_S = CONTEXT_PREFIX_SCHEMA_ORG_S "identifier";


BreedersToolkitRecord *AllocateBreedersToolkitRecord (const char * const store_code_s, const char * const accession_s)
{
	char *copied_store_code_s = EasyCopyToNewString (store_code_s);

	if (copied_store_code_s)
		{
			char *copied_accession_s = EasyCopyToNewString (accession_s);

			if (copied_accession_s)
				{
					BreedersToolkitRecord *btk_p = (BreedersToolkitRecord *) AllocMemory (sizeof (BreedersToolkitRecord));

					if (btk_p)
						{
							btk_p -> btr_accession_s = copied_accession_s;
							btk_p -> btr_store_code_s = copied_store_code_s;

							return btk_p;
						}		/* if (btk_p) */
					else
						{
							PrintErrors (STM_LEVEL_SEVERE, __FILE__, __LINE__, "Failed to allocate memory for BreedersToolkitRecord (\"%s\", \"%s\"", store_code_s, accession_s);
						}

					FreeCopiedString (copied_accession_s);
				}		/* if (copied_accession_s) */
			else
				{
					PrintErrors (STM_LEVEL_SEVERE, __FILE__, __LINE__, "Failed to copy accession \"s\"", accession_s);
				}

			FreeCopiedString (copied_store_code_s);
		}		/* if (copied_store_code_s) */
	else
		{
			PrintErrors (STM_LEVEL_SEVERE, __FILE__, __LINE__, "Failed to copy store code \"s\"", store_code_s);
		}

	return NULL;
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



json_t *GetBreedersToolkitRecordAsJSON (const BreedersToolkitRecord * const btk_p)
{
	return NULL;
}


BreedersToolkitRecord *GetBreedersToolkitRecordAsJSON (const json_t * const btk_json_p)
{
	return NULL;
}

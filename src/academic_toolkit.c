/*
 * academic_toolkit.c
 *
 *  Created on: 22 Jan 2025
 *      Author: billy
 */


#include "academic_toolkit.h"

#include "string_utils.h"
#include "memory_allocations.h"
#include "streams.h"
#include "json_util.h"


AcademicToolkitRecord *AllocateAcademicToolkitRecord (const char * const store_code_s, const char * const accession_s, const char * const syn_1_s, const char * const syn_2_s)
{
	char *copied_store_code_s = EasyCopyToNewString (store_code_s);

	if (copied_store_code_s)
		{
			char *copied_accession_s = EasyCopyToNewString (accession_s);

			if (copied_accession_s)
				{
					char *copied_syn_1_s = NULL;

					if ((syn_1_s == NULL) || ((copied_syn_1_s = EasyCopyToNewString (syn_1_s)) != NULL))
						{
							char *copied_syn_2_s = NULL;

							if ((syn_2_s == NULL) || ((copied_syn_2_s = EasyCopyToNewString (syn_2_s)) != NULL))
								{
									AcademicToolkitRecord *atk_p = (AcademicToolkitRecord *) AllocMemory (sizeof (AcademicToolkitRecord));

									if (atk_p)
										{
											atk_p -> atr_accession_s = copied_accession_s;
											atk_p -> atr_store_code_s = copied_store_code_s;
											atk_p -> atr_synonym_1_s = copied_syn_1_s;
											atk_p -> atr_synonym_2_s = copied_syn_2_s;

											return atk_p;
										}		/* if (atk_p) */
									else
										{
											PrintErrors (STM_LEVEL_SEVERE, __FILE__, __LINE__, "Failed to allocate memory for BreedersToolkitRecord (\"%s\", \"%s\"", store_code_s, accession_s);
										}

								}		/* if ((syn_2_s == NULL) || ((copied_syn_2_s = EasyCopyToNewString (syn_2_s)) != NULL)) */
							else
								{

								}

						}		/* if ((syn_1_s == NULL) || ((copied_syn_1_s = EasyCopyToNewString (syn_1_s)) != NULL)) */
					else
						{

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


void FreeAcademicToolkitRecord (AcademicToolkitRecord *atk_p)
{
	if (atk_p -> atr_accession_s)
		{
			FreeCopiedString (atk_p -> atr_accession_s);
		}

	if (atk_p -> atr_store_code_s)
		{
			FreeCopiedString (atk_p -> atr_store_code_s);
		}

	if (atk_p -> atr_synonym_1_s)
		{
			FreeCopiedString (atk_p -> atr_synonym_1_s);
		}

	if (atk_p -> atr_synonym_2_s)
		{
			FreeCopiedString (atk_p -> atr_synonym_2_s);
		}

	FreeMemory (atk_p);
}


json_t *GetAcademicToolkitRecordAsJSON (const AcademicToolkitRecord * const atk_p)
{
	json_t *json_p = NULL;

	return json_p;
}


AcademicToolkitRecord *GetAcademicToolkitRecordFromJSON (const json_t * const json_p)
{
	AcademicToolkitRecord *atk_p = NULL;

	return atk_p;
}




int CreateAcademicToolkitRecordFromTabularJSON (const json_t * const json_p, AcademicToolkitRecord **atk_pp)
{
	int res = 0;
	const char * const ATK_STORE_CODE_KEY_S = "ATK_StoreCode";
	const char *store_code_s = GetJSONString (json_p, ATK_STORE_CODE_KEY_S);

	if (!IsStringEmpty (store_code_s))
		{
			const char * const ATK_ACCESSION_KEY_S = "ATK_AccessionName";
			const char *accession_s = GetJSONString (json_p, ATK_ACCESSION_KEY_S);

			if (!IsStringEmpty (accession_s))
				{
					const char * const ATK_SYNONYM_1_KEY_S = "ATK_Synonym1";
					const char * const ATK_SYNONYM_2_KEY_S = "ATK_Synonym2";
					const char *syn_1_s = GetJSONString (json_p, ATK_SYNONYM_1_KEY_S);
					const char *syn_2_s = GetJSONString (json_p, ATK_SYNONYM_2_KEY_S);

					AcademicToolkitRecord *atk_p = AllocateAcademicToolkitRecord (store_code_s, accession_s, syn_1_s, syn_2_s);

					if (atk_p)
						{
							*atk_pp = atk_p;
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

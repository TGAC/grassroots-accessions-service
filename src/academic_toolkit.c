/*
 * academic_toolkit.c
 *
 *  Created on: 22 Jan 2025
 *      Author: billy
 */


#include "academic_toolkit.h"





AcademicToolkitRecord *AllocateAcademicToolkitRecord (const char * const store_code_s, const char * const accession_s, const char * const syn_1_s, const char * const syn_2_s)
{

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


json_t *GetAcademicToolkitRecordAsJSON (const AcademicToolkitRecord * const btk_p)
{

}


AcademicToolkitRecord *GetAcademicToolkitRecordFromJSON (const json_t * const json_p)
{

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

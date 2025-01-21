/*
 * pedigree.c
 *
 *  Created on: 21 Jan 2025
 *      Author: tyrrells
 */



#include "pedigree.h"


PedigreeParent *AllocatePedigreeParent (const char * const store_code_s, const char * const synonym_1_s,
																				const char * const synonym_2_s, const char * const synonym_3_s)
{

}


void FreePedigreeParent (PedigreeParent *parent_p)
{
	if (parent_p -> pp_nam_store_code_s)
		{
			FreeCopiedString (parent_p -> pp_nam_store_code_s);
		}

	if (parent_p -> pp_nam_synonym_1_s)
		{
			FreeCopiedString (parent_p -> pp_nam_synonym_1_s);
		}

	if (parent_p -> pp_nam_synonym_2_s)
		{
			FreeCopiedString (parent_p -> pp_nam_synonym_2_s);
		}

	if (parent_p -> pp_nam_synonym_3_s)
		{
			FreeCopiedString (parent_p -> pp_nam_synonym_3_s);
		}

	FreeMemory (parent_p);
}

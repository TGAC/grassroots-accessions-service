/*
** Copyright 2014-2018 The Earlham Institute
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/
/*
 * parental_genotype_service_service_data.c
 *
 *  Created on: 18 Nov 2018
 *      Author: billy
 */

#define ALLOCATE_ACCESSIONS_SERVICE_TAGS (1)
#include "accession_service_data.h"

#include "streams.h"
#include "string_utils.h"


AccessionServiceData *AllocateAccessionServiceData  (void)
{
	AccessionServiceData *data_p = (AccessionServiceData *) AllocMemory (sizeof (AccessionServiceData));

	if (data_p)
		{
			data_p -> asd_mongo_p = NULL;

			return data_p;
		}

	return NULL;
}


void FreeAccessionServiceData (AccessionServiceData *data_p)
{
	if (data_p -> asd_mongo_p)
		{
			FreeMongoTool (data_p -> asd_mongo_p);
		}

	FreeMemory (data_p);
}


bool ConfigureAccessionService (AccessionServiceData *data_p, GrassrootsServer *grassroots_p)
{
	bool success_flag = false;
	const json_t *service_config_p = data_p -> asd_base_data.sd_config_p;

	data_p -> asd_database_s = GetJSONString (service_config_p, "database");

	if (data_p -> asd_database_s)
		{
			if ((data_p -> asd_collection_s = GetJSONString (service_config_p, "collection")) != NULL)
				{
					if ((data_p -> asd_mongo_p = AllocateMongoTool (NULL, grassroots_p -> gs_mongo_manager_p)) != NULL)
						{
							if (SetMongoToolDatabaseAndCollection (data_p -> asd_mongo_p, data_p -> asd_database_s, data_p -> asd_collection_s))
								{
									success_flag = true;
								}
							else
								{
									PrintErrors (STM_LEVEL_SEVERE, __FILE__, __LINE__, "Failed to set database to \"%s\"", data_p -> asd_database_s);
								}

						}		/* if ((data_p -> asd_mongo_p = AllocateMongoTool (NULL, grassroots_p -> gs_mongo_manager_p)) != NULL) */
					else
						{
							PrintErrors (STM_LEVEL_SEVERE, __FILE__, __LINE__, "Failed to allocate MongoTool");
						}

				}		/* if ((data_p -> asd_accessions_collection_s = GetJSONString (service_config_p, "accessions_collection")) != NULL) */

		}		/* if (data_p -> psd_database_s) */

	return success_flag;
}



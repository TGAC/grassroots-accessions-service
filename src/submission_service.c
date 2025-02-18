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
 * submission_service.c
 *
 *  Created on: 22 Oct 2018
 *      Author: billy
 */

#include <string.h>

#include "submission_service.h"
#include "accession_service.h"
#include "accession_service_data.h"

#include "audit.h"
#include "streams.h"
#include "math_utils.h"
#include "string_utils.h"
#include "schema_keys.h"

#include "breeders_toolkit.h"

#include "json_parameter.h"

/*
 * Static declarations
 */

static const char * const S_ID_S = "id";

static NamedParameterType S_SET_DATA = { "Data", PT_JSON_TABLE };


static const char *GetAccessionSubmissionServiceName (const Service *service_p);

static const char *GetAccessionSubmissionServiceDescription (const Service *service_p);

static const char *GetAccessionSubmissionServiceAlias (const Service *service_p);

static const char *GetAccessionSubmissionServiceInformationUri (const Service *service_p);

static ParameterSet *GetAccessionSubmissionServiceParameters (Service *service_p, DataResource *resource_p, User *user_p);

static void ReleaseAccessionSubmissionServiceParameters (Service *service_p, ParameterSet *params_p);

static ServiceJobSet *RunAccessionSubmissionService (Service *service_p, ParameterSet *param_set_p, User *user_p, ProvidersStateTable *providers_p);

static ParameterSet *IsResourceForAccessionSubmissionService (Service *service_p, DataResource *resource_p, Handler *handler_p);

static bool CloseAccessionSubmissionService (Service *service_p);

static ServiceMetadata *GetAccessionSubmissionServiceMetadata (Service *service_p);

static bool GetAccessionSubmissionServiceParameterTypesForNamedParameters (const Service *service_p, const char *param_name_s, ParameterType *pt_p);


static const char *AddParentRow (json_t *doc_p, json_t *genotypes_p, const char *key_s);

static bool AddAccessionDataFromJSON (ServiceJob *job_p, const json_t *accessions_json_p, const AccessionServiceData *data_p);



/*
 * API definitions
 */


Service *GetAccessionSubmissionService (GrassrootsServer *grassroots_p)
{
	Service *service_p = (Service *) AllocMemory (sizeof (Service));

	if (service_p)
		{
			AccessionServiceData *data_p = AllocateAccessionServiceData ();

			if (data_p)
				{
					if (InitialiseService (service_p,
																 GetAccessionSubmissionServiceName,
																 GetAccessionSubmissionServiceDescription,
																 GetAccessionSubmissionServiceAlias,
																 GetAccessionSubmissionServiceInformationUri,
																 RunAccessionSubmissionService,
																 IsResourceForAccessionSubmissionService,
																 GetAccessionSubmissionServiceParameters,
																 GetAccessionSubmissionServiceParameterTypesForNamedParameters,
																 ReleaseAccessionSubmissionServiceParameters,
																 CloseAccessionSubmissionService,
																 NULL,
																 false,
																 SY_SYNCHRONOUS,
																 (ServiceData *) data_p,
																 GetAccessionSubmissionServiceMetadata,
																 NULL,
																 grassroots_p))
						{

							if (ConfigureAccessionService (data_p, grassroots_p))
								{
									return service_p;
								}
						}		/* if (InitialiseService (.... */
					else
						{
							FreeAccessionServiceData (data_p);
						}

				}		/* if (data_p) */

			FreeService (service_p);
		}		/* if (service_p) */

	return NULL;
}



static const char *GetAccessionSubmissionServiceName (const Service * UNUSED_PARAM (service_p))
{
	return "Accession submission service";
}


static const char *GetAccessionSubmissionServiceDescription (const Service * UNUSED_PARAM (service_p))
{
	return "A service to submit plant line accession data";
}


static const char *GetAccessionSubmissionServiceAlias (const Service * UNUSED_PARAM (service_p))
{
	return ACCESSION_GROUP_ALIAS_PREFIX_S SERVICE_GROUP_ALIAS_SEPARATOR "submit";
}


static const char *GetAccessionSubmissionServiceInformationUri (const Service * UNUSED_PARAM (service_p))
{
	return NULL;
}


static ParameterSet *GetAccessionSubmissionServiceParameters (Service *service_p, DataResource * UNUSED_PARAM (resource_p), User * UNUSED_PARAM (user_p))
{
	ParameterSet *param_set_p = AllocateParameterSet ("Accession submission service parameters", "The parameters used for the Accession submission service");

	if (param_set_p)
		{
			ServiceData *data_p = service_p -> se_data_p;
			Parameter *param_p = NULL;
			ParameterGroup *group_p = CreateAndAddParameterGroupToParameterSet ("Parental Cross Data", false, data_p, param_set_p);

			if ((param_p = EasyCreateAndAddJSONParameterToParameterSet (data_p, param_set_p, group_p, S_SET_DATA.npt_type, S_SET_DATA.npt_name_s, "Data", "The parental-cross data", NULL, PL_SIMPLE)) != NULL)
				{
					if (AddParameterKeyStringValuePair (param_p, PA_TABLE_COLUMN_HEADERS_PLACEMENT_S, PA_TABLE_COLUMN_HEADERS_PLACEMENT_FIRST_ROW_S))
						{
							return param_set_p;
						}
				}
			else
				{
					PrintErrors (STM_LEVEL_SEVERE, __FILE__, __LINE__, "Failed to add %s parameter", S_SET_DATA.npt_name_s);
				}

			FreeParameterSet (param_set_p);
		}
	else
		{
			PrintErrors (STM_LEVEL_SEVERE, __FILE__, __LINE__, "Failed to allocate %s ParameterSet", GetAccessionSubmissionServiceName (service_p));
		}

	return NULL;
}


static bool GetAccessionSubmissionServiceParameterTypesForNamedParameters (const Service *service_p, const char *param_name_s, ParameterType *pt_p)
{
	bool success_flag = true;

	if (strcmp (param_name_s, S_SET_DATA.npt_name_s) == 0)
		{
			*pt_p = S_SET_DATA.npt_type;
		}
	else
		{
			success_flag = false;
		}

	return success_flag;
}


static void ReleaseAccessionSubmissionServiceParameters (Service * UNUSED_PARAM (service_p), ParameterSet *params_p)
{
	FreeParameterSet (params_p);
}




static bool CloseAccessionSubmissionService (Service *service_p)
{
	bool success_flag = true;

	FreeAccessionServiceData ((AccessionServiceData *) (service_p -> se_data_p));;

	return success_flag;
}



static ServiceJobSet *RunAccessionSubmissionService (Service *service_p, ParameterSet *param_set_p, User * UNUSED_PARAM (user_p), ProvidersStateTable * UNUSED_PARAM (providers_p))
{
	AccessionServiceData *data_p = (AccessionServiceData *) (service_p -> se_data_p);

	service_p -> se_jobs_p = AllocateSimpleServiceJobSet (service_p, NULL, "GeneTrees");

	if (service_p -> se_jobs_p)
		{
			OperationStatus status = OS_FAILED_TO_START;
			ServiceJob *job_p = GetServiceJobFromServiceJobSet (service_p -> se_jobs_p, 0);

			LogParameterSet (param_set_p, job_p);

			if (param_set_p)
				{
					const json_t *data_json_p = NULL;

					if (GetCurrentJSONParameterValueFromParameterSet (param_set_p, S_SET_DATA.npt_name_s, &data_json_p))
						{
							/*
							 * Has a spreadsheet been uploaded?
							 */
							if (data_json_p && (json_array_size (data_json_p) > 0))
								{
									if (!AddAccessionDataFromJSON (job_p, data_json_p, data_p))
										{
											PrintJSONToErrors (STM_LEVEL_SEVERE, __FILE__, __LINE__, data_json_p, "AddAccessionDataFromJSON () failed");
										}
								}		/* if (data_json_p) */


						}		/* if (GetParameterValueFromParameterSet (param_set_p, S_SET_DATA.npt_name_s, &data_value, true)) */


				}		/* if (param_set_p) */

			SetServiceJobStatus (job_p, status);
			LogServiceJob (job_p);
		}		/* if (service_p -> se_jobs_p) */

	return service_p -> se_jobs_p;
}


static ServiceMetadata *GetAccessionSubmissionServiceMetadata (Service *service_p)
{
	const char *term_url_s = CONTEXT_PREFIX_EDAM_ONTOLOGY_S "topic_0625";
	SchemaTerm *category_p = AllocateSchemaTerm (term_url_s, "Genotype and phenotype",
																							 "The study of genetic constitution of a living entity, such as an individual, and organism, a cell and so on, "
																							 "typically with respect to a particular observable phenotypic traits, or resources concerning such traits, which "
																							 "might be an aspect of biochemistry, physiology, morphology, anatomy, development and so on.");

	if (category_p)
		{
			SchemaTerm *subcategory_p;

			term_url_s = CONTEXT_PREFIX_EDAM_ONTOLOGY_S "operation_0304";
			subcategory_p = AllocateSchemaTerm (term_url_s, "Query and retrieval", "Search or query a data resource and retrieve entries and / or annotation.");

			if (subcategory_p)
				{
					ServiceMetadata *metadata_p = AllocateServiceMetadata (category_p, subcategory_p);

					if (metadata_p)
						{
							SchemaTerm *input_p;

							term_url_s = CONTEXT_PREFIX_EDAM_ONTOLOGY_S "data_0968";
							input_p = AllocateSchemaTerm (term_url_s, "Keyword",
																						"Boolean operators (AND, OR and NOT) and wildcard characters may be allowed. Keyword(s) or phrase(s) used (typically) for text-searching purposes.");

							if (input_p)
								{
									if (AddSchemaTermToServiceMetadataInput (metadata_p, input_p))
										{
											SchemaTerm *output_p;
											/* Genotype */
											term_url_s = CONTEXT_PREFIX_EXPERIMENTAL_FACTOR_ONTOLOGY_S "EFO_0000513";
											output_p = AllocateSchemaTerm (term_url_s, "genotype", "Information, making the distinction between the actual physical material "
																										 "(e.g. a cell) and the information about the genetic content (genotype).");

											if (output_p)
												{
													if (AddSchemaTermToServiceMetadataOutput (metadata_p, output_p))
														{
															return metadata_p;
														}		/* if (AddSchemaTermToServiceMetadataOutput (metadata_p, output_p)) */
													else
														{
															PrintErrors (STM_LEVEL_SEVERE, __FILE__, __LINE__, "Failed to add output term %s to service metadata", term_url_s);
															FreeSchemaTerm (output_p);
														}

												}		/* if (output_p) */
											else
												{
													PrintErrors (STM_LEVEL_SEVERE, __FILE__, __LINE__, "Failed to allocate output term %s for service metadata", term_url_s);
												}

										}		/* if (AddSchemaTermToServiceMetadataInput (metadata_p, input_p)) */
									else
										{
											PrintErrors (STM_LEVEL_SEVERE, __FILE__, __LINE__, "Failed to add input term %s to service metadata", term_url_s);
											FreeSchemaTerm (input_p);
										}

								}		/* if (input_p) */
							else
								{
									PrintErrors (STM_LEVEL_SEVERE, __FILE__, __LINE__, "Failed to allocate input term %s for service metadata", term_url_s);
								}

						}		/* if (metadata_p) */
					else
						{
							PrintErrors (STM_LEVEL_SEVERE, __FILE__, __LINE__, "Failed to allocate service metadata");
						}

				}		/* if (subcategory_p) */
			else
				{
					PrintErrors (STM_LEVEL_SEVERE, __FILE__, __LINE__, "Failed to allocate sub-category term %s for service metadata", term_url_s);
				}

		}		/* if (category_p) */
	else
		{
			PrintErrors (STM_LEVEL_SEVERE, __FILE__, __LINE__, "Failed to allocate category term %s for service metadata", term_url_s);
		}

	return NULL;
}


static ParameterSet *IsResourceForAccessionSubmissionService (Service * UNUSED_PARAM (service_p), DataResource * UNUSED_PARAM (resource_p), Handler * UNUSED_PARAM (handler_p))
{
	return NULL;
}




static bool AddAccessionDataFromJSON (ServiceJob *job_p, const json_t *accessions_json_p, const AccessionServiceData *data_p)
{
	bool success_flag	= true;
	OperationStatus status = OS_FAILED;

	if (json_is_array (accessions_json_p))
		{
			const size_t num_rows = json_array_size (accessions_json_p);
			size_t i;
			size_t num_imported = 0;
			size_t num_empty_rows = 0;
			size_t num_existing = 0;

			for (i = 0; i < num_rows; ++ i)
				{
					json_t *table_row_json_p = json_array_get (accessions_json_p, i);
					const size_t row_size =  json_object_size (table_row_json_p);

					if (row_size > 0)
						{
							const char * const ACCESSION_ID_KEY_S = "ID";
							const char * const ACCESSION_GROUP_KEY_S = "Group";
							const char * const ACCESSION_SUBCOLLECTION_KEY_S = "SubCollection";
							const char * const PEDIGREE_NAM_STORE_CODE_KEY_S = "NAM.Parent.StoreCode";
							const char * const PEDIGREE_NAM_PARENT_SYNONYM_1_KEY_S = "NAM.Parent.Synonym1";
							const char * const PEDIGREE_NAM_PARENT_SYNONYM_2_KEY_S = "NAM.Parent.Synonym2";
							const char * const PEDIGREE_NAM_PARENT_SYNONYM_3_KEY_S = "NAM.Parent.Synonym3";
							const char * const PEDIGREE_WATKINS_STORE_CODE_KEY_S = "Watkins.Parent.StoreCode";
							const char * const PEDIGREE_WATKINS_PARENT_SYNONYM_1_S = "Watkins.Parent.Synonym1";
							const char * const PEDIGREE_WATKINS_COUNTRY_S = "Watkins.Country.of.Origin.";
							const char * const PEDIGREE_WATKINS_PARENT_GROWTH_S = "Watkins.Parent.Growth.Habit";
							const char * const PEDIGREE_WATKINS_ANCESTRAL_S = "Watkins.Ancestral.Group";

							BreedersToolkitRecord *btk_p = NULL;

							int res = CreateBreedersToolkitRecordFromTabularJSON (table_row_json_p, &btk_p);

							if (res >= 0)
								{
									res = CreateAcademicToolkitRecordFromTabularJSON (table_row_json_p, &btk_p);

									if (res >= 0)
										{

										}		/* if (res >= 0) */

								}		/* if (res >= 0) */


						}		/* if (row_size > 0) */
					else
						{
							++ num_empty_rows;
						}
				}		/* for (i = 0; i < num_rows; ++ i) */


			if (num_imported + num_empty_rows  + num_existing == num_rows)
				{
					status = OS_SUCCEEDED;
				}
			else if (num_imported > 0)
				{
					status = OS_PARTIALLY_SUCCEEDED;
				}

		}		/* if (json_is_array (plots_json_p)) */

	SetServiceJobStatus (job_p, status);

	return success_flag;
}


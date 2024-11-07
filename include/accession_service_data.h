/*
** Copyright 2014-2016 The Earlham Institute
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

/**
 * @file
 * @brief
 */
/*
 * parental_genotype_service_data.h
 *
 *  Created on: 18 Nov 2018
 *      Author: tyrrells
 */

#ifndef ACCESSION_SERVICE_DATA_H
#define ACCESSION_SERVICE_DATA_H

#include "accession_service_library.h"
#include "jansson.h"

#include "service.h"
#include "mongodb_tool.h"



/**
 * The configuration data used by the Gene Trees Service.
 *
 * @extends ServiceData
 */
typedef struct /*ACCESSION_SERVICE_LOCAL*/ AccessionServiceData
{
	/** The base ServiceData. */
	ServiceData asd_base_data;


	/**
	 * @private
	 *
	 * The MongoTool to connect to the database where our data is stored.
	 */
	MongoTool *asd_mongo_p;


	/**
	 * @private
	 *
	 * The name of the database to use.
	 */
	const char *asd_database_s;


	/**
	 * @private
	 *
	 * The collection name to use.
	 */
	const char *asd_collection_s;


} AccessionServiceData;



#ifndef DOXYGEN_SHOULD_SKIP_THIS

#ifdef ALLOCATE_ACCESSION_SERVICE_TAGS
	#define ACCESSION_PREFIX ACCESSION_SERVICE_LOCAL
	#define ACCESSION_VAL(x)	= x
	#define ACCESSION_CONCAT_VAL(x,y) = x y
#else
	#define ACCESSION_PREFIX extern
	#define ACCESSION_VAL(x)
	#define ACCESSION_CONCAT_VAL(x,y) = x y
#endif

#endif 		/* #ifndef DOXYGEN_SHOULD_SKIP_THIS */



#ifdef __cplusplus
extern "C"
{
#endif

ACCESSION_SERVICE_LOCAL AccessionServiceData *AllocateAccessionServiceData (void);


ACCESSION_SERVICE_LOCAL void FreeAccessionServiceData (AccessionServiceData *data_p);


ACCESSION_SERVICE_LOCAL bool ConfigureAccessionService (AccessionServiceData *data_p, GrassrootsServer *grassroots_p);

#ifdef __cplusplus
}
#endif


#endif /* ACCESSION_SERVICE_DATA_H */

/*
 * parental_genotype_service.h
 *
 *  Created on: 13 Jul 2018
 *      Author: billy
 */

#ifndef SERVICES_ACCESSION_SERVICE_INCLUDE_ACCESSION_SERVICE_H_
#define SERVICES_ACCESSION_SERVICE_INCLUDE_ACCESSION_SERVICE_H_


#include "accession_service_library.h"
#include "service.h"
#include "schema_keys.h"


ACCESSION_SERVICE_PREFIX const char *GTS_GENE_ID_S ACCESSION_SERVICE_VAL ("gene_id");

ACCESSION_SERVICE_PREFIX const char *GTS_CLUSTER_ID_S ACCESSION_SERVICE_VAL ("cluster_id");

ACCESSION_SERVICE_PREFIX const char *GTS_GENETREE_S ACCESSION_SERVICE_VAL ("genetree");

ACCESSION_SERVICE_PREFIX const char *GTS_GENE_SEQUENCE_S ACCESSION_SERVICE_VAL ("gene_sequence");

ACCESSION_SERVICE_PREFIX const char *GTS_ALIGNMENT_S ACCESSION_SERVICE_VAL ("alignment");



#define ACCESSION_GROUP_ALIAS_PREFIX_S "accession"


#ifdef __cplusplus
extern "C"
{
#endif


/**
 * Get the Service available for running the DFW Field Trial Service.
 *
 * @param user_p The User for the user trying to access the services.
 * This can be <code>NULL</code>.
 * @return The ServicesArray containing the DFW Field Trial Service. or
 * <code>NULL</code> upon error.
 *
 */
ACCESSION_SERVICE_API ServicesArray *GetServices (User *user_p, GrassrootsServer *grassroots_p);


/**
 * Free the ServicesArray and its associated DFW Field Trial Service.
 *
 * @param services_p The ServicesArray to free.
 *
 */
ACCESSION_SERVICE_API void ReleaseServices (ServicesArray *services_p);



ACCESSION_SERVICE_LOCAL bool AddErrorMessage (ServiceJob *job_p, const json_t *value_p, const char *error_s, const int index);

#ifdef __cplusplus
}
#endif


#endif /* SERVICES_ACCESSION_SERVICE_INCLUDE_ACCESSION_SERVICE_H_ */

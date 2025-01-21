/*
 * plane_line.h
 *
 *  Created on: 21 Jan 2025
 *      Author: tyrrells
 */

#ifndef SERVICES_ACCESSIONS_INCLUDE_PLANT_LINE_H_
#define SERVICES_ACCESSIONS_INCLUDE_PLANT_LINE_H_


#include "accession_record.h"
#include "academic_toolkit.h"
#include "breeders_toolkit.h"
#include "pedigree.h"

#include "accession_service_library.h"


typedef struct PlantLine
{
	AccessionRecord *pl_accession_p;

	AcademicToolkitRecord *pl_atk_p;


	BreedersToolkitRecord *pl_btk_p;


	PedigreeParent *pl_parent_p;


	PedigreeGrandparent *pl_grandparent_p;

} PlantLine;




#endif /* SERVICES_ACCESSIONS_INCLUDE_PLANT_LINE_H_ */

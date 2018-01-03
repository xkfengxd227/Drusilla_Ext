#ifndef __APPROXIMATE_FURTHEST_NEIGHBOR_H
#define __APPROXIMATE_FURTHEST_NEIGHBOR_H

// -----------------------------------------------------------------------------
int ground_truth(					// output ground truth (data in memory)
	int   n,							// number of data points
	int   qn,							// number of query points
	int   d,							// dimension of space
	char* data_set,						// address of data set
	char* query_set,					// address of query set
	char* truth_set);					// address of ground truth file
	
// -----------------------------------------------------------------------------
int indexing(						// build hash tables for the dataset
	int   n,							// number of data points
	int   d,							// dimension of space
	int   B,							// page size
	int   l,							// number of projections
	int   m,							// number of candidates on each proj
	char* data_set,						// address of data set
	char* data_folder,					// folder to store new format of data
	char* output_folder);				// output folder

// -----------------------------------------------------------------------------
int drusilla_select(				// c-k-AFN via DrusillaSelect
	int   qn,							// number of query points
	int   d,							// dimensionality
	char* query_set,					// address of query set
	char* truth_set,					// address of ground truth file
	char* data_folder,					// folder to store new format of data
	char* output_folder);				// output folder

#endif

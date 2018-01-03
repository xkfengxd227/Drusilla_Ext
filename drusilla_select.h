#ifndef __DRUSILLA_SELECT_H
#define __DRUSILLA_SELECT_H

// -----------------------------------------------------------------------------
//  Basic Data Structure for Approximate Furthest Neighbor Search
// -----------------------------------------------------------------------------
struct Score_Pair {
	int obj;
	float score;
};

// -----------------------------------------------------------------------------
//  Comparison Function for qsort
// -----------------------------------------------------------------------------
int score_compar(
	const void* xv,
	const void* yv);

// -----------------------------------------------------------------------------
//  Drusilla_Index: structure of DrusillaSelect, which is used to solve the 
//  problem of approximate furthest neighbor search.
// -----------------------------------------------------------------------------
class Drusilla_Index {
public:
	Drusilla_Index();				// constructor
	~Drusilla_Index();				// destructor

	// -------------------------------------------------------------------------
	void build(						// build index of DrusillaSelect
		int   n,						// number of data points
		int   d,						// number of dimensions
		int   l,						// number of projections
		int   m,						// number of candidates on each proj
		int   B,						// page size
		char* output_folder,			// output folder
		float** data);					// dataset

	// -------------------------------------------------------------------------
	int load(						// load index of DrusillaSelect
		char* output_folder);			// output folder

	// -------------------------------------------------------------------------
	int search(						// c-k-afn search via DrusillaSelect
		float* query,					// query point
		char* data_folder,				// folder to store new format of data
		MaxK_List* list);				// top-k results (return)

protected:
	int num_points_;				// number of data objects <n>
	int num_dimensions_;			// dimensionality <d>
	int num_projections_;			// number of random projections <l>
	int num_candidates_;			// number of candidates <m>
	int B_;							// page size in words <B>

	char index_set_[200];			// address of index file
	int* fn_candidates_;			// candidates on each projection
};

#endif

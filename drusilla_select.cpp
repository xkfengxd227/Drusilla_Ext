#include "headers.h"

// -----------------------------------------------------------------------------
//  Descending order for <score>
// -----------------------------------------------------------------------------
int score_compar(
	const void *xv,
	const void *yv)
{
	float x,y;

	x = ((Score_Pair *)xv)->score;
	y = ((Score_Pair *)yv)->score;

	if (x > y) return -1;
	else if (x < y) return 1;
	else return 0;
}

// -----------------------------------------------------------------------------
//  Drusilla_Index: structure of DrusillaSelect, which is used to solve the 
//  problem of approximate furthest neighbor search.
// -----------------------------------------------------------------------------
Drusilla_Index::Drusilla_Index()	// constructor
{
	num_points_= -1;
	num_dimensions_ = -1;
	num_projections_ = -1;
	num_candidates_ = -1;

	B_ = -1;
	fn_candidates_ = NULL;
}

// -----------------------------------------------------------------------------
Drusilla_Index::~Drusilla_Index()	// destructor
{
	if (fn_candidates_ != NULL) {
		free(fn_candidates_); fn_candidates_ = NULL;
	}
}

// -----------------------------------------------------------------------------
void Drusilla_Index::build(			// build index of DrusillaSelect
	int n,								// number of data points
	int d,								// number of dimensions
	int l,								// number of projections
	int m,								// number of candidates on each proj
	int B,								// page size
	char* output_folder,				// output folder
	float** data)						// dataset
{
	// -------------------------------------------------------------------------
	//  Set up parameters of DrusillaSelect
	// -------------------------------------------------------------------------
	num_points_ = n;				// init <num_points_>
	num_dimensions_ = d;			// init <num_dimensions_>
	num_projections_ = l;			// init <num_projections_>
	num_candidates_ = m;			// init <num_candidates_>
	B_ = B;							// init <B_>

									// init <index_path_>
	strcpy(index_set_, output_folder);
	strcat(index_set_, "drusilla.index");

	// -------------------------------------------------------------------------
	//  declare random variables for generating furthest neighbor candidates
	// -------------------------------------------------------------------------
	const float ANGLE = PI / 8.0f;
	int i, j, k, obj, max_obj;
	float x, max_norm;

	float* mean_center = NULL;
	float* norm = NULL;
	float* projection = NULL;
	bool*  close_angle = NULL;
	
	Score_Pair* spair = NULL;

	// -------------------------------------------------------------------------
	//  calculate the mean center of the data obejcts
	// -------------------------------------------------------------------------
	mean_center = (float*) malloc(sizeof(float) * d);
	for (i = 0; i < d; i++) {
		mean_center[i] = 0.0f;
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < d; j++) {
			mean_center[j] += data[i][j];
		}
	}
	for (i = 0; i < d; i++) {
		mean_center[i] /= (float) n;
	}

	// -------------------------------------------------------------------------
	//  move all data objects to the mean center
	// -------------------------------------------------------------------------
	for (i = 0; i < n; i++) {
		for (j = 0; j < d; j++) {
			data[i][j] -= mean_center[j];
		}
	}

	// -------------------------------------------------------------------------
	//  generate furthest neighbor candidates <fn_candidates_>
	// -------------------------------------------------------------------------
	norm = (float*) malloc(sizeof(float) * n);
	max_obj = -1;
	max_norm = -1.0f;
	for (i = 0; i < n; i++) {
		norm[i] = 0.0f;
		for (j = 0; j < d; j++) {
			x = data[i][j];
			norm[i] += (x * x);
		}
		norm[i] = sqrt(norm[i]);

		if (norm[i] > max_norm) {
			max_norm = norm[i];
			max_obj = i;
		}
	}

	fn_candidates_ = (int*) malloc(sizeof(int) * l * m);

	projection = (float*) malloc(sizeof(float) * d);
	close_angle = (bool*) malloc(sizeof(bool) * n);
	spair = (Score_Pair*) malloc(sizeof(Score_Pair) * n);

	for (i = 0; i < l; i++) {
		// ---------------------------------------------------------------------
		//  select the projection vector with largest norm and normalize it
		// ---------------------------------------------------------------------
		for (j = 0; j < d; j++) {
			projection[j] = data[max_obj][j] / norm[max_obj];
		}

		// ---------------------------------------------------------------------
		//  calculate offsets and distortions
		// ---------------------------------------------------------------------
		for (j = 0; j < n; j++) {
			spair[j].obj = j;
			close_angle[j] = false;
			
			if (norm[j] > 0.0F) {
				float offset = 0.0F;
				for (k = 0; k < d; k++) {
					offset += (data[j][k] * projection[k]);
				}

				float distortion = 0.0F;
				for (k = 0; k < d; k++) {
					x = data[j][k] - offset * projection[k];
					distortion += (x * x);
				}
				distortion = sqrt(distortion);

				spair[j].score = fabs(offset) - fabs(distortion);			
				if (atan(distortion / fabs(offset)) < ANGLE) {
					close_angle[j] = true;
				}
			}
			else if (fabs(norm[j]) < 0.000001f) {
				spair[j].score = MIN_FLT + 1.0f;
			}
			else {				
				spair[j].score = MIN_FLT;
			}
		}
		
		// ---------------------------------------------------------------------
		//  collect the objects that are well-represented by this projection
		// ---------------------------------------------------------------------
		qsort(spair, n, sizeof(Score_Pair), score_compar);
		for (j = 0; j < m; j++) {
			obj = spair[j].obj;
			//printf("obj = %d, score = %f\n", spair[j].obj, spair[j].score);

			fn_candidates_[i * m + j] = obj;
			norm[obj] = -1.0f;
		}

		// ---------------------------------------------------------------------
		//  find the next largest norm and the corresponding object
		// ---------------------------------------------------------------------
		max_obj = -1;
		max_norm = -1.0f;
		for (j = 0; j < n; j++) {
			if (norm[j] > 0.0f && close_angle[j]) {
				norm[j] = 0.0f;
			}
			if (norm[j] > max_norm) {
				max_norm = norm[j];
				max_obj = j;
			}
		}
	}

	free(mean_center);
	free(norm);
	free(projection);
	free(close_angle);
	free(spair);

	// -------------------------------------------------------------------------
	//  display the parameters of DrusillaSelect
	// -------------------------------------------------------------------------
	printf("Generating Index of DrusillaSelect (SISAP2016 paper):\n");
	printf("    Data Objects: n = %d\n", num_points_);
	printf("    Dimension:    d = %d\n", num_dimensions_);
	printf("    Projections:  l = %d\n", num_projections_);
	printf("    Candidates:   m = %d\n", num_candidates_);
	printf("    Page Size:    B = %d\n", B_);
	printf("    Index File:   %s\n\n",   index_set_);

	// -------------------------------------------------------------------------
	//  write the index to disk
	// -------------------------------------------------------------------------
	FILE* fp = NULL;
	fp = fopen(index_set_, "wb");	// open "para" file to write
	if (!fp) {
		printf("I could not create %s.\n", index_set_);
		printf("Perhaps no such folder %s?\n", output_folder);
		exit(1);
	}

	printf("Saving Index...\n");
	fwrite(&num_points_, SIZEINT, 1, fp);
	fwrite(&num_dimensions_, SIZEINT, 1, fp);
	fwrite(&num_projections_, SIZEINT, 1, fp);
	fwrite(&num_candidates_, SIZEINT, 1, fp);
	fwrite(&B_, SIZEINT, 1, fp);

	fwrite(fn_candidates_, SIZEINT, num_projections_ * num_candidates_, fp);
	fclose(fp);
}

// -----------------------------------------------------------------------------
int Drusilla_Index::load(			// load index of DrusillaSelect
	char* output_folder)				// output folder
{
	// -------------------------------------------------------------------------
	//  init the name of index file <index_set_>
	// -------------------------------------------------------------------------
	strcpy(index_set_, output_folder);
	strcat(index_set_, "drusilla.index");

	// -------------------------------------------------------------------------
	//  read index file from disk
	// -------------------------------------------------------------------------
	FILE* fp = NULL;
	fp = fopen(index_set_, "rb");
	if (!fp) {						// ensure we can open the file
		fprintf(stderr, "Could not open %s.\n", index_set_);
		exit(1);
	}

	fread(&num_points_, SIZEINT, 1, fp);
	fread(&num_dimensions_, SIZEINT, 1, fp);
	fread(&num_projections_, SIZEINT, 1, fp);
	fread(&num_candidates_, SIZEINT, 1, fp);
	fread(&B_, SIZEINT, 1, fp);

	int size = num_projections_ * num_candidates_;
	fn_candidates_ = (int*) malloc(SIZEINT * size);
	fread(fn_candidates_, SIZEINT, size, fp);
	fclose(fp);

	// -------------------------------------------------------------------------
	//  display the parameters of DrusillaSelect
	// -------------------------------------------------------------------------
	printf("Loading Index of DrusillaSelect (SISAP2016 paper):\n");
	printf("    Data Objects: n = %d\n", num_points_);
	printf("    Dimension:    d = %d\n", num_dimensions_);
	printf("    Projections:  l = %d\n", num_projections_);
	printf("    Candidates:   m = %d\n", num_candidates_);
	printf("    Page Size:    B = %d\n", B_);
	printf("    Index File:   %s\n\n",   index_set_);

	return 0;
}

// -----------------------------------------------------------------------------
int Drusilla_Index::search(			// c-k-afn search via DrusillaSelect
	float* query,						// query point
	char* data_folder,					// folder to store new format of data
	MaxK_List* list)					// top-k results (return)
{
	int i, size, obj;
	float dist;
	float* data = NULL;

	data = (float*) malloc(SIZEFLOAT * num_dimensions_);
	size = num_projections_ * num_candidates_;

	for (i = 0; i < size; i++) {
		obj = fn_candidates_[i];
		read_data(obj, num_dimensions_, B_, data, data_folder);

		dist = calc_l2_dist(data, query, num_dimensions_);
		list->insert(dist, obj + 1);
	}
	free(data);

	return size;
}

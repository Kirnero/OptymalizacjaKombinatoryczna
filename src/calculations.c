#include "calculations.h"

int calculate_eigen_values(Graph *graph, double *eigen_values_storage){
    // Allocation of memory
    gsl_matrix *GSL_Matrix = gsl_matrix_alloc(NUMBER_OF_VERTICES, NUMBER_OF_VERTICES);
    gsl_vector *eigen = gsl_vector_alloc(NUMBER_OF_VERTICES);
    gsl_eigen_symm_workspace *workspace = gsl_eigen_symm_alloc(NUMBER_OF_VERTICES);


    if (!GSL_Matrix || !eigen || !workspace) { // failed memory allocation
        fprintf(stderr, "Błąd alokacji pamięci GSL.\n");

        for (int i = 0; i < NUMBER_OF_VERTICES; i++) {
            eigen_values_storage[i] = 0.0;
        }
 
        if (GSL_Matrix) gsl_matrix_free(GSL_Matrix);
        if (eigen) gsl_vector_free(eigen);
        if (workspace) gsl_eigen_symm_free(workspace);
 
        return 1;
    }

    // Copying matrix into a good type (gsl_matrix)
    for(int i = 0; i<NUMBER_OF_VERTICES; i++){
        for(int j = 0; j<NUMBER_OF_VERTICES; j++){
            gsl_matrix_set(GSL_Matrix, i, j, (double)graph->matrix[i][j]);
        }
    }

    // All the calculations are in the magical function
    gsl_eigen_symm(GSL_Matrix, eigen, workspace);

    // Pasting eigen values into the output
    for(int i = 0; i<NUMBER_OF_VERTICES; i++){
        eigen_values_storage[i] = gsl_vector_get(eigen, i);
    }

    // Freeing up the memory
    gsl_matrix_free(GSL_Matrix);
    gsl_vector_free(eigen);
    gsl_eigen_symm_free(workspace);
    return 0;
}

int calculate_greedy_score(Graph *graph){
    double score = 0;
    double eigen = 0; // singular eigen value
    double *eigen_values = (double*)malloc(NUMBER_OF_VERTICES*sizeof(double));
    if(!eigen_values){ // failed memory allocation
        fprintf(stderr, "Błąd alokacji pamięci w obliczaniu greed_score.\n");
    }

    calculate_eigen_values(graph, eigen_values);

    for(int i = 0; i<NUMBER_OF_VERTICES; i++){
        eigen = eigen_values[i];

        if(fabs(eigen - round(eigen)) < EIGEN_PRECISION){
            score += 1; // Improve the score by the number of whole eigen values
            continue;
        }

        double score_floor = fabs(eigen - floor(eigen));
        double score_ceiling = fabs(eigen - ceil(eigen));
        score -= fmin(score_floor, score_ceiling); // Worsen the score by the distance to a whole number
    }

    graph->greed_integrity_score = score;
    free(eigen_values);
    return 0;
}
#include "misc.h"

// Zmienia pusty struct Graph na losowy graf spojny
void initialize_graph(Graph *graph){
    // Przydziela pamiec i inicjuje graf zerowy
    graph->matrix = malloc(NUMBER_OF_VERTICES * sizeof(int*));
    for(int i = 0; i<NUMBER_OF_VERTICES; i++) 
        graph->matrix[i] = calloc(NUMBER_OF_VERTICES, sizeof(int));
    graph->list_of_edges = malloc(NUMBER_OF_EDGES * sizeof(Edge));
    graph->edge_count = 0;
    graph->greed_integrity_score = 0;

    // Zmienia graf zerowy na losowy spojny
    for (int i = 1; i < NUMBER_OF_VERTICES; i++) {
        int parent = rand() % i;
        graph->matrix[i][parent] = graph->matrix[parent][i] = 1;
        graph->list_of_edges[(graph->edge_count)] = (Edge){parent, i};
        graph->edge_count++;
    }
}

// Name should tell enough
void clean_memory(Graph *graph){
    for (int i = 0; i < NUMBER_OF_VERTICES; i++) free(graph->matrix[i]);
    free(graph->matrix);
    free(graph->list_of_edges);
}

// Wypisuje macierz sasiedztwa
void printout(Graph *graph){
    for(int i = 0; i<NUMBER_OF_EDGES; i++){
        //printf("%d -- %d\n", graph->list_of_edges[i].u, graph->list_of_edges[i].v);
        //for(int j = 0; j<NUMBER_OF_VERTICES; j++){printf("%d ", graph->matrix[i][j]);} printf("\n");
    }
    printf("%f\n",graph->greed_integrity_score);
    printf("\n\n");
}

void draw(Graph *graph){
    FILE *f = fopen("graph_visual/graph.dot", "w");
    fprintf(f, "graph G {\n");

    for (int i = 0; i<NUMBER_OF_VERTICES; i++) {
        for (int j = i+1; j<NUMBER_OF_VERTICES; j++) {
            if (graph->matrix[i][j])
                fprintf(f, "  %d -- %d;\n", i, j);
        }
    }

    fprintf(f, "}\n");
    fclose(f);
}

int graph6_exists_in_file(char *filename, char *graph6) {
    FILE *file = fopen(filename, "r");
    if (!file) return 0;  // file doesn't exist → not present

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        // strip newline
        line[strcspn(line, "\r\n")] = '\0';

        if (strcmp(line, graph6) == 0) {
            fclose(file);
            return 1;  // found
        }
    }
    fclose(file);
    return 0;  // not found
}

void save_graph(Graph *graph, char *filename){
    if(NUMBER_OF_VERTICES>62){
        printf("Number of vertices too large to save in graph6 format\n");
        return;
    }
    char results[40];
    results[0] = (char)(NUMBER_OF_VERTICES + 63);

    int current_byte = 0;
    int bit_index = 0;
    int buffer_index = 1;
 
    for (int i = 0; i < NUMBER_OF_VERTICES; i++) {
        for (int j = i + 1; j < NUMBER_OF_VERTICES; j++) {
            int bit = graph->matrix[i][j]; 
 
            current_byte = (current_byte << 1) | bit;
            bit_index++;
 
            if (bit_index == 6) {
                results[buffer_index++] = (char)(current_byte + 63);
                current_byte = 0;
                bit_index = 0;
            }
        }
    }
 
    if (bit_index > 0) {
        current_byte = current_byte << (6 - bit_index);
        results[buffer_index++] = (char)(current_byte + 63);
    }
    results[buffer_index] = '\0';

    if(graph6_exists_in_file(filename,results)) return;

    FILE *file = fopen(filename,"a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    fprintf(file, "%s\n", results);
    fclose(file);
}

void swap_edges(Edge *a, Edge *b) {
    Edge temp = *a;
    *a = *b;
    *b = temp;
}

void add_edge(Graph *graph, Edge b){
    graph->matrix[b.u][b.v] = graph->matrix[b.v][b.u] = 1;
    graph->list_of_edges[graph->edge_count] = (Edge){b.u,b.v};
    graph->edge_count++;
}

void delete_edge(Graph *graph, Edge b){
    graph->matrix[b.u][b.v] = graph->matrix[b.v][b.u] = 0;
    graph->edge_count--;
    graph->list_of_edges[graph->edge_count] = (Edge){-1,-1};
}
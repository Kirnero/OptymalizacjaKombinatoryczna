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
        printf("%d -- %d\n", graph->list_of_edges[i].u, graph->list_of_edges[i].v);
    }
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

void save_graph(Graph *graph, char *filename){
    printout(graph);
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
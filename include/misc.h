#ifndef MISC_H
#define MISC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Global variables
extern int NUMBER_OF_VERTICES;
extern int NUMBER_OF_EDGES;
extern int NUMBER_OF_EDGES_MAX;

typedef struct{
    int u;
    int v;
} Edge;

typedef struct{ 
    int **matrix;
    Edge *list_of_edges;
    int edge_count;
    double greed_integrity_score;
} Graph;

void initialize_graph(Graph *graph);
void clean_memory(Graph *graph);
void printout(Graph *graph);
void draw(Graph *graph);
void save_graph(Graph *graph, char *filename); // todo
void swap_edges(Edge *a, Edge *b);
void add_edge(Graph *graph, Edge b);
void delete_edge(Graph *graph, Edge b);

#endif
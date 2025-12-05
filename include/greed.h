#ifndef GREED_H
#define GREED_H

#include "calculations.h"
#include "misc.h"

// number of random edges to check when adding an edge to graph 
extern int GREED_RAND_CANDIDATES;

void greed_add_edge(Graph *graph, Edge *candidates, int candidates_count);
int greed_graph(Graph *graph);
void greed_integral_graph();
void greed_all_integral_graph();

#endif
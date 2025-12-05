#include "greed.h"

void greed_add_edge(Graph *graph, Edge *candidates, int candidates_count){
    // To ensure there are no duplicate calculations, while still being random
    for(int i = 0; i<GREED_RAND_CANDIDATES; i++){
        int random_index = i + rand() % (candidates_count - i);
        swap_edges(&candidates[i], &candidates[random_index]);
    }

    Edge winner = candidates[0];
    double winners_score=0;
    for(int i = 0; i<GREED_RAND_CANDIDATES; i++){
        add_edge(graph, candidates[i]);
        calculate_greedy_score(graph);
        if(winners_score < graph->greed_integrity_score){
            winner = candidates[i];
            winners_score = graph->greed_integrity_score;
        }
        delete_edge(graph, candidates[i]);
    }
    add_edge(graph, winner);
    calculate_greedy_score(graph);
}

// This function wants an absolutely empty, non-initialized Graph, just as a place to store results
// Returns 0 if not integral, 1 if integral
int greed_graph(Graph *graph){
    // Stworzenie grafu spojnego
    initialize_graph(graph);
    
    int count = 0;
    Edge candidates[NUMBER_OF_EDGES_MAX-graph->edge_count];
    for(int i = 0; i<NUMBER_OF_VERTICES; i++){
        for(int j = i+1; j<NUMBER_OF_VERTICES; j++){
            if(graph->matrix[i][j]==0){
                candidates[count].u = i;
                candidates[count].v = j;
                count++;
            }
        }
    }


    while(graph->edge_count < NUMBER_OF_EDGES){
        greed_add_edge(graph, candidates, count);
    }

    // We can do that due to the formula in score calculation
    calculate_greedy_score(graph);
    //clean_memory(graph);
    if(graph->greed_integrity_score==NUMBER_OF_VERTICES){
        return 0;
    }

    return 1;
}

// Makes sure to find an integral graph
void greed_integral_graph(){
    Graph *graph;
    int found = 0;
    while(!found){
        found = greed_graph(graph);
    }
    save_graph(graph, "greed_integral_graph.txt");
}

// Makes sure to find all integral graphs
void greed_all_integral_graph(){
    while(1){
        greed_integral_graph();
    }
}
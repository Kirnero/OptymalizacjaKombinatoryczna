#include "greed.h"

void greed_add_edge(Graph *graph, Edge *candidates, int candidates_count){
    // To ensure there are no duplicate calculations, while still being random
    int count=0;
    while(count!=GREED_RAND_CANDIDATES){
        int random_index = count + rand() % (candidates_count - count);
        if(candidates[random_index].u==-1) continue;
        swap_edges(&candidates[count], &candidates[random_index]);
        count++;
    }

    Edge winner = candidates[0];
    double winners_score=0-NUMBER_OF_EDGES; // just a big negative number
    int winners_index=0;
    for(int i = 0; i<GREED_RAND_CANDIDATES; i++){
        add_edge(graph, candidates[i]);
        calculate_greedy_score(graph);
        if(winners_score < graph->greed_integrity_score){
            winner = candidates[i];
            winners_score = graph->greed_integrity_score;
            winners_index = i;
        }
        delete_edge(graph, candidates[i]);
    }
    add_edge(graph, winner);
    candidates[winners_index] = (Edge){-1,-1};
    calculate_greedy_score(graph);
}

// This function wants an absolutely empty, non-initialized Graph, just as a place to store results
// Returns 1 if not integral, 0 if integral
int greed_graph(Graph *graph){
    // Stworzenie grafu spojnego
    
    

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
    if(graph->greed_integrity_score==NUMBER_OF_VERTICES){
        return 1;
    }

    return 0;
}

// Makes sure to find an integral graph
void greed_integral_graph(){
    int found = 0;
    Graph graph;
    while(!found){
        initialize_graph(&graph);
        found = greed_graph(&graph);
        if (found){
            save_graph(&graph, "greed_graphs");
            
        }
        printout(&graph);
        clean_memory(&graph);
    }
}

// Makes sure to find all integral graphs
void greed_all_integral_graph(){
    for(int i = 0; i<GREED_TARGET_NUMBER; i++){
        greed_integral_graph();
    }
}
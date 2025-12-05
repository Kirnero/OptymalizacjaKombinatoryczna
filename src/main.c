#include "greed.h"

int NUMBER_OF_VERTICES;
int NUMBER_OF_EDGES;
int NUMBER_OF_EDGES_MAX;
int GREED_RAND_CANDIDATES;
int GREED_TARGET_NUMBER;

int main(int argc, char* argv[]) {

    if(argc > 2) {
        NUMBER_OF_VERTICES = atoi(argv[1]);
        NUMBER_OF_EDGES = atoi(argv[2]);
    } else {
        NUMBER_OF_VERTICES = 15;
        NUMBER_OF_EDGES = 66;
    }
    NUMBER_OF_EDGES_MAX = (NUMBER_OF_VERTICES*(NUMBER_OF_VERTICES-1))/2;
    if(argc > 3 && atoi(argv[3])>0){
        GREED_RAND_CANDIDATES = atoi(argv[3]);
    }
    else{
        GREED_RAND_CANDIDATES = (floor(NUMBER_OF_EDGES_MAX*0.33) < NUMBER_OF_EDGES_MAX-NUMBER_OF_EDGES) ? floor(NUMBER_OF_EDGES_MAX*0.33) : NUMBER_OF_EDGES_MAX-NUMBER_OF_EDGES;
    }
    if(argc > 4){
        GREED_TARGET_NUMBER = atoi(argv[4]);
    }
    else{
        GREED_TARGET_NUMBER = 5;
    }
    
    srand(time(NULL));
    greed_all_integral_graph();

    return 0;
}
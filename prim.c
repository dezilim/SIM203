#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// function which takes in a distance list wrt the current node and an inSet list, returns the vertice index of smallest weight
int minNodeIndex(float distTo[], bool inSet[], int V, float INF){   
    float minVal = INF;
    int minIndex;

    for(int v = 0 ; v < V; v++){
        // if a vertice is not in the set already and the distance to it from the current node is less than the current minVal, take as min
        if (inSet[v] == false && distTo[v] < minVal){
            minVal = distTo[v] ; minIndex = v;
        }
    }
    return minIndex;
}

// function that prints the elements of a float list
void printList_float(float myList[], int V){   
    printf("[ ");
    for(int i = 0; i < V; i ++){
        printf("%f ", myList[i]);
    }
    printf("]\n");
}

// function that prints the elements of an integer list
void printList_int(int myList[], int V){   
    printf("[ ");
    for(int i = 0; i < V; i ++){
        printf("%d ", myList[i]);
    }
    printf("]\n");
}

// function that prints the elements of a boolean list
void printList_bool(bool myList[], int V){   
    printf("[ ");
    for(int i = 0; i < V; i ++){
        printf("%d ", myList[i]);
    }
    printf("]\n");
}


/* Implementation of Prim's algorithm: 
entry: Number of nodes and the graph of the problem
exit: parent list which indicates the parent of each node in order */
int* primalgo(int V, float* graph[]){

    // print the graph as it is 
    printf("-------- Initial graph --------");
    for(int i=0; i<V; i++){
        printf("[");
        for(int j=0; j<V; j++){
            printf(" %f ", graph[i][j]);
        }
        printf("]\n");
    }
    float tol = 1e-3;   // the tolerance for float comparison to zero
    bool* inSet = malloc(V*sizeof(*inSet)); // true means we take the vertice to be in S already
    if(inSet == NULL){
        fprintf(stderr, "Failed to allocate memory for inSet\n");
        exit(-1);
    }
    float* distTo = malloc(V*sizeof(*distTo));
    if(distTo == NULL){
        fprintf(stderr, "Failed to allocate memory for distTo\n");
        exit(-1);
    }
    int* parent = malloc(V*sizeof(*parent));    // returned array
    if(parent == NULL){
        fprintf(stderr, "Failed to allocate memory for parent\n");
        exit(-1);
    }
    int currNode;
    float INF = 99999.;


    //int graph[V][V] = {{0,2,0,6,0},{2,0,3,8,5},{0,3,0,0,7},{6,8,0,0,9},{0,5,7,9,0}};

    //Initialise set to contain just the first node
    for (int i = 0; i < V; i++){   
        inSet[i] = false;
        parent[i] = 0;
    }
    currNode = 0; inSet[0] = true; // starting from the first node
    
    // run through all vertices except the first one and write the distance from currnode
    for (int v = 1 ; v < V; v++){
        // make everything infinite first
        distTo[v] = INF; distTo[currNode] = 0.;
        if(graph[currNode][v] > tol){
            distTo[v] = graph[currNode][v];
        }
    }


    /* start algorithm */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */

    for(int step = 0; step < V-1; step ++){

        printf("Iteration: %d\nCurrent node: %d\n", step, currNode);
        printf("Distance from current node list: ");
        printList_float(distTo, V); 
        printf("In Set list: ");
        printList_bool(inSet, V);
        printf("Parent list: ");
        printList_int(parent, V); 
        printf("--------------------------------------------\n");

        // update current node and put it in the set
        currNode = minNodeIndex(distTo, inSet, V, INF);
        inSet[currNode] = true;

        // update distTo
        for(int v = 0 ; v < V; v++){
            // only update distance if is smaller than the current distance we have, if it's not zero and if it is not already in the set 
            if (!inSet[v] && graph[currNode][v] < distTo[v] && graph[currNode][v]){
                distTo[v] = graph[currNode][v];
                parent[v] = currNode;
            }
        }

        
    }

    printf("\n___________End of Prim's Algorithm___________ \n"); 
    printf("Result:\n");
    printf("Parent ----- Distance ------- City\n");

    for(int v = 1; v< V; v++){
        printf("[%d] ------- %f ------- [%d]\n", parent[v], graph[v][parent[v]], v);
    }

    // parent[0] is not used since the first node has no parent! Use it to store the total weight of the reslut :-)
    for(int v = 0; v < V; v++){
        parent[0] += (int)graph[v][parent[v]];
    }

    // freeing the memory that is no longer used
    free(inSet);
    free(distTo);

    return parent;
    

}
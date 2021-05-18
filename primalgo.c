
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define V 5

int main() {
    bool inSet[V]; // true means we take the vertice to be in S already
    int distTo[V], parent[V], weight[V]; 
    int currNode; 
    int INF = 9999;


    int graph[V][V] = {{0,2,0,6,0},{2,0,3,8,5},{0,3,0,0,7},{6,8,0,0,9},{0,5,7,9,0}};

    //Initialise set to contain just the first node
    for (int i = 0; i < V; i++) 
    {   
        inSet[i] = false;
        parent[i] = 0; weight[i] = 0;
    }
    currNode = 0; inSet[0] = true; 
    
    // run through all vertices except the first one and write the distance from currnode
    for (int v = 1 ; v < V; v++)
    {
        // make everything infinite first
        distTo[v] = INF; distTo[currNode] = 0;
        if(graph[currNode][v] != 0)
        {
            distTo[v] = graph[currNode][v];
        }
    }

    // function which takes in a distance list wrt the current node and an inSet list, returns the vertice index of smallest weight
    int minNodeIndex(int distTo[], bool inSet[])
    {   
        int minVal = INF;
        int minIndex;

        for (int v = 0 ; v < V; v++)
        {
            // if a vertice is not in the set already and the distance to it from the current node is less than the current minVal, take as min
            if (inSet[v] == false && distTo[v] < minVal)
            {
                minVal = distTo[v] ; minIndex = v;
            }
        }
        return minIndex;
    }

    void printList_int(int myList[])
    {   
        printf("[ ");
        for(int i = 0; i < V; i ++) printf("%d ", myList[i]);
        printf("]\n");
    }
    void printList_bool(bool myList[])
    {   
        printf("[ ");
        for(int i = 0; i < V; i ++) printf("%d ", myList[i]);
        printf("]\n");
    }


    /* start algorithm */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */

    for(int step = 0; step < V-1; step ++) 
    {

        printf("Iteration: %d\nCurrent node: %d\n", step, currNode);
        printf("Distance from current node list: ");
        printList_int(distTo); 
        printf("In Set list: ");
        printList_bool(inSet);
        printf("Parent list: ");
        printList_int(parent); 
        printf("--------------------------------------------");

        // update current node and put it in the set
        currNode = minNodeIndex(distTo, inSet);
        inSet[currNode] = true;

        // update distTo
        for(int v = 0 ; v < V; v++)
        {
            // only update distance if is smaller than the current distance we have, if it's not zero and if it is not already in the set 
            if ( !inSet[v] && graph[currNode][v] < distTo[v] && graph[currNode][v] )
            {
                distTo[v] = graph[currNode][v]; parent[v] = currNode; 
            }
        }

        
    }

    printf("\n___________End of Prim's Algorithm___________ \n"); 
    printf("Result:\n");
    for(int v = 1; v< V; v++)
    {
        printf("[%d] ------- %d ------- [%d]\n", parent[v], graph[v][parent[v]], v );
    }

    return 0;
    

}
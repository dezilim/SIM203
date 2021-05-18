// Compilation:
//   icc -std=c99 main.c citiesReader.c prim.c
//   gcc main.c citiesReader.c prim.c -lm

// Execution:
//   ./a.out
//   ./a.exe


#include "citiesReader.h"
#include "prim.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define R 6378
#define p 0.017453292519943295 // pi/180

int main() {

//-----------------------------------------------------------------
//--- READING cities
//-----------------------------------------------------------------

  int popMin; int choice;
  int dep = 0;

  // if big cities only, minimal population is used for the sub cities
  printf("Connect all cities of min pop : press 0; \nConnect all cities of min pop in a certain department : press 1;\nBig cities only : press 2\n");
  scanf("%i", &choice);

  

  ListOfCities* cities;
  //int** ListOfParents = malloc(94*sizeof(int*));

  // connect all min pop cities
  if (choice == 0) 
  { 
    printf("Minimal population? ");
    scanf("%i", &popMin);
    cities = citiesReader(popMin, dep, false);
  }
  // connect all min pop cities in a department
  else if (choice == 1)
  {
    printf("Which department? ");
    scanf("%i", &dep);
    printf("Minimal population? ");
    scanf("%i", &popMin);
    cities = citiesReader(popMin, dep, false);
  }

  // calculate big cities only
  else if (choice == 2)
  {
    cities = citiesReader(popMin, dep, true);   
  }


  /*
  // calculate all (big cities + min pop in each depart)
  else if (choice == 3)
  {
    printf("Minimal population? ");
    scanf("%i", &popMin);
    cities = citiesReader(popMin, dep, true);   
    for (int i = 0; i < 94; i++)
    {
      ListOfCities* cities_dep = citiesReader(popMin, dep, false);   
      int V_dep = cities_dep->number;

      float** citiesGraph_dep= malloc(V_dep*sizeof(float*));
      for(int i = 0; i< V_dep; i++)
      {
        citiesGraph_dep[i] = malloc (V_dep*sizeof(float));
      }

      for(int i =0; i < V_dep; i++)
      {
        printf("CURRENT CITY  =====  %s %i %f %f %i\n", cities_dep->name[i], cities_dep->pop[i], cities_dep->lon[i], cities_dep->lat[i], cities_dep->dep[i]);
      // run through other cities and check its distance from them 
        for (int j = 0; j < V_dep; j++)
        {
          float x_ij = R * acos(sin(p*cities_dep->lat[i])*sin(p*cities_dep->lat[j])+ cos(p*cities_dep->lon[i] - p*cities_dep->lon[j])*cos(p*cities_dep->lat[i])*cos(p*cities_dep->lat[j]));
          printf("DIST FROM %s to %s : %.2f\n", cities_dep->name[i],cities_dep->name[j], x_ij);
          citiesGraph_dep[i][j] = x_ij;
        }
      }
      int* parent_dep = primalgo(V_dep, citiesGraph_dep);
      ListOfParents[i+1] = parent_dep;
    }
    

  }*/
  



  // USING cities, allocate and fill citiesGraph
  // writes in resuCities.dat
  int V = cities->number;			// V is the number of cities (verticies in the graph)

  // allocating matrix
  float** citiesGraph= malloc(V*sizeof(float*));
  for(int i = 0; i< V; i++){
    citiesGraph[i] = malloc (V*sizeof(float));
  }

  
  printf("(name, population, lon, lat, dep)\n");
  // allocate the distances between nodes for the graph 
  for(int i =0; i < V; i++){
    printf("CURRENT CITY  =====  %s %i %f %f %i\n", cities->name[i], cities->pop[i], cities->lon[i], cities->lat[i], cities->dep[i]);
    // run through other cities and check its distance from them 
    for (int j = 0; j < V; j++){
      float x_ij = R * acos(sin(p*cities->lat[i])*sin(p*cities->lat[j])+ cos(p*cities->lon[i] - p*cities->lon[j])*cos(p*cities->lat[i])*cos(p*cities->lat[j]));
      printf("DIST FROM %s to %s : %.2f\n", cities->name[i],cities->name[j], x_ij);
      citiesGraph[i][j] = x_ij;
    }
    printf("=====================================\n");
  }
  

  
  printf("CHECK // Printing cities in prim algo form: \n");
  
  for(int i = 0; i<V; i++){
    printf("[");
    for(int j = 0; j<V; j++){
		printf(" %f ", citiesGraph[i][j]);
	  }
    printf("]\n\n");
  }
  

  //int* parent = malloc(V*sizeof(*parent));

  // float graph_test[5][5] = {{0,2,0,6,0},{2,0,3,8,5},{0,3,0,0,7},{6,8,0,0,9},{0,5,7,9,0}};
  // float *graph_test2[5] = {graph_test[0], graph_test[1], graph_test[2], graph_test[3], graph_test[4]};
  // int* parent = primalgo(V, graph_test2);
  int* parent = primalgo(V, citiesGraph);

  printf("Total weight of the graph: %d\n", parent[0]);
  printf("___________________________________________");

  // ... just to check! This line can be removed.
  //for(int i=0; i<V; i++){
  //  printf("%s %i %f %f\n", cities->name[i], cities->pop[i], cities->lon[i], cities->lat[i]);
  //}

//-----------------------------------------------------------------
//--- COMPUTING graph
//-----------------------------------------------------------------

  // [...]

  // Écriture du graphe (chaque ligne correspond à une arête)
  // !!! Ci-dessous, on écrit le graphe complet pour l'exemple
  // !!! Vous devez modifier cette commande pour écrire le graphe obtenu avec Prim

  FILE* fileOut = NULL;
  fileOut = fopen("resuGraph.dat", "w");
  for(int i=1; i<V; i++){
    fprintf(fileOut, "%i %i\n", i, parent[i]);
  }
  // for(int i=0; i<V; i++){
  //   for(int j=0; j<i; j++){
  //     fprintf(fileOut, "%i %i\n", i, j);
  //   }
  // }
  fclose(fileOut);

//-----------------------------------------------------------------
//--- DEALLOCATE arrays
//-----------------------------------------------------------------

  free(cities->name);
  free(cities->pop);
  free(cities->lon);
  free(cities->lat);
  free(cities->dep);
  free(cities);

  for(int i = 0; i< V; i++){
    free(citiesGraph[i]);
  }
  free(citiesGraph);
  
  free(parent);

  return 0;
}

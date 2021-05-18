#ifndef PRIM_H
#define PRIM_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int minNodeIndex(int distTo[], bool inSet[], int V, int INF);

void printList_float(float myList[], int V);

void printList_int(int myList[], int V);

void printList_bool(bool myList[], int V);

int* primalgo(int V, float* graph[]);



#endif
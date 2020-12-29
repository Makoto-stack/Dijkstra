#ifndef GRAPHM_H
#define GRAPHM_H
#include "nodedata.h"
#include <iostream>
#include <fstream>
#include <climits>
#include <string>
#include <sstream>
#include <stack>
using namespace std;

class GraphM {

public:

GraphM(); //constuctor
void buildGraph(ifstream& infile);  //build graph
void insertEdge(int start, int finish, int cost); //insert an edge
void removeEdge(int start, int finish); //remove an edge
void findShortestPath(); // find shortest path
void displayAll(); // display all paths
void display(int fromNode, int toNode); //display path from one node to another

private:

struct TableType {
  bool visited;          // whether node has been visited
  int dist;              // shortest distance from source known so far
  int path;              // previous node in path of min dist
};

static const int MAXNODES = 100;
NodeData data[MAXNODES];              // data for graph nodes
int C[MAXNODES][MAXNODES];            // Cost array, the adjacency matrix
int size;                             // number of nodes in the graph
TableType T[MAXNODES][MAXNODES];      // stores visited, distance, path

};

#endif
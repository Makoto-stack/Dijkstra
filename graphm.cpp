#include "graphm.h"

/*
Constructor for GraphM
Pre: no graph exists
Post: graph with all variables intialized
*/
GraphM::GraphM(){
  for(int i = 0; i < MAXNODES; i++){
    data[i] = NodeData();
  }
  for(int i = 0; i < MAXNODES; i++){
    for(int j = 0; j < MAXNODES; j++){
      C[i][j] = 0;
    }
  }
  size = 0;
  for(int i = 0; i < MAXNODES; i++){
    for(int j = 0; j < MAXNODES; j++){
      T[i][j].visited = false;
      T[i][j].dist = INT_MAX;
      T[i][j].path = 0;
    }
  }
}

/*
Creates a graph from file
Pre: graph is empty
Post: graph is full with data from text file
*/
void GraphM::buildGraph(ifstream& infile){
  string s;
  getline(infile, s);
  if(infile.eof()){
    return;
  }
  size = stoi(s);

  for(int i = 1; i <= size; i++){
    data[i].setData(infile);
  }

  while(true){
    int start;
    int finish;
    int cost;

    getline(infile, s);
    string delimiter = " ";
    string token = s.substr(0, s.find(delimiter));
    start = stoi(token);
    if(start == 0){
      break;
    }
    s.erase(0, s.find(delimiter) + delimiter.length());
    size_t index = 0;
    while(index == s.find(delimiter)){
      s.erase(0, 1);
    }
    token = s.substr(0, s.find(delimiter));
    finish = stoi(token);
    s.erase(0, s.find(delimiter) + delimiter.length());
    while(index == s.find(delimiter)){
      s.erase(0, 1);
    }
    token = s.substr(0, s.find(delimiter));
    cost = stoi(token);

    C[start][finish] = cost;
  }
}

/*
Inserts an edge
Pre: graph has original edges
Post: graph has new specified edge
*/
void GraphM::insertEdge(int start, int finish, int cost){
  C[start][finish] = cost;
}

/*
removes an edge
Pre: graph has original edges
Post: specified edge removed from graph
*/
void GraphM::removeEdge(int start, int finish){
  C[start][finish] = 0;
}

/*
shortest path algorithm
Pre: 2D tabletype array is empty
Post: 2D tabletype array is full and can be used to calculate shortest paths
*/
void GraphM::findShortestPath(){
  for(int source = 1; source <= size; source++){
    T[source][source].dist = 0;
    T[source][source].visited = true;
    T[source][source].path = source;
    
    int current = source;

    for(int i = 1; i <= size; i++){
      for(int j = 1; j <= size; j++){
        if(C[current][j] != 0 && T[source][j].visited == false){
          if(T[source][current].dist + C[current][j] < T[source][j].dist){
            T[source][j].dist = T[source][current].dist + C[current][j];
            T[source][j].path = current;
          }
        }
      }

      int minDist = INT_MAX;
      int indexMin;

      for(int k = 1; k <= size; k++){
        if(T[source][k].dist < minDist && T[source][k].visited == false){
          minDist = T[source][k].dist;
          indexMin = k;
        }
      }

      T[source][indexMin].visited = true;
      current = indexMin;
    }
  }
}

/*
displays every single shortest path with dijkstra
Pre: console empty
Post: console prints all shortest paths, formatted
*/
void GraphM::displayAll(){
  cout << "Description          " << "From    " << "To    " << "Dijkstra's    " << "Path" << endl;
  for(int i = 1; i <= size; i++){
    cout << data[i] << endl;
    for(int j = 1; j <= size; j++){
      if(j != i){
        cout << "                      " << i << "      " << j << "      ";
        if (T[i][j].dist != INT_MAX){
          stack<int> pathStack;
          int current = j;
          pathStack.push(current);
          while(true){
            if(current == i){
              break;
            }
            pathStack.push(T[i][current].path);
            current = T[i][current].path;
          }
          cout << T[i][j].dist << "          ";
          while(!pathStack.empty()){
            cout << pathStack.top() << " ";
            pathStack.pop();
          }
          cout << endl;
        }
        else{
          cout << "---" << "         " << endl;
        }
      }
    }
  }
}

/*
prints specified shortest path from one node to another
Pre: console is empty
Post: console prints specified shortest path
*/
void GraphM::display(int fromNode, int toNode){
  cout << fromNode << "    " << toNode << "    ";
  if(T[fromNode][toNode].dist == INT_MAX){
    cout << "---        ---" << endl;
  }
  else{
    cout << T[fromNode][toNode].dist << "        ";
    stack<int> pathStack;
    int current = toNode;
    pathStack.push(current);
    while(true){
      if(current == fromNode){
        break;
      }
      pathStack.push(T[fromNode][current].path);
      current = T[fromNode][current].path;
    }
    stack<int> copyStack = pathStack;
    while(!pathStack.empty()){
      cout << pathStack.top() << " ";
      pathStack.pop();
    }
    cout << endl;
    while(!copyStack.empty()){
      cout << data[copyStack.top()] << endl;
      copyStack.pop();
    }
  }
}
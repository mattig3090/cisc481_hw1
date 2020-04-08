#include <iostream>
#include <list>
#include <string>
using namespace std;

class Graph{ // This is essentially being used to create a given node
    int id; // this will serve as the identifier for a given node for creating edges and things like that.
    int cost; // this will represent the cost to achieve this state from the previous state
    int cakes[4]; // this will represent the current stack of pancakes at this given node
    list<int> *adj; // this will be used to track what nodes are able to be traveled to from our current node
    int start; // this is gonna be a identifier for the initial node in the thing
    void DFSUtil(int v, bool visited[]);
    void buildArr(string input);
    int getCost(int cakes[], int flipSpot); // this is a little helper that we're making to help us get the cost of flipping a given set of pancakes
    void flipCakes(int cakes[], int flipSpot); // this is a helper that is going to do the actual flipping. The cost is calculated in getCost.
    
public:
    Graph(int id, int cost);
    void addEdge(int v, int w); // this will be connecting points
    void aStar();
    void DFS(int v);
};

Graph::Graph(int id, int cost){
    this->id = id;
    this->cost = cost;
    adj = new list<int>[];
}

int getCost(int flipSpot){ // the big thing for this is, since we know there's only four pancakes, we just need to know where in the stack we're inserting the spatula
    switch(flipSpot){
        case 1:
            return 3; // because in the stack, it's being inserted between the 3rd and 4th pancakes
            break;
        case 2:
            return 2; // in the stack, being inserted between 2nd and 3rd pancakes
            break;
        case 3:
            return 1; // in the stack, being inserted between the 1st and 2nd pancakes
            break;
    }
}

void Graph::flipCakes(int cakes[], int flipSpot){

}

void Graph::addEdge(int v, int w){
adj[v].push_back(w); 
}

void Graph::buildArr(string input){ // this will build the pancake stack array
    // It can be assumed that the string will be 5 characters
    // 4 characters for the pancake stack, and one telling us what the type of search is going to be 
    for(int j = 0; j < 4; j++){
        cakes[j] = stoi(input.substr(j, j+1));
    }
}

#include <iostream>
#include <list>
#include <string>
using namespace std;

class Graph{ // This is essentially being used to create a given node
    int id; // this will serve as the identifier for a given node for creating edges and things like that.
    int cost; // this will represent the cost to achieve this state from the previous state
    int cakes[4]; // this will represent the current stack of pancakes at this given node
    list<string> fringe;
    list<int> *adj; // this will be used to track what nodes are able to be traveled to from our current node
    int start; // this is gonna be a identifier for the initial node in the thing
    bool DFSUtil(int cakes[], list<string> fringe);
    void buildArr(string input);
    void goBack(int cakes[], list<string> fringe);
    int getCost(int cakes[], int flipSpot); // this is a little helper that we're making to help us get the cost of flipping a given set of pancakes
    void flipCakes(int cakes[], int flipSpot); // this is a helper that is going to do the actual flipping. The cost is calculated in getCost.
    // note. We should be calling getCost() and flipCakes() SEPARATELY!!!
    
public:
    Graph(int id, int cost);
    void addEdge(int v, int w); // this will be connecting points
    void aStar(int cakes[], list<string> fringe);
    void DFS(int cakes[], list<string> fringe);
};

Graph::Graph(int id, int cost){
    this->id = id;
    this->cost = cost;
    adj = new list<int>[];
}

int getCost(int flipSpot){ // the big thing for this is, since we know there's only four pancakes, we just need to know where in the stack we're inserting the spatula
    switch(flipSpot){
        case 0:
            cout << "Cost is 4" << endl;
            return 4;
            break;
        case 1:
            cout << "Cost is 3" << endl;
            return 3; // because in the stack, it's being inserted between the 3rd and 4th pancakes
            break;
        case 2:
            cout << "Cost is 2" << endl;
            return 2; // in the stack, being inserted between 2nd and 3rd pancakes
            break;
    }
}

void Graph::flipCakes(int cakes[], int flipSpot){ // we're essentially reversing the order of whatever pancakes we are flipping
    switch(flipSpot){ // determines what to do based on the value of 'flipSpot'
        case 0: // this is flipping literally THE ENTIRE STACK (from a comp sci perspective this makes sense but from a food perspective... WHY WOULD YOU DO THIS)
            // Obviously there's so many different ways we can do this, but for sanity's sake let's just swap the two outer cakes, and then the two inner ones
            cout << "Flipping entire stack" << endl;
            int temp = cakes[0];
            cakes[0] = cakes[3];
            cakes[3] = temp;
            temp = cakes[1];
            cakes[1] = cakes[2];
            cakes[2] = temp;
            // probably not the best way, but at the end of the day the problem's about searches, not flipping pancakes.
            break;
        case 1: // here we are flipping the top 3 cakes. We can just swap the first and third cake, as the middle one in this is virtually unaffected.
            cout << "Flipping top 3 pancakes" << endl;
            int temp = cakes[0];
            cakes[0] = cakes[2];
            cakes[2] = temp;
            break;
        case 2: // here, we're just flipping the top 2 cakes. Just swap them! Make this easy on yourself dangit!!!
            cout << "Flipping top 2 pancakes" << endl;
            int temp = cakes[0];
            cakes[0] = cakes[1];
            cakes[1] = temp;
            break;
    }
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

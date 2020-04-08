#include <iostream>
#include "graph.cpp"
#include <string>
#include "fringe.cpp"
#include <iterator>

using namespace std;

bool Graph::DFSUtil(int cakes[], list<string> fringe){ // this is just adding this set of cakes to the fringe
    // it is also gonna help us out a wee bit. As long as we successfully add something to the fringe without it already existing in the fringe, we'll return true
    // otherwise, we return false, and the search has to go back up a level in the graph
    // Also NOTE. The cake stack that should be taken in here (so "int cakes[]") should be the newly flipped stack. The DFS function should handle the flipping and the cost getting
    string cakeString = "";
    for(int i = 0; i < 3; i++){
        cakeString = cakeString + to_string(cakes[i]);
    } // converting our int array to a string so it can be easily passed through the list.
    std::list<string>::iterator it; // this gonna be what goes through and sees if the stack exists in the fringe
    it = find(fringe.begin(), fringe.end(), cakeString);
    if(it != fringe.end()){ // meaning that this already exists in the fringe, meaning there's probably a better solution to this somewhere. Just NOT HERE
        return false; // this will trigger the DFS function to use the function fringe.pop_back()
    }
    else{ // means that this cake does NOT already exist in the fringe, meaning we might find a potential winner here! (yuh)
        fringe.push_back(cakeString); // so add that bad boy into the fringe!
        return true;
    }
}

void Graph::goBack(int cakes[], list<string> fringe){ // this is gonna let us go back to a previous level in our graph. This'll be useful for both DFS and a*

}

void Graph::DFS(int cakes[], list<string> fringe){ // treating this essentially like a normal DFS. This is a traversal of all things reachable from this given node. Since we are going to likely run this
    // recursively, we can pass in the current stack of cakes that we are looking at.
    // the first time this runs, "cakes[]" represents the start state of our stack!
    if(DFSUtil(cakes, fringe) == false){ // let's check right out of the gate and make sure that we don't have to go back up a level
        goBack(cakes)
    }
}

void Graph::aStar(int cakes[], list<string> fringe){
    
}



int main(){

}


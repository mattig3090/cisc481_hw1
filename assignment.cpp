#include <iostream>
#include "graph.cpp"
#include <string>
#include <iterator>

using namespace std;

bool Graph::DFSUtil(int cakes[], list<string> fringe){ // this is just adding this set of cakes to the fringe
    // we can also, either way, add it to the list of nodes that have been explored.
    // it is also gonna help us out a wee bit. As long as we successfully add something to the fringe without it already existing in the fringe, we'll return true
    // otherwise, we return false, and the search has to go back up a level in the graph
    // Also NOTE. The cake stack that should be taken in here (so "int cakes[]") should be the newly flipped stack. The DFS function should handle the flipping and the cost getting
    string cakeString = "";
    for(int i = 0; i < 3; i++){
        cakeString = cakeString + to_string(cakes[i]);
    } // converting our int array to a string so it can be easily passed through the list.
    explored.insert({cakeString, this->id}); // we store this node in the "explored map" regardless of whether it's in the fringe or not... Something tells me we won't need this 
    this->id = this->id + 1;
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
    // what we want to do here is go back to the previous level. This is GUARANTEED to be the last element in our fringe, because we are just going straight down until
    // we have the stack we're looking at match something in the fringe, so we can just reset our stack to be the one before that. 
    // Not 100% sure about which element in the fringe we go back to, though. 
    // so since we never added the duplicate node to the fringe, just go to the node before the most recent one in the fringe and restore the stack state to THAT
    // we can probably just pop that last node off the fringe right from the get go, and then just set the stack to be the new end of the fringe... that makes sense yeah...
    // because you can't go backwards in the linked list, but you CAN access the last element using fringe.back()
    fringe.pop_back(); // so let's get that untrustworthy node off the fringe
    cout << "New last element is: " << fringe.back() << endl;
    string newState = fringe.back(); // now let's get the stack state of the previous level
    // and we're gonna do this kinda piecemeal, but we're gonna methodically replace each element in the array with the ones in the string
    for(int j = 0; j < 4; j++){
        cakes[j] = stoi(newState.substr(j, j+1)); // same as buildArr, but this is to make sure that the array is directly changed, and we don't accidentally make a new one
    } 
}

int Graph::DFS(int cakes[], list<string> fringe){ // treating this essentially like a normal DFS. This is a traversal of all things reachable from this given node. Since we are going to likely run this
    // recursively, we can pass in the current stack of cakes that we are looking at.
    // the first time this runs, "cakes[]" represents the start state of our stack!
    cout << "Running DFS" << endl;
    string cakeString = "";
    for(int i = 0; i < 3; i++){
        cakeString = cakeString + to_string(cakes[i]);
    } // converting our int array to a string so we can check if we've achieved our goal state!
    if(cakeString == "4321"){ // if we reached our goal state
        cout << "GOALLLLLLLLL" << endl;
        return 0; // stop the function!
    }
    else{ // proceed through the function
        int numFlip = 2; // this will represent how many pancakes we are gonna try to flip
        if(DFSUtil(cakes,fringe) == false){ // let's check right out of the gate and make sure that we don't have to go back up a level
            cout << "WE HAVE TO GO BACK" << endl; // this means that the stack config is already on the fringe, so we now go back up a level
            goBack(cakes, fringe);
            int costLess = costs.at(explored.at(cakeString)); // this is telling us what we need to subtract from the total cost since we are going back up a level.
            this->cost = this->cost - costLess;
            if(numFlip + 1 > 4){
                numFlip = 2;
            }
            else{ 
                numFlip++;
            }
        }
        else{ // this means that we don't have to go up a level, and also now this stack config is added to the fringe! Now we just get the cost, 
        // add that to the cost identifier map, and then flip the cakes at a given spot and then do this whole shindig over again until we have our winner!
        int flipCost = getCost(cakes, numFlip);
        cout << "Got that cost BOI" << endl;
        costs.insert({this->id - 1, flipCost}); // doing 'id-1' because the id number is incremented in DFSUtil(). ID number should be to help us with a*, but if we need to add something extra for that we can
        flipCakes(cakes, numFlip);
        cout << "Cakes flipped" << endl;
        DFS(cakes, fringe);
        }
    }
    /*int numFlip = 2; // this will represent how many pancakes we are gonna try to flip
    if(DFSUtil(cakes, fringe) == false){ // let's check right out of the gate and make sure that we don't have to go back up a level
        goBack(cakes, fringe);
        if(numFlip + 1 > 4){
            numFlip = 2;
        }
        else{
            numFlip++;
        }
    }
    else{ // this means that we don't have to go up a level, and also now this stack config is added to the fringe woo!
        
    }*/
}

void Graph::aStar(int cakes[], list<string> fringe){
    
}



int main(){
    string input;
    string theCakes;
    string search;
    list<string> fringe;
    int cakes[4];
    Graph g(1); // this is just creating a Graph object that has the first node id automatically set to 1
    cout << "Hello! Please input your pancake stack, and your preferred search method (d for DFS, a for a*)" << endl;
    cin >> input; // taking in the input from the user. Should be a 5 character string
    if(input.size() == 5){ // checking to make sure the input is 5 characters
        theCakes = input.substr(0,3);
        search = input.substr(3,4); // these two methods are separating the cakes, as well as taking out the chosen search method
        for(int j = 0; j < 4; j++){
            cakes[j] = stoi(theCakes.substr(j, j+1)); // creating our cakes array
        }
        if(search.compare("d") == 0){
            g.DFS(cakes, fringe);
        }
        else if(search.compare("a") == 0){
            g.aStar(cakes, fringe);
        }
        else{
            cout << "ERROR: Please select either 'd'(DFS) or 'a'(aStar)" << endl;
        }
    }
    else{
        cout << "ERROR: Please input a 5 character string consisting of your startng pancake order and your search selection" << endl;
    }
    return 0;
}


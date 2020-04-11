#include <iostream>
#include "graph.cpp"
#include <string>
#include <iterator>
#include <algorithm>
#include <sstream>

using namespace std;


bool Graph::DFSUtil(int cakes[]){ // this is just adding this set of cakes to the fringe
    // we can also, either way, add it to the list of nodes that have been explored.
    // it is also gonna help us out a wee bit. As long as we successfully add something to the fringe without it already existing in the fringe, we'll return true
    // otherwise, we return false, and the search has to go back up a level in the graph
    // Also NOTE. The cake stack that should be taken in here (so "int cakes[]") should be the newly flipped stack. The DFS function should handle the flipping and the cost getting
    string cakeString = "";
    for(int i = 0; i <= 3; i++){
        cakeString = cakeString + to_string(cakes[i]);
    } // converting our int array to a string so it can be easily passed through the list.
    cout << "Analyzing string: " << cakeString << endl;
    explored.insert({cakeString, this->id}); // we store this node in the "explored map" regardless of whether it's in the fringe or not... Something tells me we won't need this 
    this->id = this->id + 1;
    std::list<string>::iterator it; // this gonna be what goes through and sees if the stack exists in the fringe
    it = find(this->fringe.begin(), this->fringe.end(), cakeString);
    if(it != this->fringe.end()){ // meaning that this already exists in the fringe, meaning there's probably a better solution to this somewhere. Just NOT HERE
        return false; // this will trigger the DFS function to use the function fringe.pop_back()
    }
    else{ // means that this cake does NOT already exist in the fringe, meaning we might find a potential winner here! (yuh)
        cout << "It exists!" << endl;
        this->fringe.push_back(cakeString); // so add that bad boy into the fringe!
        cout << "added " << cakeString << " to fringe" << endl;
        return true;
    }
}

void Graph::goBack(int cakes[]){ // this is gonna let us go back to a previous level in our graph. This'll be useful for both DFS and a*
    // what we want to do here is go back to the previous level. This is GUARANTEED to be the last element in our fringe, because we are just going straight down until
    // we have the stack we're looking at match something in the fringe, so we can just reset our stack to be the one before that. 
    // Not 100% sure about which element in the fringe we go back to, though. 
    // so since we never added the duplicate node to the fringe, just go to the node before the most recent one in the fringe and restore the stack state to THAT
    // we can probably just pop that last node off the fringe right from the get go, and then just set the stack to be the new end of the fringe... that makes sense yeah...
    // because you can't go backwards in the linked list, but you CAN access the last element using fringe.back()
    this->fringe.pop_back(); // so let's get that untrustworthy node off the fringe
    cout << "New last element is: " << this->fringe.back() << endl;
    string newState = this->fringe.back(); // now let's get the stack state of the previous level
    // and we're gonna do this kinda piecemeal, but we're gonna methodically replace each element in the array with the ones in the string
    for(int j = 0; j < 4; j++){
        cakes[j] = stoi(newState.substr(j, 1)); // same as buildArr, but this is to make sure that the array is directly changed, and we don't accidentally make a new one
    } 
}

int Graph::DFS(int cakes[]){ // treating this essentially like a normal DFS. This is a traversal of all things reachable from this given node. Since we are going to likely run this
    // recursively, we can pass in the current stack of cakes that we are looking at.
    // the first time this runs, "cakes[]" represents the start state of our stack!
    cout << "Running DFS" << endl;
    string cakeString = "";
    for(int i = 0; i <= 3; i++){
        cakeString = cakeString + to_string(cakes[i]);
    } // converting our int array to a string so we can check if we've achieved our goal state!
    if(cakeString == "4321"){ // if we reached our goal state
        cout << "GOALLLLLLLLL" << endl;
        return 0; // stop the function!
    }
    else{ // proceed through the function
        int numFlip = 0; // this will represent how many pancakes we are gonna try to flip
        if(DFSUtil(cakes) == false){ // let's check right out of the gate and make sure that we don't have to go back up a level
            cout << "WE HAVE TO GO BACK" << endl; // this means that the stack config is already on the fringe, so we now go back up a level
            goBack(cakes);
            int costLess = costs.at(explored.at(cakeString)); // this is telling us what we need to subtract from the total cost since we are going back up a level.
            this->cost = this->cost - costLess;
            if(numFlip + 1 >= 2){
                numFlip = 0;
            }
            else{ 
                numFlip++; 
            }
            DFS(cakes);
        }
        else{ // this means that we don't have to go up a level, and also now this stack config is added to the fringe! Now we just get the cost, 
        // add that to the cost identifier map, and then flip the cakes at a given spot and then do this whole shindig over again until we have our winner!
        if(explored.find(cakeString) != explored.end()){ // we'll figure out a way to handle this
            cout << "Node already explored" << endl;
        }
        int flipCost = getCost(numFlip);
        cout << "Got that cost BOI" << endl;
        costs.insert({this->id - 1, flipCost}); // doing 'id-1' because the id number is incremented in DFSUtil(). ID number should be to help us with a*, but if we need to add something extra for that we can
        flipCakes(cakes, numFlip);
        cout << "Cakes flipped" << endl;
        DFS(cakes);
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


int Graph::getHeu(int cakes[]){ // this is going to give us our heuristic. The heuristic is going to be based off how many pancakes are out of order currently.
    int heuristic;
    // we can figure out our heuristic by making sure that each pancake is in it's proper spot (cake 4 is in spot 0, 3 is in 1, and so on)
    // for each cake that is NOT in it's proper position, we increment 'heuristic' by 1
    int spotCheck = 4;
    for(int i = 0; i < 3; i++){
        if(cakes[i] != spotCheck){
            heuristic++;
            spotCheck--;
        }
        else{
            spotCheck--;
        }
    }
    return heuristic;

}


int Graph::bestFlip(int cakes[]){ // this is what will use getHeu(). NOT aStar(). Should also use getCost. 
    int theChosen; // this will be the spot at which inserting our spatula will provide the best possible result.
    int totalCost; // this will represent the sum of the forward and backward costs.
    int bestCost; // this is the cost that will be connected to whatever is the best pancake flip choice
    int fCost; // this is where we will save the value gotten from getHeu(). This is forward cost.
    int bCost; // this is where we are going to save the value gotten from getCost(). This is backward cost
    int experiment[4]; // this is going to be our test dummy for flipping pancakes
    int flipCost;
    for(int i = 0; i <= 2; i++){
        for(int j = 0; j < 4; j++){ // this is merely resetting our experiment array to what it originally should be
            experiment[j] = cakes[j];
        }
        bCost = this->cost; // resets currentTotal to the global total
        flipCost = getCost(i);
        bCost += flipCost;
        flipCakes(experiment, i); // flipping the cakes so we can check the heuristic with the updated cakes.
        fCost = getHeu(experiment); // this is running the heuristic function 
        totalCost = fCost + bCost;
        if(theChosen == 0){ // seeing how theChosen can only be 2,3, or 4, if it's 0, that means it hasn't been set yet.
            theChosen = i;
        }
        else if(totalCost > 0 && totalCost < bestCost){
            bestCost = totalCost; // this means that it is a less costly path because the f(n) is smaller
            theChosen = i;
        }
    }
    this->cost = bCost;
    cout << "Cost value is: " << this->cost << " Heuristic value is: " << fCost << endl;
    return theChosen; // in aStar, the best flip spot will be used when we actually flip our pancakes for real. Here, it was just an experiment to see what works
}


int Graph::aStar(int cakes[]){
    cout << "Running aStar" << endl;
    string cakeString = "";
    int bestFlipSpot; // this is what will be passed into the flipCakes() method
    for(int i = 0; i < 3; i++){
        cakeString = cakeString + to_string(cakes[i]);
    } // converting our int array to a string so we can check if we've achieved our goal state!
    if(cakeString == "4321"){ // if we reached our goal state
        cout << "GOALLLLLLLLL" << endl;
        return 0; // stop the function! That's what this is for.
    }
    else{ // meaning we haven't reached the goal yet.
        list<string>::iterator it;
        it = find(this->fringe.begin(), this->fringe.end(), cakeString);
        if(it != this->fringe.end()){
            explored.insert({cakeString, this->id});
            this->id++;
            goBack(cakes);
            int costLess = costs.at(explored.at(cakeString));
            this->cost -= costLess;
            aStar(cakes);
        }
        else{
            explored.insert({cakeString,this->id});
            this->id++;
            bestFlipSpot = bestFlip(cakes); // determine what the next best spot to go is.
            flipCakes(cakes,bestFlipSpot); // flip the pancakes based on where the next good spot is
            aStar(cakes); // and then run this bad boy again!
        } 
    }
    
}

// one thing I might do, instead of having all the functions be recursive, is just toss them all in a while loop that says like "while not at the goal state, do all this stuff"
// idk we can look into it since (seemingly) we have all the code. Who knows though so we can figure this out tomorrow for sure.


int main(){
    string input;
    string theCakes;
    string search;
    string digit;
    int dig;
    unordered_map<string, int> explored;
    list<string> fringe;
    int cakes[4];
    Graph g(1, 0, fringe); // this is just creating a Graph object that has the first node id automatically set to 1
    cout << "Hello! Please input your pancake stack!" << endl;
    cin >> input; // taking in the input from the user. Should be a 5 character string
    if(input.size() == 4){ // checking to make sure the input is 5 characters
        for(int j = 0; j <= 3; j++){
            digit = input.substr(j, 1);
            stringstream(digit) >> dig;
            cakes[j] = dig; // creating our cakes array
        }
    }
    else{
        cout << "ERROR: Please input a 4 character string consisting of your starting pancake stack!" << endl;
    }
    cout << "Awesome! Now choose your search method! Type 'd' for DFS, or 'a' for aStar! " << endl;
    cin >> input;
    if(search.compare("d") != 0){
        g.DFS(cakes);
    }
    else if(search.compare("a") != 0){
        g.aStar(cakes);
    }
    else{
        cout << "ERROR: Please type either 'd' for DFS, or 'a' for aStar " << endl;
    }
    return 0;
}


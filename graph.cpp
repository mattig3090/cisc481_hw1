#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
using namespace std;

class Graph{ // This is essentially being used to create a given node
    int id; // this will serve as the identifier for a given node for creating edges and things like that.
    //int cost; // this will represent the cost to achieve this state from the previous state
    //int cakes[4]; // this will represent the current stack of pancakes at this given node
    //list<string> fringe;
    int cost; // this is the total overall cost
    unordered_map<string, int> explored;// this will represent all of the stack variations that have been visited so far, regardless of whether or not they are currently in the fringe.
    // this will be useful 
    unordered_map<int, int> costs;
    //list<int> *adj; // this will be used to track what nodes are able to be traveled to from our current node
    int start; // this is gonna be a identifier for the initial node in the thing
    bool DFSUtil(int cakes[], list<string> fringe);
    //void buildArr(string input);
    void goBack(int cakes[], list<string> fringe);
    int getHeu(int cakes[]); // this is for a*. This'll tell us how many pancakes are out of place for calculating forward cost.
    int bestFlip(int cakes[]); // this is for determining, combined with getHeu(), what the best direction to go in for getting the right answer is.
    int getCost(int flipSpot) {// this is a little helper that we're making to help us get the cost of flipping a given set of pancakes
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
    void flipCakes(int cakes[], int flipSpot){ // this is a helper that is going to do the actual flipping. The cost is calculated in getCost.
    // note. We should be calling getCost() and flipCakes() SEPARATELY!!!
        string cakeString = "";

        for(int i = 0; i < 3; i++){
            cakeString = cakeString + to_string(cakes[i]);
        } // converting our int array to a string so it can be easily passed through the list.
        switch(flipSpot){ // determines what to do based on the value of 'flipSpot'
            case 0: // this is flipping literally THE ENTIRE STACK (from a comp sci perspective this makes sense but from a food perspective... WHY WOULD YOU DO THIS)
            // Obviously there's so many different ways we can do this, but for sanity's sake let's just swap the two outer cakes, and then the two inner ones
                {
                    cout << cakeString << "|" << endl;
                    int tempOne = cakes[0];
                    cout << "swapping " << cakes[0] << " and " << cakes[3] << endl;
                    cakes[0] = cakes[3];
                    cakes[3] = tempOne;
                    tempOne = cakes[1];
                    cout << "swapping " << cakes[1] << " and " << cakes[2] << endl;
                    cakes[1] = cakes[2];
                    cakes[2] = tempOne;
                    // probably not the best way, but at the end of the day the problem's about searches, not flipping pancakes.
                    break;
            }
            case 1: // here we are flipping the top 3 cakes. We can just swap the first and third cake, as the middle one in this is virtually unaffected.
                {
                    string ptOne = cakeString.substr(0,2);
                    string ptTwo = cakeString.substr(2,2);
                    cout << ptOne << "|" << ptTwo << endl;
                    int tempTwo = cakes[0];
                    cakes[0] = cakes[2];
                    cakes[2] = tempTwo;
                    break;
            }
            case 2: // and here we are just flipping the first two cakes. Simple swap job!!!
                {
                    string ptOne = cakeString.substr(0,1);
                    string ptTwo = cakeString.substr(1,1);
                    cout << ptOne << "|" << ptTwo << endl;
                    int tempThree = cakes[0];
                    cakes[0] = cakes[1];
                    cakes[1] = tempThree;
                    break;
            }
        }
    }
    
public:
    Graph(int id, int cost){
        this->id = id;
        this->cost = cost;
    }
    //void addEdge(int v, int w); // this will be connecting points
    int aStar(int cakes[], list<string> fringe);
    int DFS(int cakes[], list<string> fringe);
};

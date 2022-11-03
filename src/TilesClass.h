
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace std;



struct TilesClass {
    bool hidden = true;
    bool flagged = false;
    bool mine = false;
    bool gameOver = false;

    bool revealNum = false;
    int neighbors = 0;

    vector<TilesClass*> ptr;
    
    void reveal();
};




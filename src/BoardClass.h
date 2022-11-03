#include <iostream>
#include <vector>

#include "TilesClass.h"

using namespace std;




class BoardClass {
    int width;
    int height;
    int mineCount;
    int defaultmineCount;

public:
    vector<vector<TilesClass>> tilesCoord;
   BoardClass(int width, int height, int mineCount);
   int getWidth();
   int getHeight();
   int getmineCount();
   static void GetDataFromFile(string filepath, vector<BoardClass>& BoardSets);
   void setMine(string filePath);
   void setMine();
   void setNeighbors();
   int reveal(TilesClass& Tile);

   

};


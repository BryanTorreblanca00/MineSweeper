#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <ctime>

#include "BoardClass.h"

BoardClass::BoardClass(int width, int height, int mineCount){
    this->width = width;
    this->height = height;
    this->mineCount = mineCount;
    this->defaultmineCount = mineCount;
}

int BoardClass::getHeight() {
    return this->height;
}

int BoardClass::getWidth() {
    return this->width;
}

int BoardClass::getmineCount() {
    return this->mineCount;
}

void BoardClass::GetDataFromFile(string filePath, vector<BoardClass>& BoardSets) {

    ifstream inFile(filePath);

    if (inFile.is_open()) {


        int width;
        int height;
        int mineCount;



        inFile >> width;
        inFile >> height;
        inFile >> mineCount;

        BoardClass BSet(width, height, mineCount);

        BoardSets.push_back(BSet);

    }
}

void BoardClass::setMine(string filepath){
    tilesCoord.clear();



    ifstream inFile(filepath);

    int digits = 0;

    if (inFile.is_open()) {

        string lineFromFile;


        while(getline(inFile,lineFromFile)){

            vector<TilesClass> colTiles;

            for (int y = 0; y < lineFromFile.length(); y++) {
                TilesClass tile;
                if(lineFromFile.at(y) == '1'){
                    digits++;
                    tile.mine = true;
                }
                //tile.mine = true;


                colTiles.push_back(tile);
            }
            tilesCoord.push_back(colTiles);

        }
        width = tilesCoord[0].size();
        height = tilesCoord.size();

    }

    mineCount = digits;

}



void BoardClass::setMine(){

    this->mineCount = defaultmineCount;
    int row;
    int col;
    //uniform_int_distribution<int> dist(min,max);

    tilesCoord.clear();

    for(int x = 0; x < height; x++){

        vector<TilesClass> colTiles;

        for (int y = 0; y < width; y++) {
            TilesClass tile;

            //tile.mine = true;


            colTiles.push_back(tile);
        }
        tilesCoord.push_back(colTiles);

    }

    for (int i = 0; i < mineCount; i++){

        row = rand() % height;
        col = rand() % width;

        if (tilesCoord[row][col].mine){
            i--;
        }

        tilesCoord[row][col].mine = true;
    }

}

void BoardClass::setNeighbors() {

    for( int i = 0; i < height; i++){
        for(int k = 0; k < width; k++){
            if(i != 0 && k != 0)
            {
                if (tilesCoord[i - 1][k - 1].mine){
                    tilesCoord[i][k].neighbors++;
                }
                tilesCoord[i][k].ptr.push_back(&tilesCoord[i - 1][k - 1]);
            }
            if(i != 0)
            {
                if (tilesCoord[i - 1][k].mine){
                    tilesCoord[i][k].neighbors++;
                }
                tilesCoord[i][k].ptr.push_back(&tilesCoord[i - 1][k]);
            }
            if(i != 0 && k != width - 1)
            {
                if (tilesCoord[i - 1][k + 1].mine){
                    tilesCoord[i][k].neighbors++;
                }
                tilesCoord[i][k].ptr.push_back(&tilesCoord[i - 1][k + 1]);
            }
            if(k != 0)
            {
                if (tilesCoord[i][k - 1].mine){
                    tilesCoord[i][k].neighbors++;
                }
                tilesCoord[i][k].ptr.push_back(&tilesCoord[i][k - 1]);
            }
            if(k != width - 1)
            {
                if (tilesCoord[i][k + 1].mine){
                    tilesCoord[i][k].neighbors++;
                }
                tilesCoord[i][k].ptr.push_back(&tilesCoord[i][k + 1]);
            }
            if(i != height - 1 && k != 0)
            {
                if (tilesCoord[i + 1][k - 1].mine){
                    tilesCoord[i][k].neighbors++;
                }
                tilesCoord[i][k].ptr.push_back(&tilesCoord[i + 1][k - 1]);
            }
            if(i != height - 1)
            {
                if (tilesCoord[i + 1][k].mine){
                    tilesCoord[i][k].neighbors++;
                }
                tilesCoord[i][k].ptr.push_back(&tilesCoord[i + 1][k]);
            }
            if(i != height - 1 && k != width - 1)
            {
                if (tilesCoord[i + 1][k + 1].mine){
                    tilesCoord[i][k].neighbors++;
                }
                tilesCoord[i][k].ptr.push_back(&tilesCoord[i + 1][k + 1]);
            }
        }
    }

}

int BoardClass::reveal(TilesClass& Tile){

    if (Tile.mine || Tile.flagged){
        return 0;
    }

    if (Tile.neighbors > 0){
        Tile.hidden = false;
        Tile.revealNum = true;

        return 1;
    }

    int x = 1;
    Tile.hidden = false;

    for (int i = 0; i < Tile.ptr.size(); i++){
        if(Tile.ptr.at(i)->hidden) {
            x += reveal(*Tile.ptr.at(i));
        }
    }

    return x;
}




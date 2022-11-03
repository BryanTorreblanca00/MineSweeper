#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <fstream>
#include <sstream>

#include "BoardClass.h"


using namespace std;


int main() {
    string filepath;
    vector<BoardClass> BoardSet;
    BoardClass::GetDataFromFile("boards/config.cfg", BoardSet);
    BoardSet[0].setMine();
    BoardSet[0].setNeighbors();



    sf::Texture texture;

    texture.loadFromFile("images/tile_hidden.png");
    sf::Sprite sprite(texture);



    sf::Texture revealedTexture;
    revealedTexture.loadFromFile("images/tile_revealed.png");
    sf::Sprite revealedSprite(revealedTexture);

    map<int,sf::Texture> numOnRev;
    for(int i = 1; i <= 8; i++){

       string numFiles = "images/number_" + to_string(i) + ".png";
       sf::Texture numOnRevTexture;
        numOnRevTexture.loadFromFile(numFiles);
        numOnRev.emplace(i,numOnRevTexture);

    }
    sf::Texture faceloseTexture;
    faceloseTexture.loadFromFile("images/face_lose.png");
    sf::Sprite faceloseSprite(faceloseTexture);
#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <fstream>
#include <sstream>

#include "BoardClass.h"


    using namespace std;


    int main() {
        string filepath;
        vector<BoardClass> BoardSet;
        BoardClass::GetDataFromFile("boards/config.cfg", BoardSet);
        BoardSet[0].setMine();
        BoardSet[0].setNeighbors();



        sf::Texture texture;

        texture.loadFromFile("images/tile_hidden.png");
        sf::Sprite sprite(texture);



        sf::Texture revealedTexture;
        revealedTexture.loadFromFile("images/tile_revealed.png");
        sf::Sprite revealedSprite(revealedTexture);

        map<int,sf::Texture> numOnRev;
        for(int i = 1; i <= 8; i++){

            string numFiles = "images/number_" + to_string(i) + ".png";
            sf::Texture numOnRevTexture;
            numOnRevTexture.loadFromFile(numFiles);
            numOnRev.emplace(i,numOnRevTexture);

        }
        sf::Texture faceloseTexture;
        faceloseTexture.loadFromFile("images/face_lose.png");
        sf::Sprite faceloseSprite(faceloseTexture);

        sf::Texture facewinTexture;
        facewinTexture.loadFromFile("images/face_win.png");
        sf::Sprite facewinSprite(facewinTexture);



        sf::RenderWindow window(sf::VideoMode(BoardSet[0].getWidth() * 32, (BoardSet[0].getHeight() * 32) + 88),
                                "Minesweeper");
        bool gameOver = false;
        bool test1 = false;
        bool test2 = false;
        bool test3 = false;
        bool debug = false;
        bool gameWin = false;
        int TilesHidden = BoardSet[0].getWidth() * BoardSet[0].getHeight();


        float flagCounter = 0;
        while (window.isOpen()) {

            sf::Event event;
            while (window.pollEvent(event)) {

                if (event.type == sf::Event::Closed) {
                    window.close();
                }



                else if (event.type == sf::Event::MouseButtonPressed) {

                    if (event.mouseButton.button == sf::Mouse::Left) {


                        float x = event.mouseButton.x / 32;
                        float y = event.mouseButton.y / 32;
                        if(!gameOver) {

                            if ( y < BoardSet[0].getHeight() && BoardSet[0].tilesCoord[y][x].mine) {
                                BoardSet[0].tilesCoord[y][x].hidden = false;
                                gameOver = true;

                                gameWin = false;
                            }

                            else if(y < BoardSet[0].getHeight() && !BoardSet[0].tilesCoord[y][x].flagged && BoardSet[0].tilesCoord[y][x].hidden) {

                                TilesHidden -= BoardSet[0].reveal(BoardSet[0].tilesCoord[y][x]);

                                if(TilesHidden == BoardSet[0].getmineCount() && flagCounter == BoardSet[0].getmineCount()){
                                    gameOver = true;
                                    gameWin = true;
                                }

                            }

                            else {
                                x *= 32;
                                y *= 32;

                                if (x >= ((BoardSet[0].getWidth() * 32) + 200) / 2 && x <= ((BoardSet[0].getWidth() * 32) + 200) / 2 + 64 &&
                                    y >= (BoardSet[0].getHeight() * 32) && y < (BoardSet[0].getHeight() * 32) + 64){

                                    if (!debug) {
                                        debug = true;
                                    }
                                    else {
                                        debug = false;
                                    }




                                }


                                if (y >= (BoardSet[0].getHeight() * 32) && y < (BoardSet[0].getHeight() * 32) + 64 && (x >= ((BoardSet[0].getWidth() * 32) - 32) / 2 && x <= (((BoardSet[0].getWidth() * 32) - 32) / 2) + 64) ){
                                    gameOver = false;
                                    test1 = false;
                                    test2 = false;
                                    test3 = false;
                                    flagCounter = 0;

                                    BoardSet[0].setMine();
                                    BoardSet[0].setNeighbors();
                                    TilesHidden = BoardSet[0].getWidth() * BoardSet[0].getHeight();

                                }

                                if (x >= ((BoardSet[0].getWidth() * 32) + 325) / 2  && x <= (((BoardSet[0].getWidth() * 32) + 325) / 2) + 64 &&
                                    y >= (BoardSet[0].getHeight() * 32) && y < (BoardSet[0].getHeight() * 32) + 64){

                                    gameOver = false;
                                    test1 = true;
                                    test2 = false;
                                    test3 = false;

                                    BoardSet[0].setMine("boards/testboard1.brd");
                                    BoardSet[0].setNeighbors();
                                    flagCounter = 0;
                                    TilesHidden = BoardSet[0].getWidth() * BoardSet[0].getHeight();
                                }


                                if (x >= ((BoardSet[0].getWidth() * 32) + 450) / 2 && x <= (((BoardSet[0].getWidth() * 32) + 450) / 2) + 64 &&
                                    y >= (BoardSet[0].getHeight() * 32) && y < (BoardSet[0].getHeight() * 32) + 64){

                                    gameOver = false;
                                    test2 =  true;
                                    test1 = false;
                                    test3 = false;

                                    BoardSet[0].setMine("boards/testboard2.brd");
                                    BoardSet[0].setNeighbors();
                                    TilesHidden = BoardSet[0].getWidth() * BoardSet[0].getHeight();
                                    flagCounter = 0;
                                }


                                if (x >= ((BoardSet[0].getWidth() * 32) + 575) / 2 && x <= (((BoardSet[0].getWidth() * 32) + 575) / 2) + 64 &&
                                    y >= (BoardSet[0].getHeight() * 32) && y < (BoardSet[0].getHeight() * 32) + 64){

                                    gameOver = false;
                                    test3 = true;
                                    test1 = false;
                                    test2 = false;

                                    BoardSet[0].setMine("boards/testboard3.brd");
                                    BoardSet[0].setNeighbors();
                                    flagCounter = 0;
                                    TilesHidden = BoardSet[0].getWidth() * BoardSet[0].getHeight();

                                }

                            }


                        }


                        else {

                            x *= 32;
                            y *= 32;
                            if (y >= (BoardSet[0].getHeight() * 32) && y < (BoardSet[0].getHeight() * 32) + 64 && (x >= ((BoardSet[0].getWidth() * 32) - 32) / 2 && x <= (((BoardSet[0].getWidth() * 32) - 32) / 2) + 64) ){
                                gameOver = false;
                                test1 = false;
                                test2 = false;
                                test3 = false;
                                flagCounter = 0;

                                BoardSet[0].setMine();
                                BoardSet[0].setNeighbors();
                                TilesHidden = BoardSet[0].getWidth() * BoardSet[0].getHeight();


                            }

                            if (x >= ((BoardSet[0].getWidth() * 32) + 325) / 2  && x <= (((BoardSet[0].getWidth() * 32) + 325) / 2) + 64 &&
                                y >= (BoardSet[0].getHeight() * 32) && y < (BoardSet[0].getHeight() * 32) + 64){

                                gameOver = false;
                                test1 = true;
                                test2 = false;
                                test3 = false;
                                flagCounter = 0;
                                BoardSet[0].setMine("boards/testboard1.brd");
                                BoardSet[0].setNeighbors();
                                TilesHidden = BoardSet[0].getWidth() * BoardSet[0].getHeight();

                            }


                            if (x >= ((BoardSet[0].getWidth() * 32) + 450) / 2 && x <= (((BoardSet[0].getWidth() * 32) + 450) / 2) + 64 &&
                                y >= (BoardSet[0].getHeight() * 32) && y < (BoardSet[0].getHeight() * 32) + 64){

                                gameOver = false;
                                test2 =  true;
                                test1 = false;
                                test3 = false;
                                flagCounter = 0;
                                BoardSet[0].setMine("boards/testboard2.brd");
                                BoardSet[0].setNeighbors();
                                TilesHidden = BoardSet[0].getWidth() * BoardSet[0].getHeight();

                            }


                            if (x >= ((BoardSet[0].getWidth() * 32) + 575) / 2 && x <= (((BoardSet[0].getWidth() * 32) + 575) / 2) + 64 &&
                                y >= (BoardSet[0].getHeight() * 32) && y < (BoardSet[0].getHeight() * 32) + 64){

                                gameOver = false;
                                test3 = true;
                                test1 = false;
                                test2 = false;
                                flagCounter = 0;
                                BoardSet[0].setMine("boards/testboard3.brd");
                                BoardSet[0].setNeighbors();
                                TilesHidden = BoardSet[0].getWidth() * BoardSet[0].getHeight();

                            }

                        }


                    }

                    else if (event.mouseButton.button == sf::Mouse::Right) {
                        float x = event.mouseButton.x / 32;
                        float y = event.mouseButton.y / 32;
                        if(y < BoardSet[0].getHeight()){
                            if (BoardSet[0].tilesCoord[y][x].hidden && !gameOver) {

                                if (BoardSet[0].tilesCoord[y][x].flagged) {
                                    BoardSet[0].tilesCoord[y][x].flagged = false;
                                    flagCounter--;
                                } else {
                                    BoardSet[0].tilesCoord[y][x].flagged = true;
                                    flagCounter++;
                                }
                                if(TilesHidden == BoardSet[0].getmineCount() && flagCounter == BoardSet[0].getmineCount()){
                                    gameOver = true;
                                    gameWin = true;
                                }
                            }

                        }
                    }

                }





                window.clear();


                for (int height = 0; height < BoardSet[0].tilesCoord.size(); height++) {
                    for (int width = 0; width < BoardSet[0].tilesCoord[0].size(); width++) {
                        sprite.setPosition(width * 32, height * 32);

                        window.draw(sprite);

                        if (!BoardSet[0].tilesCoord[height][width].hidden) {
                            sf::Texture revealedTexture;

                            revealedTexture.loadFromFile("images/tile_revealed.png");
                            sf::Sprite revealedSprite(revealedTexture);
                            revealedSprite.setPosition(width * 32, height * 32);
                            window.draw(revealedSprite);
                        }

                        if (BoardSet[0].tilesCoord[height][width].flagged) {
                            sf::Texture flagTexture;

                            flagTexture.loadFromFile("images/flag.png");
                            sf::Sprite flagSprite(flagTexture);
                            flagSprite.setPosition(width * 32, height * 32);
                            window.draw(flagSprite);
                        }

                        if(gameOver && !gameWin) {
                            debug = false;
                            if (BoardSet[0].tilesCoord[height][width].mine) {
                                revealedSprite.setPosition(width * 32, height * 32);
                                window.draw(revealedSprite);
                                sf::Texture mineTexture;

                                mineTexture.loadFromFile("images/mine.png");
                                sf::Sprite mineSprite(mineTexture);
                                mineSprite.setPosition(width * 32, height * 32);
                                window.draw(mineSprite);
                            }
                        }

                        if (debug && BoardSet[0].tilesCoord[height][width].mine){
                            sf::Texture mineTexture;

                            mineTexture.loadFromFile("images/mine.png");
                            sf::Sprite mineSprite(mineTexture);
                            mineSprite.setPosition(width * 32, height * 32);
                            window.draw(mineSprite);
                        }

                        if (BoardSet[0].tilesCoord[height][width].revealNum && !BoardSet[0].tilesCoord[height][width].hidden){
                            sf::Texture numsTexture = numOnRev[BoardSet[0].tilesCoord[height][width].neighbors];
                            sf::Sprite numsSprite(numsTexture);
                            numsSprite.setPosition(width * 32,height * 32);
                            window.draw(numsSprite);
                        }




                    }
                }


                sf::Texture smileyTexture;
                smileyTexture.loadFromFile("images/face_happy.png");
                sf::Sprite smileySprite(smileyTexture);
                smileySprite.setPosition(((BoardSet[0].getWidth() * 32) - 32) / 2, BoardSet[0].getHeight() * 32);
                // ((BoardSet[0].getWidth() * 32) - 32) / 2
                sf::Texture digitsTexture;
                digitsTexture.loadFromFile("images/digits.png");


                int digitCount = BoardSet[0].getmineCount() - flagCounter;
                if (digitCount < 0){
                    sf::Sprite negativeSprite(digitsTexture, sf::IntRect(210,0,21,32));
                    negativeSprite.setPosition((BoardSet[0].getWidth()), BoardSet[0].getHeight() * 32);
                    window.draw(negativeSprite);
                    digitCount = digitCount * (-1);
                }

                int one = digitCount % 10;
                int two = (digitCount/10) % 10;
                int three = digitCount / 100;

                sf::Sprite oneSprite(digitsTexture, sf::IntRect(one * 21,0, 21,32));
                sf::Sprite twoSprite(digitsTexture, sf::IntRect(two * 21,0, 21,32));
                sf::Sprite threeSprite(digitsTexture, sf::IntRect(three * 21,0, 21,32));

                oneSprite.setPosition((BoardSet[0].getWidth() + 21 * 3), BoardSet[0].getHeight() * 32);
                twoSprite.setPosition((BoardSet[0].getWidth()) + 21 * 2, BoardSet[0].getHeight() * 32);
                threeSprite.setPosition((BoardSet[0].getWidth() + 21), BoardSet[0].getHeight() * 32);

                window.draw(oneSprite);
                window.draw(twoSprite);
                window.draw(threeSprite);

                sf::Texture debugTexture;
                debugTexture.loadFromFile("images/debug.png");
                sf::Sprite debugSprite(debugTexture);
                debugSprite.setPosition(((BoardSet[0].getWidth() * 32) + 200) / 2, BoardSet[0].getHeight() * 32);

                sf::Texture test1Texture;
                test1Texture.loadFromFile("images/test_1.png");
                sf::Sprite test1Sprite(test1Texture);
                test1Sprite.setPosition(((BoardSet[0].getWidth() * 32) + 325) / 2, BoardSet[0].getHeight() * 32);

                sf::Texture test2Texture;
                test2Texture.loadFromFile("images/test_2.png");
                sf::Sprite test2Sprite(test2Texture);
                test2Sprite.setPosition(((BoardSet[0].getWidth() * 32) + 450) / 2, BoardSet[0].getHeight() * 32);

                sf::Texture test3Texture;
                test3Texture.loadFromFile("images/test_3.png");
                sf::Sprite test3Sprite(test3Texture);
                test3Sprite.setPosition(((BoardSet[0].getWidth() * 32) + 575) / 2, BoardSet[0].getHeight() * 32);





                if(!gameOver){
                    window.draw(smileySprite);
                }

                window.draw(debugSprite);
                window.draw(test1Sprite);
                window.draw(test2Sprite);
                window.draw(test3Sprite);
                if (gameOver && !gameWin){
                    faceloseSprite.setPosition(((BoardSet[0].getWidth() * 32) - 32) / 2,BoardSet[0].getHeight() * 32);
                    window.draw(faceloseSprite);

                }

                else if (gameOver && gameWin){
                    facewinSprite.setPosition(((BoardSet[0].getWidth() * 32) - 32) / 2,BoardSet[0].getHeight() * 32);
                    window.draw(facewinSprite);

                }

                window.display();

            }
        }







        return 0;
    }


    sf::Texture facewinTexture;
    facewinTexture.loadFromFile("images/face_win.png");
    sf::Sprite facewinSprite(facewinTexture);



    sf::RenderWindow window(sf::VideoMode(BoardSet[0].getWidth() * 32, (BoardSet[0].getHeight() * 32) + 88),
                            "Minesweeper");
    bool gameOver = false;
    bool test1 = false;
    bool test2 = false;
    bool test3 = false;
    bool debug = false;
    bool gameWin = false;
    int TilesHidden = BoardSet[0].getWidth() * BoardSet[0].getHeight();


    float flagCounter = 0;
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }



           else if (event.type == sf::Event::MouseButtonPressed) {

                if (event.mouseButton.button == sf::Mouse::Left) {


                    float x = event.mouseButton.x / 32;
                    float y = event.mouseButton.y / 32;
                    if(!gameOver) {

                        if ( y < BoardSet[0].getHeight() && BoardSet[0].tilesCoord[y][x].mine) {
                            BoardSet[0].tilesCoord[y][x].hidden = false;
                            gameOver = true;

                            gameWin = false;
                        }

                        else if(y < BoardSet[0].getHeight() && !BoardSet[0].tilesCoord[y][x].flagged && BoardSet[0].tilesCoord[y][x].hidden) {

                            TilesHidden -= BoardSet[0].reveal(BoardSet[0].tilesCoord[y][x]);

                            if(TilesHidden == BoardSet[0].getmineCount() && flagCounter == BoardSet[0].getmineCount()){
                                gameOver = true;
                                gameWin = true;
                            }

                        }

                        else {
                            x *= 32;
                            y *= 32;

                            if (x >= ((BoardSet[0].getWidth() * 32) + 200) / 2 && x <= ((BoardSet[0].getWidth() * 32) + 200) / 2 + 64 &&
                                y >= (BoardSet[0].getHeight() * 32) && y < (BoardSet[0].getHeight() * 32) + 64){

                                if (!debug) {
                                    debug = true;
                                }
                                else {
                                    debug = false;
                                }




                            }


                            if (y >= (BoardSet[0].getHeight() * 32) && y < (BoardSet[0].getHeight() * 32) + 64 && (x >= ((BoardSet[0].getWidth() * 32) - 32) / 2 && x <= (((BoardSet[0].getWidth() * 32) - 32) / 2) + 64) ){
                                gameOver = false;
                                test1 = false;
                                test2 = false;
                                test3 = false;
                                flagCounter = 0;

                                BoardSet[0].setMine();
                                BoardSet[0].setNeighbors();
                                TilesHidden = BoardSet[0].getWidth() * BoardSet[0].getHeight();

                            }

                            if (x >= ((BoardSet[0].getWidth() * 32) + 325) / 2  && x <= (((BoardSet[0].getWidth() * 32) + 325) / 2) + 64 &&
                                y >= (BoardSet[0].getHeight() * 32) && y < (BoardSet[0].getHeight() * 32) + 64){

                                gameOver = false;
                                test1 = true;
                                test2 = false;
                                test3 = false;

                                BoardSet[0].setMine("boards/testboard1.brd");
                                BoardSet[0].setNeighbors();
                                flagCounter = 0;
                                TilesHidden = BoardSet[0].getWidth() * BoardSet[0].getHeight();
                            }


                            if (x >= ((BoardSet[0].getWidth() * 32) + 450) / 2 && x <= (((BoardSet[0].getWidth() * 32) + 450) / 2) + 64 &&
                                y >= (BoardSet[0].getHeight() * 32) && y < (BoardSet[0].getHeight() * 32) + 64){

                                gameOver = false;
                                test2 =  true;
                                test1 = false;
                                test3 = false;

                                BoardSet[0].setMine("boards/testboard2.brd");
                                BoardSet[0].setNeighbors();
                                TilesHidden = BoardSet[0].getWidth() * BoardSet[0].getHeight();
                                flagCounter = 0;
                            }


                            if (x >= ((BoardSet[0].getWidth() * 32) + 575) / 2 && x <= (((BoardSet[0].getWidth() * 32) + 575) / 2) + 64 &&
                                y >= (BoardSet[0].getHeight() * 32) && y < (BoardSet[0].getHeight() * 32) + 64){

                                gameOver = false;
                                test3 = true;
                                test1 = false;
                                test2 = false;

                                BoardSet[0].setMine("boards/testboard3.brd");
                                BoardSet[0].setNeighbors();
                                flagCounter = 0;
                                TilesHidden = BoardSet[0].getWidth() * BoardSet[0].getHeight();

                            }

                        }


                    }


                    else {

                        x *= 32;
                        y *= 32;
                        if (y >= (BoardSet[0].getHeight() * 32) && y < (BoardSet[0].getHeight() * 32) + 64 && (x >= ((BoardSet[0].getWidth() * 32) - 32) / 2 && x <= (((BoardSet[0].getWidth() * 32) - 32) / 2) + 64) ){
                            gameOver = false;
                            test1 = false;
                            test2 = false;
                            test3 = false;
                            flagCounter = 0;

                            BoardSet[0].setMine();
                            BoardSet[0].setNeighbors();
                            TilesHidden = BoardSet[0].getWidth() * BoardSet[0].getHeight();


                        }

                        if (x >= ((BoardSet[0].getWidth() * 32) + 325) / 2  && x <= (((BoardSet[0].getWidth() * 32) + 325) / 2) + 64 &&
                            y >= (BoardSet[0].getHeight() * 32) && y < (BoardSet[0].getHeight() * 32) + 64){

                            gameOver = false;
                            test1 = true;
                            test2 = false;
                            test3 = false;
                            flagCounter = 0;
                            BoardSet[0].setMine("boards/testboard1.brd");
                            BoardSet[0].setNeighbors();
                            TilesHidden = BoardSet[0].getWidth() * BoardSet[0].getHeight();

                        }


                        if (x >= ((BoardSet[0].getWidth() * 32) + 450) / 2 && x <= (((BoardSet[0].getWidth() * 32) + 450) / 2) + 64 &&
                            y >= (BoardSet[0].getHeight() * 32) && y < (BoardSet[0].getHeight() * 32) + 64){

                            gameOver = false;
                            test2 =  true;
                            test1 = false;
                            test3 = false;
                            flagCounter = 0;
                            BoardSet[0].setMine("boards/testboard2.brd");
                            BoardSet[0].setNeighbors();
                            TilesHidden = BoardSet[0].getWidth() * BoardSet[0].getHeight();

                        }


                        if (x >= ((BoardSet[0].getWidth() * 32) + 575) / 2 && x <= (((BoardSet[0].getWidth() * 32) + 575) / 2) + 64 &&
                            y >= (BoardSet[0].getHeight() * 32) && y < (BoardSet[0].getHeight() * 32) + 64){

                            gameOver = false;
                            test3 = true;
                            test1 = false;
                            test2 = false;
                            flagCounter = 0;
                            BoardSet[0].setMine("boards/testboard3.brd");
                            BoardSet[0].setNeighbors();
                            TilesHidden = BoardSet[0].getWidth() * BoardSet[0].getHeight();

                        }

                    }


                }

                else if (event.mouseButton.button == sf::Mouse::Right) {
                    float x = event.mouseButton.x / 32;
                    float y = event.mouseButton.y / 32;
                    if(y < BoardSet[0].getHeight()){
                    if (BoardSet[0].tilesCoord[y][x].hidden && !gameOver) {

                        if (BoardSet[0].tilesCoord[y][x].flagged) {
                            BoardSet[0].tilesCoord[y][x].flagged = false;
                            flagCounter--;
                        } else {
                            BoardSet[0].tilesCoord[y][x].flagged = true;
                            flagCounter++;
                        }
                        if(TilesHidden == BoardSet[0].getmineCount() && flagCounter == BoardSet[0].getmineCount()){
                            gameOver = true;
                            gameWin = true;
                        }
                    }

                    }
                }

            }





            window.clear();


            for (int height = 0; height < BoardSet[0].tilesCoord.size(); height++) {
                for (int width = 0; width < BoardSet[0].tilesCoord[0].size(); width++) {
                    sprite.setPosition(width * 32, height * 32);

                    window.draw(sprite);

                    if (!BoardSet[0].tilesCoord[height][width].hidden) {
                        sf::Texture revealedTexture;

                        revealedTexture.loadFromFile("images/tile_revealed.png");
                        sf::Sprite revealedSprite(revealedTexture);
                        revealedSprite.setPosition(width * 32, height * 32);
                        window.draw(revealedSprite);
                    }

                    if (BoardSet[0].tilesCoord[height][width].flagged) {
                        sf::Texture flagTexture;

                        flagTexture.loadFromFile("images/flag.png");
                        sf::Sprite flagSprite(flagTexture);
                        flagSprite.setPosition(width * 32, height * 32);
                        window.draw(flagSprite);
                    }

                    if(gameOver && !gameWin) {
                        debug = false;
                        if (BoardSet[0].tilesCoord[height][width].mine) {
                            revealedSprite.setPosition(width * 32, height * 32);
                            window.draw(revealedSprite);
                            sf::Texture mineTexture;

                            mineTexture.loadFromFile("images/mine.png");
                            sf::Sprite mineSprite(mineTexture);
                            mineSprite.setPosition(width * 32, height * 32);
                            window.draw(mineSprite);
                        }
                    }

                    if (debug && BoardSet[0].tilesCoord[height][width].mine){
                        sf::Texture mineTexture;

                        mineTexture.loadFromFile("images/mine.png");
                        sf::Sprite mineSprite(mineTexture);
                        mineSprite.setPosition(width * 32, height * 32);
                        window.draw(mineSprite);
                    }

                    if (BoardSet[0].tilesCoord[height][width].revealNum && !BoardSet[0].tilesCoord[height][width].hidden){
                        sf::Texture numsTexture = numOnRev[BoardSet[0].tilesCoord[height][width].neighbors];
                        sf::Sprite numsSprite(numsTexture);
                        numsSprite.setPosition(width * 32,height * 32);
                        window.draw(numsSprite);
                    }




                }
            }


            sf::Texture smileyTexture;
            smileyTexture.loadFromFile("images/face_happy.png");
            sf::Sprite smileySprite(smileyTexture);
            smileySprite.setPosition(((BoardSet[0].getWidth() * 32) - 32) / 2, BoardSet[0].getHeight() * 32);
                                    // ((BoardSet[0].getWidth() * 32) - 32) / 2
            sf::Texture digitsTexture;
            digitsTexture.loadFromFile("images/digits.png");


            int digitCount = BoardSet[0].getmineCount() - flagCounter;
            if (digitCount < 0){
                sf::Sprite negativeSprite(digitsTexture, sf::IntRect(210,0,21,32));
                negativeSprite.setPosition((BoardSet[0].getWidth()), BoardSet[0].getHeight() * 32);
                window.draw(negativeSprite);
                digitCount = digitCount * (-1);
            }

            int one = digitCount % 10;
            int two = (digitCount/10) % 10;
            int three = digitCount / 100;

            sf::Sprite oneSprite(digitsTexture, sf::IntRect(one * 21,0, 21,32));
            sf::Sprite twoSprite(digitsTexture, sf::IntRect(two * 21,0, 21,32));
            sf::Sprite threeSprite(digitsTexture, sf::IntRect(three * 21,0, 21,32));

            oneSprite.setPosition((BoardSet[0].getWidth() + 21 * 3), BoardSet[0].getHeight() * 32);
            twoSprite.setPosition((BoardSet[0].getWidth()) + 21 * 2, BoardSet[0].getHeight() * 32);
            threeSprite.setPosition((BoardSet[0].getWidth() + 21), BoardSet[0].getHeight() * 32);

           window.draw(oneSprite);
           window.draw(twoSprite);
           window.draw(threeSprite);

            sf::Texture debugTexture;
            debugTexture.loadFromFile("images/debug.png");
            sf::Sprite debugSprite(debugTexture);
            debugSprite.setPosition(((BoardSet[0].getWidth() * 32) + 200) / 2, BoardSet[0].getHeight() * 32);

            sf::Texture test1Texture;
            test1Texture.loadFromFile("images/test_1.png");
            sf::Sprite test1Sprite(test1Texture);
            test1Sprite.setPosition(((BoardSet[0].getWidth() * 32) + 325) / 2, BoardSet[0].getHeight() * 32);

            sf::Texture test2Texture;
            test2Texture.loadFromFile("images/test_2.png");
            sf::Sprite test2Sprite(test2Texture);
            test2Sprite.setPosition(((BoardSet[0].getWidth() * 32) + 450) / 2, BoardSet[0].getHeight() * 32);

            sf::Texture test3Texture;
            test3Texture.loadFromFile("images/test_3.png");
            sf::Sprite test3Sprite(test3Texture);
            test3Sprite.setPosition(((BoardSet[0].getWidth() * 32) + 575) / 2, BoardSet[0].getHeight() * 32);





            if(!gameOver){
                window.draw(smileySprite);
            }

            window.draw(debugSprite);
            window.draw(test1Sprite);
            window.draw(test2Sprite);
            window.draw(test3Sprite);
            if (gameOver && !gameWin){
                faceloseSprite.setPosition(((BoardSet[0].getWidth() * 32) - 32) / 2,BoardSet[0].getHeight() * 32);
                window.draw(faceloseSprite);

            }

            else if (gameOver && gameWin){
                facewinSprite.setPosition(((BoardSet[0].getWidth() * 32) - 32) / 2,BoardSet[0].getHeight() * 32);
                window.draw(facewinSprite);

            }

            window.display();

        }
    }







        return 0;
    }


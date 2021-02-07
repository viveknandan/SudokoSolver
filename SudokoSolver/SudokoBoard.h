#ifndef _SUDOKO_BOARD_H
#define _SUDOKO_BOARD_H

#include <iostream>
#include <iomanip>
#include <set>
#include <algorithm>
#include "Pos.h"
#include "Grid.h"
#include "Element.h"
namespace Sudoko
{
    class SudokoBoard
    {
    private:
        Grid<int, char> h1;
        std::map<char, Element> _listElements;
        /*Return -1 : Cannot be solved
                  0 : solved
                  >0 : Not solved
        */
        int calculateState();

        int importState(char ele);

        /*
            Export the element to the grid
        */
        void exportState(char ele);



    public:
        SudokoBoard()
        {
        }
        void init();
        void Problem_add(std::vector< std::vector<char>>& problemMatrix);

        void print();

        void getElementLocWhereNotExist(char ele, std::vector< std::pair<int, int>>& loc);

        void getElementLocWhereExist(char ele, std::vector< std::pair<int, int>>& loc);

        bool elementCanExistAt(char ele, std::pair<int, int>& loc);

        void fillPos(char ele, std::pair<int, int>& loc);

        //Elements with lowest rank should be solved first
        int getLowestRankers(std::vector<char>& result);
        int getPossiblePositions(char ele, std::vector<std::pair<int,int>>& rPos);
        int solve();
        int solve(char ele);
        int checkSolutionExist();
        void barPosition(char ele, std::pair<int, int>& loc);
        int getBoxNumber(std::pair<int, int>& pos);
        std::pair<int, int> checkBoxContains(int boxNr,char ele);
        void getBoxMissings(int boxNr,std::vector<Element>& eleList);


        int solMat();
        ~SudokoBoard()
        {

        }
    };
}

#endif
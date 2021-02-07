// SudokoSolver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SudokoBoard.h"
#define ENABLE
//#define ENABLE1
using namespace std;
int solve(Sudoko::SudokoBoard& brd, char ele)
{
    for (int r = 1; r <= 9; r++)
    {
        for (int c = 1; c <= 9; c++)
        {
            std::pair<int, int> loc(r, c);
            if (brd.elementCanExistAt(ele, loc))
            {
                cout << "{" << r << "," << c << "}";
                //check if it is unique
                bool isUnique = true;
                for (char j = '1'; j <= '9'; j++)
                {
                    if (j != ele)
                    {
                        if (brd.elementCanExistAt(j, loc))
                        {
                            isUnique = false;
                            break;
                        }
                    }
                }
                if (isUnique)
                {
                    cout << "=> Is Unique";
                    brd.fillPos(ele, loc);
                    return 0;
                }
            }
        }
    }
    return -1;
}

void solveByUniquePositions(Sudoko::SudokoBoard& brd)
{
    int res = 0;
    bool solFound = false;
    do {
        solFound = false;
        for (char ele = '1'; ele <= '9'; ele++)
        {
            cout << ele << ":" << endl;
            res = solve(brd, ele);
            if (res == 0)
            {
                cout << "Solution found for " << ele << endl;
                solFound = true;
                //continue iteration
                break;
            }
            cout << endl;
        }
        //brd.print();
        //char w = getchar();
    } while (solFound);
}
int getUnsolvedElements(Sudoko::SudokoBoard& brd, vector<Sudoko::Element>& element)
{
    Sudoko::Element ele_s;

    for (char ele = '1'; ele <= '9'; ele++)
    {
        //cout << ele << ":" << endl;
        ele_s.val = ele;
        for (int r = 1; r <= 9; r++)
        {
            for (int c = 1; c <= 9; c++)
            {
                std::pair<int, int> loc(r, c);
                if (brd.elementCanExistAt(ele, loc))
                {
                    //cout << "{" << r << "," << c << "}";
                    ele_s.loc_empty.push_back(loc);
                }
            }
            if (ele_s.loc_empty.size() != 0)
            {
                element.push_back(ele_s);
            }
        }
        //cout << endl;
    }
    return element.size();

}

int solveByHysterisis(Sudoko::SudokoBoard& brd,char ele, pair<int,int> pos)
{
    //fill pos
    //getUnsolvedElements
    // 

     //Assume this location is the solution
    brd.fillPos(ele, pos);
    solveByUniquePositions(brd);
    vector<pair<int, int>> llpos;
    int fx = brd.checkSolutionExist();
    if (fx == -1)
    {
        return -1;
    }
    if (fx == 0)
    {
        return 0;
    }
    brd.getPossiblePositions(ele, llpos);
    if (llpos.size() == 0)
    {
        return 0;
    }
    return solveByHysterisis(brd, ele, llpos.at(0));

}
void printPosList(std::vector<std::pair<int, int>>& posList)
{
    for (auto e : posList)
    {
        cout << "("<<e.first << "," << e.second <<")"<< endl;
    }
}
int main()
{
    Sudoko::SudokoBoard b1;
    char problemMatrix[9][9] = {
        {'.','2','6','.','.','.','8','1','.'},
        {'3','.','.','7','.','8','.','.','6'} ,
        {'4','.','.','.','5','.','.','.','7'} ,
        {'.','5','.','1','.','7','.','9','.'} ,
        {'.','.','3','9','.','5','1','.','.'} ,
        {'.','4','.','3','.','2','.','5','.'} ,
        {'1','.','.','.','3','.','.','.','2'} ,
        {'5','.','.','2','.','4','.','.','9'} ,
        {'.','3','8','.','.','.','4','6','.'}
    };
    vector<vector<char>> problemMatV;
    problemMatV.resize(9);
    auto it = problemMatV.begin();
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            it->push_back(problemMatrix[i][j]);
        }
        it++;
    }
    b1.init();
    b1.Problem_add(problemMatV);
    b1.print();

    int limit = 100;
    int count = 0;
    /*
    * Test Functions
    for (int i = 1; i <= 9; i++)
    {
        for (int j = 1; j <= 9; j++)
        {
            std::pair<int, int> pos(i, j);
            cout << "Box number: ("<<i<<","<<j<<")=" << b1.getBoxNumber(pos) << endl;
        }
    }
    
    
    for (int i = 1; i <= 9; i++)
    {
      
        for (char ch = '1'; ch <= '9'; ch++)
        {
            std::pair<int, int> pos = b1.checkBoxContains(i,ch);
            if (pos.first == -1)
            {
                cout << "Box "<<i<<" do not contain= " << ch << endl;
            }
            else
            {
                cout<< "Box " << i << "  contains" <<ch<<" at pos( " << pos.first<<","<<pos.second<<")" << endl;
            }
        }

    }
    */
    //Find list of position where element can exist


    //Solve by find unique list of position where element can exist
#ifdef ENABLE
    solveByUniquePositions(b1);
    cout << "Finished operations!" << endl;
    b1.print();
#endif
    //Solve further By Hysterisis
#ifdef ENABLE1
    bool cntHyst = false;
    do
    {
        vector<char> lowestRankers;
        vector<pair<int, int>> lpos;
        int rank = b1.getLowestRankers(lowestRankers);
        int nmore = 0;
       // cout << "Lowest Rank = " << rank << "=>{";
        for (auto x : lowestRankers)
        {
            //cout << x << " ";
            nmore = b1.getPossiblePositions(x, lpos);
            //cout << "Possible Position for " << x << ":" << endl;
            //printPosList(lpos);
            if (nmore > 0)
            {
                Sudoko::SudokoBoard testBrd = b1;
                for (auto epos : lpos)
                {
                    int iret = solveByHysterisis(testBrd, x, epos);
                    if (iret == 0)
                    {
                        b1 = testBrd;
                        b1.print();
                        //getchar();
                        break;
                    }
                    
                }
            }
        }
        // << "}" << endl;
        vector<Sudoko::Element > lele;
        int nele = getUnsolvedElements(b1, lele);
        if (nele == 0)
        {
            cntHyst = false;
        }
        else
        {
            cntHyst = true;
        }

    } while (cntHyst);
#endif  

#ifdef ENABLE2
    while (1)
    {
        int res = 0;
        vector<char> lowestRankers;
        int rank = b1.getLowestRankers(lowestRankers);
        cout << "Lowest Rank = " << rank;
        //for (auto x : lowestRankers)
       // {
            //cout << "=>{" << x << ",";
       // }
        //cout << "}" << endl;

        for (auto x : lowestRankers)
        {
            cout << "Solving for: " << x << endl;
            vector<pair<int, int>> possiblePosList;
            b1.getPossiblePositions(x,possiblePosList);
            while (possiblePosList.size() > 0)
            {
                std::pair<int, int> rng = possiblePosList.at(0);
                Sudoko::SudokoBoard b2 = b1; //Create copy by default copy constructor
                b2.fillPos(x, rng);
                res = b1.checkSolutionExist();
                while (res != 0 && res != -1)
                {
                    res = b2.solve(x);
                    if (res == 0)
                    {
                        b1.fillPos(x, rng);
                        b1.solve();
                    }
                    if (res == -1)
                    {
                        cout << "Position (" << rng.first << "," << rng.second << ") is barred" << endl;
                        b1.barPosition(x, rng);
                    }
                }
                b1.getPossiblePositions(x, possiblePosList);
                
            }
            b1.print();
        }
        res = b1.solve();
        b1.print();
        if (res == 0)
        {
            break;
        }
        count++;
        //if (count > limit)
        //{
          //  break;
        //}

    }
#endif
    /*
    vector<pair<int, int>> locList;
    b1.getElementLocWhereExist('1', locList);
    for (auto x : locList)
    {
        cout <<"("<< x.first << " ," << x.second <<")"<< endl;
    }
    */

    /*
    bool cont = true;
    int limit = 500;
    int count = 0;
    while (cont)
    {
        int result = b1.solve();
        if (result == -1)
        {
            cout << "Cannot be solved" << endl;
            cont = false;
        }

        if (result == 0)
        {
            cout << "Solved" << endl;
            b1.print();
            cont = false;
        }
    }
    if (count > limit)
    {
        cont = false;
        cout << "Limit exceeded. " << endl;
    }*/




}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

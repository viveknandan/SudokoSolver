// SudokoSolver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SudokoBoard.h"
using namespace std;
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
    vector<char> lowestRankers;
    int limit = 100;
    int count = 0;
    while (1)
    {
        int res = 0;
        int rank = b1.getLowestRankers(lowestRankers);
        cout << "Lowest Rank = " << rank;
        for (auto x : lowestRankers)
        {
            cout << "=>{" << x << ",";
        }
        cout << "}" << endl;

        for (auto x : lowestRankers)
        {
            res = b1.solve(x);
        }

        res = b1.solve();

        if (res == 0)
        {
            break;
        }
        count++;
        if (count > limit)
        {
            break;
        }

    }
    
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

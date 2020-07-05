#include "SudokoBoard.h"
#include "Grid.h"

namespace Sudoko
{
    int SudokoBoard::calculateState()
    {
        Element eleSt;
        int result = 0;
        for (char i = '1'; i <= '9'; i++)
        {
            eleSt = _listElements[i];
            if (eleSt.isFilled() == true) // Skip element that is already filled.
            {
                continue;
            }
            //If empty, proceed with check
            eleSt = _listElements[i];
            int sum = eleSt.loc_empty.size() + eleSt.loc_fixed.size();
            if (sum >= 9)
            {
                if (sum == 9)  //Good, found complete solution for this element
                {
                    int itr = 0;
                    while (itr = eleSt.getNextEmptyLoc() >= 0)
                    {
                        eleSt.fillLoc(itr);
                    }
                }
                if (sum >= 9)
                {
                    //Many possible location exist for this element
                    result++;
                    //Print Locations {
                    std::cout << "Possible Locations for" << "[" << eleSt.val << "] => ";
                    for (auto x : eleSt.loc_empty)
                    {
                        std::cout << "{" << x.first << "," << x.second << "} ";
                    }
                    std::cout << std::endl;
                    // } Print end;
                }

            }
            else
            {
                //No further solution exist for given state
                result = -1;
                break;
            }
        }
        return result;
    }
    int SudokoBoard::importState(char ele)
    {
        Element eleSt;
        int nMore = 0; //Store difference of number of posible and filled positions  
        eleSt.val = ele;
        h1.searchElement(ele, true, eleSt.loc_fixed);
        h1.searchElement(ele, false, eleSt.loc_empty);
        std::set<int> bar_rowIdx;
        std::set<int> bar_colIdx;
        for (auto itr : eleSt.loc_fixed)
        {
            bar_rowIdx.insert(itr.first);
            bar_colIdx.insert(itr.second);
        }
        for (int i = 0; i < eleSt.loc_empty.size(); i++)
        {
            //If empty location is present in barred state remove it
            if (bar_rowIdx.find(eleSt.loc_empty[i].first) != bar_rowIdx.end())
            {
                eleSt.loc_empty.erase(eleSt.loc_empty.begin() + i);
            }
        }
        for (int i = 0; i < eleSt.loc_empty.size(); i++)
        {
            //If the empty location is present in bared list, erase it
            if (bar_colIdx.find(eleSt.loc_empty[i].second) != bar_colIdx.end())
            {
                eleSt.loc_empty.erase(eleSt.loc_empty.begin() + i);
            }
        }

        nMore = (9 - eleSt.loc_fixed.size());
        if (nMore == 0)
        {
            eleSt.loc_empty.clear();
        }
        //This assignment should be a deep copy i.e new copy of assigned object should persist event after eleSt is destroyed
        _listElements[ele] = eleSt;
        //calculate excess possible locations.
        //nMore = eleSt.loc_empty.size() - (9-eleSt.loc_fixed.size());

        /*
        if (nMore != 0 && eleSt.loc_empty.size() < nMore)
        {
            nMore = eleSt.loc_empty.size() - nMore;
        }
        else if (nMore == 0 && eleSt.loc_empty.size() != 0)
        {
            //Remove rest if the elements
            eleSt.loc_empty.clear();
        }
        else
        {

        }
        */
        return nMore;
    }
    /*
        Export the element to the grid
    */
    void SudokoBoard::exportState(char ele)
    {
        Element eleSt = _listElements[ele];
        extern  std::map<int, int> IntToInt;
        Pos<int> pos(IntToInt, IntToInt, static_cast<int>(1));
        for (auto loc : eleSt.loc_fixed)
        {
            std::cout << "writing " << ele << "=>(" << loc.first << "," << loc.second << ")" << std::endl;
            h1.writePos(pos(loc.first, loc.second), ele);
        }
    }

    void SudokoBoard::init()
    {
        h1.create(static_cast<int>(9), static_cast<int>(9), static_cast<char>('.'));
    }
    void SudokoBoard::Problem_add(std::vector< std::vector<char>>& problemMatrix)
    {
        //Store the grid
        h1.initData(problemMatrix);
        for (char ele = '1'; ele <= '9'; ele++)
        {
            int count = importState(ele);
            std::cout << "state(" << ele << ")=>" << count << std::endl;;

        }
    }
    void SudokoBoard::print()
    {
        std::map<int, int> rowMap;
        for (int i = 1; i <= 9; i++)
        {
            rowMap[i] = i;
        }
        int cor = 1;
        Pos<int> p(rowMap, rowMap, cor);
        for (int i = 1; i <= 9; i++)
        {
            for (int j = 1; j <= 9; j++)
            {
                std::cout << std::setw(2) << h1.readPos(p(i, j));
            }
            std::cout << std::endl;
        }
    }
    void SudokoBoard::getElementLocWhereNotExist(char ele, std::vector< std::pair<int, int>>& loc)
    {
        h1.searchElement(ele, false, loc);
    }
    void SudokoBoard::getElementLocWhereExist(char ele, std::vector< std::pair<int, int>>& loc)
    {
        h1.searchElement(ele, true, loc);
    }
    bool SudokoBoard::elementCanExistAt(char ele, std::pair<int, int>& loc)
    {
        bool ret = false;
        //Element can exist in its possible empty location
        for (auto pos : _listElements[ele].loc_empty)
        {
            if (pos == loc)
            {
                ret = true;
                break;
            }
        }

        for (auto pos : _listElements[ele].loc_fixed)
        {
            if (pos == loc)
            {
                ret = true;
                break;
            }
        }
        return ret;
    }

    //Elements with lowest rank should be solved first
    int SudokoBoard::getLowestRankers(std::vector<char>& result)
    {
        std::set<int> openPos;
        std::map<char, int> element2openPos;
        for (char ele = '1'; ele <= '9'; ele++)
        {
            /*
            count = 0 , solved
            count < 0 , soultion not possible
            count > 0, solution possible
            */
            int count = importState(ele);
            element2openPos[ele] = count;
            if (openPos.find(count) == openPos.end()) //Do not insert duplicates
            {
                if (count > 0)
                    openPos.insert(count);
            }

        }
        int min = *(openPos.upper_bound(-9));
        for (char ele = '1'; ele <= '9'; ele++)
        {

            if (element2openPos[ele] == min)
            {
                result.push_back(ele);
            }
        }
        return min;
    }

    int SudokoBoard::solve()
    {
        int result = 1;

        //Initialize
        //import all sate


        for (char ele = '1'; ele <= '9'; ele++)
        {
            result = calculateState();
            if (result == -1)
            {
                break;
            }
            exportState(ele);
            importState(ele);
        }
        return result;
    }

    int SudokoBoard::solve(char ele)
    {
        //This is a memory intensive function
        int res = 0;
        //Loop until element is solved or not solvabale
        bool cont = true;
        while (cont)
        {
            //Backup the _listElements
            std::map<char, Element> backup = _listElements;
            //Get the empty location
            Element le = _listElements[ele];
            int i = le.getNextEmptyLoc();
            //Fill the location
            le.fillLoc(i);
            _listElements[ele] = le;
            //Export
            exportState(ele);
            //Import
            res = solve();
            if (res == 0 || res == -1)
            {
                cont = false;
            }
            if (res == -1)
            {
                //Solvable point reached. No more tries possible now. Solve for other elements required.
                //restore
                _listElements = backup;
            }
        }

        return res;
    }
}
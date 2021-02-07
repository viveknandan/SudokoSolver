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

    //Return number of open position
    int SudokoBoard::importState(char ele)
    {
        Element eleSt;
        int nMore = 0; //Store difference of number of posible and filled positions  
        eleSt.val = ele;
        h1.searchElement(ele, true, eleSt.loc_fixed);
        h1.searchElement(ele, false, eleSt.loc_empty);
        std::set<int> bar_rowIdx; //blacklisted row index
        std::set<int> bar_colIdx; //blacklisted col index
        for (auto itr : eleSt.loc_fixed)
        {
            bar_rowIdx.insert(itr.first);
            bar_colIdx.insert(itr.second);
        }

        bool cnt = true;
        int lp = 0;
        while (cnt)
        {
            lp = eleSt.loc_empty.size();
            for (std::vector<std::pair<int, int>>::iterator itrp = eleSt.loc_empty.begin(); itrp < eleSt.loc_empty.end(); itrp++)
            {

                int boxNr = getBoxNumber(*itrp);
                std::pair<int, int> lloc = checkBoxContains(boxNr, ele);
                if (!(lloc.first == -1 && lloc.second == -1))
                {
                    eleSt.loc_empty.erase(itrp);
                    break;
                }
                
                if (lp-- == 1)
                {
                    cnt = false;
                }
            }
            if (lp == 0)
            {
                cnt = false;
            }
            
        }
        

        std::vector<std::pair<int, int>>::iterator jptr = eleSt.loc_empty.begin();
        while (jptr != eleSt.loc_empty.end()  )
        {
            if (bar_rowIdx.find(jptr->first) != bar_rowIdx.end() || bar_colIdx.find(jptr->second) != bar_colIdx.end())
            {
                eleSt.loc_empty.erase(jptr);
                jptr = eleSt.loc_empty.begin();
            }
            else
            {
                jptr++;
            }
            
        }

        nMore = (9 - eleSt.loc_fixed.size());
        if (nMore == 0)
        {
            //eleSt.loc_empty.clear();
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
        //Return if there are no positions left to fill.
        if (_listElements[ele].loc_fixed.size() < 9)
        {
            //Element can exist in its possible empty location
            for (auto pos : _listElements[ele].loc_empty)
            {
                if (pos == loc)
                {
                        ret = true;
                    break;
                }
            }
        }
        return ret;
    }

    void SudokoBoard::fillPos(char ele, std::pair<int, int>& loc)
    {
        Element ele_s = _listElements[ele];
        //Get index of this pos
        int idx = ele_s.getEmptyLoc(loc);
 
        //FillPos
        if (idx >= 0)
        {
            ele_s.fillLoc(idx);
            _listElements[ele] = ele_s;
            exportState(ele);
            importState(ele);
        }
    }

    //Elements with lowest rank( least number of to-be-filled positons)
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

    int SudokoBoard::getPossiblePositions(char ele, std::vector<std::pair<int, int>>& rPos)
    {
        Element ele_st = _listElements[ele];
        rPos = ele_st.loc_empty;
        return (9 - ele_st.loc_fixed.size());
    }

    void SudokoBoard::barPosition(char ele, std::pair<int, int>& loc)
    {
        Element ele_st = _listElements[ele];
        for (std::vector<std::pair<int,int>>::iterator it = ele_st.loc_empty.begin(); it <= ele_st.loc_empty.end(); it++)
        {
            if (*it == loc)
            {
                ele_st.loc_empty.erase(it);
                break;
            }
        }
        _listElements[ele] = ele_st;
    }

    int SudokoBoard::getBoxNumber(std::pair<int, int>& pos)
    {
        int boxNr = 0;
        if (pos.first <= 3)
        {
            if (pos.second <= 3)
            {
                //box1
                boxNr = 1;
            }
            else if (pos.second <= 6)
            {
                //box2
                boxNr = 2;
            }
            else
            {
                //box3
                boxNr = 3;
            }

        }
        else if (pos.first <= 6)
        {
            if (pos.second <= 3)
            {
                //box4
                boxNr = 4;
            }
            else if (pos.second <= 6)
            {
                //box5
                boxNr = 5;
            }
            else
            {
                //box6
                boxNr = 6;
            }
        }
        else
        {
            if (pos.second <= 3)
            {
                //box7
                boxNr = 7;
            }
            else if (pos.second <= 6)
            {
                //box8
                boxNr = 8;
            }
            else
            {
                //box9
                boxNr = 9;
            }
        }
        return boxNr;
    }

    //returns position of found element else {-1,-1}
    std::pair<int,int> SudokoBoard::checkBoxContains(int boxNr, char ele)
    {
        std::pair<int, int> pos = { -1,-1 };
        int row = 0;
        int col = 0;
        std::map<int, int> rowMap;
        for (int i = 1; i <= 9; i++)
        {
            rowMap[i] = i;
        }
        int cor = 1;
        Pos<int> p(rowMap, rowMap, cor);
        switch (boxNr)
        {
        case 1:
            row = 3;
            col = 3;
            break;
        case 2:
            row = 3;
            col = 6;
            break;
        case 3:
            row = 3;
            col = 9;
            break;
        case 4:
            row = 6;
            col = 3;
            break;
        case 5:
            row = 6;
            col = 6;
            break;
        case 6:
            row = 6;
            col = 9;
            break;
        case 7:
            row = 9;
            col = 3;
            break;
        case 8:
            row = 9;
            col = 6;
            break;
        case 9:
            row = 9;
            col = 9;
            break;
        }

        for (int i = row - 2; i <= row; i++)
        {
            for (int j = col - 2; j <= col; j++)
            {

                
                if (ele == h1.readPos(p(i, j)))
                {
                    pos.first = i;
                    pos.second = j;
                    break;
                }
            }
        }
        return pos;
    }

    void SudokoBoard::getBoxMissings(int boxNr, std::vector<Element>& eleList)
    {
        //Element ele_s = _listElements[ele];
        int row = 0;
        int col = 0;
        switch (boxNr)
        {
        case 1:
            row = 3;
            col = 3;
            break;
        case 2:
            row = 3;
            col = 6;
            break;
        case 3:
            row = 3;
            col = 9;
            break;
        case 4:
            row = 6;
            col = 3;
            break;
        case 5:
            row = 6;
            col = 6;
            break;
        case 6:
            row = 6;
            col = 9;
            break;
        case 7:
            row = 9;
            col = 3;
            break;
        case 8:
            row = 9;
            col = 6;
            break;
        case 9:
            row = 9;
            col = 9;
            break;
        }

        for (char el = '1'; el <= '9'; el++)
        {
            Element ele_s = _listElements[el];
            std::pair<int, int> lc(-1, 1);
            for (auto loc : ele_s.loc_empty)
            {
                if (loc.first >= row-2 && loc.first <= row  )
                {
                    if (loc.second >= col - 2 && loc.second <= col)
                    {
                        eleList.push_back(ele_s);
                        break;
                    }
                    
                }
            }
        }
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
        std::cout << "Solving for: " << ele<<std::endl;
        while (cont)
        {
            //Backup the _listElements
            std::map<char, Element> backup = _listElements;
            //Get the empty location
            Element le = _listElements[ele];
            std::cout << "Number of fixed Pos: " << le.loc_fixed.size() << std::endl;;
            std::cout << "Number of Possible positions: " << le.loc_empty.size() << std::endl;
            if (res = checkSolutionExist() == -1)
            {
                return -1;
            }
            if (res == 0)
            {
                return 0;
            }
            int i = le.getNextEmptyLoc();
            std::cout << "Next empty location : " << i << std::endl;
            if (i != -1)
            {
                //Fill the location
                le.fillLoc(i);
                _listElements[ele] = le;
                //Export
                exportState(ele);
                //Import
                res = importState(ele);
                res = solve();
                //print();
                if (res == 0)
                {
                    cont = false;
                }
                else
                {
                    //res = solMat();
                }
            }
            else
            {
                res = -1;
            }
        }
        return res;
    }

    int SudokoBoard::solMat()
    {
        int res = 0;
        std::vector<char> lowestRankers;
        int rank = getLowestRankers(lowestRankers);
        std::cout << "Lowest Rank = " << rank;
        for (auto x : lowestRankers)
        {
            std::cout << "Solving for: " << x << std::endl;
            res = solve(x);
            print();
        }
        
        print();
        if (res == 0 || res == -1)
        {
            return res;
        }

    }
    int SudokoBoard::checkSolutionExist()
    {
        return calculateState();
    }
}
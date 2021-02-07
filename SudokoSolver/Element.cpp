#include "Element.h"
namespace Sudoko
{
    bool Element::isFilled()
    {
        return static_cast<bool>(loc_fixed.size() == 9);
    }
    //return idex at next empty location
    int  Element::getNextEmptyLoc()
    {
        int result = -1;
        if ((loc_empty.size() == 0) || (itr > loc_empty.size()))
        {
            return result;
        }
        else
        {
            result = itr++;
        }
 
        return result;
    }
    void Element::fillLoc(int itr)
    {
        if (itr >= 0 && itr < loc_empty.size())
        {
            //Get & then erase the element aat this position from empty list
            std::pair<int, int> ele = loc_empty[itr];
            loc_empty.erase(loc_empty.begin() + itr);
            //Move this pos to empty
            loc_fixed.push_back(ele);
        }
    }
    int Element::getEmptyLoc(std::pair<int, int> pos)
    {
        int index = 0;
        for (auto x : loc_empty)
        {
            if (x == pos)
            {
                return index;
            }
            index++;
        }
    }
    Element::Element()
    {
        itr = 0;
        loc_fixed.clear();
        loc_empty.clear();
    }
    Element::~Element()
    {
        loc_fixed.clear();
        loc_empty.clear();
    }
}
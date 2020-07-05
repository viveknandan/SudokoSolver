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
        if (loc_empty.size() == 0)
        {
            return result;
        }

        if (itr == loc_empty.size())
        {
            itr = 0;
        }
        result = itr++;
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
    Element::Element() :itr(-1)
    {
        loc_fixed.clear();
        loc_empty.clear();
    }
    Element::~Element()
    {
        loc_fixed.clear();
        loc_empty.clear();
    }
}
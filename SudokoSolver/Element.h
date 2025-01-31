#ifndef _ELEMENT_H
#define _ELEMENT_H

#include <vector>
namespace Sudoko
{
    struct Element
    {
        char val;
        std::vector< std::pair<int, int>> loc_fixed;
        std::vector< std::pair<int, int>> loc_empty;
        bool isFilled();
        //return idex at next empty location
        int  getNextEmptyLoc();
        void fillLoc(int itr);
        int getEmptyLoc(std::pair<int, int>);
        Element();
        ~Element();

    private:
        //Iterator for traversing empty location
        size_t itr;
    };
}
#endif
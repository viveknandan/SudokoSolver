#ifndef _POS_H
#define _POS_H

#include <map>
#include <utility>
#include <algorithm>
namespace Sudoko
{
    template <class P>
    class Pos
    {
    private:
        std::map<P, int> _mapRow;
        std::map<P, int> _mapCol;
    public:
        P row;
        P col;
        Pos()
        {

        }
        Pos(std::map<P, int>& mapRow, std::map<P, int>& mapCol, P initVal);
       // Pos(std::map<P, int>& mapRow, std::map<P, int>& mapCol, const P initVal);

        int Row();

        int Col();

        Pos& operator()(P row, P col);

        bool operator==(Pos<P>& lhs);

        bool operator>(Pos<P>& lhs);

        bool operator<(Pos<P>& lhs);

        ~Pos()
        {

        }

    };

    template <class P>
    Pos<P>::Pos(std::map<P, int>& mapRow, std::map<P, int>& mapCol, P initVal)
    {
        row = initVal;
        col = initVal;
        auto itr = mapRow.begin();
        for_each(mapRow.begin(), mapRow.end(), [&](auto it) {
            _mapRow.insert(*itr++);

            });
        itr = mapCol.begin();
        for_each(mapCol.begin(), mapCol.end(), [&](auto it) {
            _mapCol.insert(*itr++);

            });
    }

    template <class P>
    int Pos<P>::Row()
    {
        return _mapRow.at(row);
    }

    template <class P>
    int Pos<P>::Col()
    {
        return _mapCol.at(col);
    }
    template <class P>
    Pos<P>& Pos<P>::operator()(P row, P col)
    {
        this->row = row;
        this->col = col;
        return *this;
    }
    template <class P>
    bool Pos<P>::operator==(Pos<P>& lhs)
    {
        return (_mapRow(this->row) == _mapRow(lhs.row)) && (_mapCol(this->col) == _mapCol(lhs.col));
    }
    template <class P>
    bool Pos<P>::operator>(Pos<P>& lhs)
    {
        return (_mapRow(this->row) > _mapCol(lhs->row)) || (_mapCol(this->col) > _mapRow(lhs.col));
    }
    template <class P>
    bool Pos<P>::operator<(Pos<P>& lhs)
    {
        return (_mapRow(this->row) < _mapRow(lhs->row)) && (_mapCol(this->col) < _mapCol(lhs.col));
    }


}
#endif
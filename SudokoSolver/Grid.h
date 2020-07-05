//#pragma once
#ifndef _GRID_H
#define _GRID_H

#include "Pos.h"
#include <vector>
namespace Sudoko
{
	template <class P, class T>
	class Grid
	{
	public:
		//Constructor to initialize Grid
		//Inputs-
		// m : Number of rows
		// n : Number of column
		// T : Data type of grid contents, should define constructors
		//     to create automatically
		Grid();
		void create(int m, int n, T emptySymbol);
		void initData(std::vector< std::vector<T>>& valMatrix);
		T readPos(Pos<P>& pos);
		void writePos(Pos<P>& pos, T val);
		void clearPos(Pos<P>& pos);
		void movPos(Pos<P>& fromPos, Pos<P>& toPos);
		void copyPos(Pos<P>& fromPos, Pos<P>& toPos);
		void searchElement(T ele, bool whereItExist, std::vector< std::pair<int, int>>& result);

		T operator()(Pos<P>& pos);

		~Grid();

	private:
		char _emptySymbol;
		std::vector< std::vector<T>> _grid;
	};
	template <class P, class T>
	void Grid<P, T>::searchElement(T ele, bool whereItExist, std::vector< std::pair<int, int>>& result)
	{
		int sizeLoc = 0;
		//Iterate the Grid and copy location
		for (int i = 1; i <= _grid.size(); i++)
		{
			for (int j = 1; j <= _grid[i - 1].size(); j++)
			{

				std::pair<int, int> loc;
				loc.first = i;
				loc.second = j;
				if (_grid[i - 1][j - 1] == ele)
				{
					if (whereItExist == true)
					{
						sizeLoc++;
						result.push_back(loc);
					}
				}
				else
				{
					if (whereItExist == false)
					{
						result.push_back(loc);
					}
				}

			}
		}
	}

	template <class P, class T>
	T Grid<P, T>::operator()(Pos<P>& pos)
	{

		T result = _emptySymbol;
		if (pos.row() <= _grid.size() && pos.col() <= _grid.begin()->size())
		{
			result = _grid[pos.row()][pos.col()];
		}
		return result;
	}

	template<class P, class T>
	Grid<P, T>::Grid() :_emptySymbol(static_cast<T>('.'))
	{
	}

	template<class P, class T>
	void Grid<P, T>::create(int m, int n, T emptySymbol)
	{
		for (int i = 1; i <= m; i++)
		{
			std::vector<T> rowVal;
			for (int j = 1; j <= n; j++)
			{
				rowVal.push_back(emptySymbol);
			}
			_grid.push_back(rowVal);
			rowVal.clear();
		}
	}

	template<class P, class T>
	void Grid<P, T>::initData(std::vector< std::vector<T>>& valMatrix)
	{
		//Store number of rows 
		auto lsize = valMatrix.size();
		//check grid is big enough otherwise resize and copy data.
		if (lsize > _grid.size())
		{
			_grid.resize(lsize);
		}

		int gridColSize = 0;
		for (int i = 0; i < lsize; i++)
		{
			gridColSize = valMatrix[i].size();
			_grid[i].resize(gridColSize);
			for (int j = 0; j < gridColSize; j++)
			{
				_grid[i][j] = valMatrix[i][j];
			}
		}
	}

	template<class P, class T>
	T Grid<P, T>::readPos(Pos<P>& pos)
	{
		int nRow = pos.Row();
		int nCol = pos.Col();
		T retVal = _emptySymbol;
		if (_grid.size() >= nRow && _grid.begin()->size() >= nCol)
		{
			retVal = _grid[nRow - 1][nCol - 1];
		}

		return retVal;

	}

	template<class P, class T>
	void Grid<P, T>::writePos(Pos<P>& pos, T val)
	{
		int nRow = pos.Row();
		int nCol = pos.Col();
		if (_grid.size() >= nRow && _grid.begin()->size() >= nCol)
		{
			_grid[nRow - 1][nCol - 1] = val;
		}

	}

	template<class P, class T>
	void Grid<P, T>::clearPos(Pos<P>& pos)
	{
		int nRow = pos.Row();
		int nCol = pos.Col();
		if (_grid.size() >= nRow && _grid.begin()->size() >= nCol)
		{
			_grid[nRow - 1][nCol - 1] = _emptySymbol;
		}
	}

	template<class P, class T>
	void Grid<P, T>::movPos(Pos<P>& fromPos, Pos<P>& toPos)
	{
		int nRow1 = fromPos.Row();
		int nCol1 = fromPos.Col();
		int nRow2 = toPos.Row();
		int nCol2 = toPos.Col();
		if (_grid.size() >= nRow1 && _grid.begin()->size() >= nCol1 && _grid.size() >= nRow2 && _grid.begin()->size() >= nCol2)
		{
			_grid[nRow2 - 1][nCol2 - 1] = _grid[nRow1 - 1][nCol1 - 1];
			_grid[nRow1 - 1][nCol1 - 1] = _emptySymbol;
		}
	}

	template<class P, class T>
	void Grid<P, T>::copyPos(Pos<P>& fromPos, Pos<P>& toPos)
	{
		int nRow1 = fromPos.Row();
		int nCol1 = fromPos.Col();
		int nRow2 = toPos.Row();
		int nCol2 = toPos.Col();
		if (_grid.size() >= nRow1 && _grid.begin()->size() >= nCol1 && _grid.size() >= nRow2 && _grid.begin()->size() >= nCol2)
		{
			_grid[nRow2 - 1][nCol2 - 1] = _grid[nRow1 - 1][nCol1 - 1];
		}
	}

	template<class P, class T>
	Grid<P, T>::~Grid()
	{
	}

}
#endif
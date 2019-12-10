#include "CellIterator.h"

CellIterator::CellIterator(TerrainCell* bC, TerrainCell* eC, int hlRS, int rS) : currentCell(bC), endingCell(eC), beginningCell(bC), highlightedRowSize(hlRS), rowSize(rS)
{ 
	currentRow = highlightedRowSize; 
}

CellIterator::CellIterator(const CellIterator& temp) : currentCell(temp.currentCell), endingCell(temp.endingCell), beginningCell(temp.beginningCell), highlightedRowSize(temp.highlightedRowSize), rowSize(temp.rowSize)
{ 
	currentRow = highlightedRowSize; 
}

CellIterator& CellIterator::operator++ ()
{
	if (highlightedRowSize <= 0)
	{
		highlightedRowSize = currentRow + 1;
		currentCell += (rowSize - currentRow);
		highlightedRowSize--;
		return *this;
	}
	else
	{
		currentCell++;
		highlightedRowSize--;
		return *this;
	}
}

CellIterator CellIterator::operator++(int) 
{ 
	operator++(); 
	return *this; 
}

CellIterator CellIterator::begin() 
{ 
	CellIterator temp(*this); 
	temp.SetCurrentCell(beginningCell);
	return temp; 
}

CellIterator CellIterator::end()
{ 
	CellIterator temp(*this); 
	temp.SetCurrentCell(endingCell); 
	return temp; 
}
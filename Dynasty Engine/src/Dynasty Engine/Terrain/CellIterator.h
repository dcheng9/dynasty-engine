#ifndef _CellIterator
#define _CellIterator

#include <iterator>
#include "TerrainCell.h"

class CellIterator : public std::iterator<std::input_iterator_tag, TerrainCell>
{
private:
	TerrainCell* currentCell;
	TerrainCell* beginningCell;
	TerrainCell* endingCell;

	int currentRow;
	int highlightedRowSize;
	int rowSize;

	void SetCurrentCell(TerrainCell* c) { currentCell = c; }

public:
	CellIterator(){};
	CellIterator(TerrainCell* bC, TerrainCell* eC, int hlRS, int rS );
	CellIterator(const CellIterator& temp);
	virtual ~CellIterator(){};

	TerrainCell& operator*() { return *currentCell; }

	CellIterator& operator++();
	CellIterator operator++(int);

	bool operator==(const CellIterator& temp){ return currentCell == temp.currentCell; }
	bool operator<=(const CellIterator& temp){ return currentCell <= temp.currentCell; }

	CellIterator begin();
	CellIterator end();

	const Vect GetMaxCorner() const { return currentCell->GetMaxCorner(); }
	const Vect GetMinCorner() const { return currentCell->GetMinCorner(); }
	void CollidingOn(const Vect& col){ currentCell->CollidingOn(col); }
};

#endif  _CellIterator
#pragma once
class Rook
{
public:
	Rook();
	long generateLegalMovesForRook(int bitPositionOfRook,char color,long enemyAndEmptySquares,long fullBoard);
	void setRookBoards();

	long rookRightBoard[64]={0}; // set all squares to the right of each square
    long rookLeftBoard[64]={0}; // set all squares to the left of each square
    long rookUpBoard[64]={0}; // set all squares to the up of each square
    long rookDownBoard[64]={0}; // set all squares to the down of each square
};

#pragma once
class Pawn
{
public:
	Pawn();
	void setPawnBoards();
	long generateLegalMovesForPawn(int bitPositionOfPawn,char color,long emptySquares,long whitePieces, long blackPieces, long fullBoard);

private:
	long whitePawnMovesBoard[64]={0};
	long whitePawnTwoMovesBoard[64]={0};
	long whitePawnCaptures[64]={0};

	long blackPawnMovesBoard[64]={0} ;
	long blackPawnTwoMovesBoard[64]={0};
	long blackPawnCaptures[64]={0};
	
};
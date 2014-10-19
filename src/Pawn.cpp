#include "../Headers/Pawn.h"
#include <iostream>
using namespace std;
Pawn::Pawn()
{
	setPawnBoards();
}

void Pawn::setPawnBoards()
{
	for (int i = 8; i < 64; i++)
	{
		whitePawnMovesBoard[i] = 1ULL<<(i+8);
		if (i<56)
			blackPawnMovesBoard[i] = 1ULL<<(i-8);
	}
	for (int i = 8; i < 16; i++)
		whitePawnTwoMovesBoard[i] =1ULL<<(i+16);

	for (int i = 48; i < 56; i++)
		blackPawnTwoMovesBoard[i] =1ULL<<(i-16);

	for (int i = 8; i < 64; i++)
	{
		if (i%8==0 || (i+1)%8==0)
			continue;

		whitePawnCaptures[i] = 1ULL<<(i+7) | 1ULL<<(i+9);
		if(i < 56)
			blackPawnCaptures[i] = 1ULL<<(i-7) | 1ULL<<(i-9);
	}
	
	//display(blackPawnMovesBoard[55]);
	//display(blackPawnMovesBoard[45]);

}

long Pawn::generateLegalMovesForPawn(int bitPositionOfPawn,char color,long emptySquares,long whitePieces, long blackPieces,long fullBoard)
{
	long legalMovesPawn;

	if (color=='w')
	{
		legalMovesPawn=whitePawnMovesBoard[bitPositionOfPawn] & emptySquares;
		if (legalMovesPawn)
			legalMovesPawn|=whitePawnTwoMovesBoard[bitPositionOfPawn] & emptySquares;
		legalMovesPawn|=whitePawnCaptures[bitPositionOfPawn] & blackPieces;
		return legalMovesPawn;
	}
	else if(color=='b')
	{
		legalMovesPawn=blackPawnMovesBoard[bitPositionOfPawn] & emptySquares;
		if (legalMovesPawn)
			legalMovesPawn|=blackPawnTwoMovesBoard[bitPositionOfPawn] & emptySquares;
		legalMovesPawn|=blackPawnCaptures[bitPositionOfPawn] & whitePieces;
		return legalMovesPawn;
	}
}
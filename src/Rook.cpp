#include "../Headers/Rook.h"
#include <iostream>
using namespace std;

Rook::Rook()
{
	setRookBoards();
}

void Rook::setRookBoards()
{
	int j;
	for (int i = 0; i < 64; i++)
	{
		for (j = i+1; (j%8)!=0; j++)
			rookRightBoard[i]|=(1ULL<<j);

		for (j = i-1; (j%8)!=0; j--)
			rookLeftBoard[i]|=(1ULL<<j);
		rookLeftBoard[i]|=(1ULL<<j);

		for (j=i+8;j<=63;j+=8)
			rookUpBoard[i]|=(1ULL<<j);

		for(j=i-8;j>=0;j-=8)
			rookDownBoard[i]|=(1ULL<<j);

   }
}

long Rook::generateLegalMovesForRook(int bitPositionOfRook,char color,long enemyAndEmptySquares,long fullBoard)
{
	long rightMoves;
	long leftMoves;
	long upMoves;
	long downMoves;
	long rookMoves;

	rightMoves=rookRightBoard[bitPositionOfRook] & fullBoard;
	rightMoves=(rightMoves<<1) | (rightMoves<<2) | (rightMoves<<3) | (rightMoves<<4) | (rightMoves<<5) | (rightMoves<<6);
	rightMoves&=rookRightBoard[bitPositionOfRook];
	rightMoves^=rookRightBoard[bitPositionOfRook];
	rightMoves&=enemyAndEmptySquares;

	leftMoves=rookLeftBoard[bitPositionOfRook] & fullBoard;
	leftMoves=(leftMoves>>1) |(leftMoves>>2) | (leftMoves>>3) | (leftMoves>>4) | (leftMoves>>5) | (leftMoves>>6);
	leftMoves&=rookLeftBoard[bitPositionOfRook];
	leftMoves^=rookLeftBoard[bitPositionOfRook];
	leftMoves&=enemyAndEmptySquares;

	upMoves=rookUpBoard[bitPositionOfRook] & fullBoard;
	upMoves=(upMoves<<8) | (upMoves<<16) | (upMoves<<24) | (upMoves<<32) | (upMoves<<40) | (upMoves<<48);
	upMoves&=rookUpBoard[bitPositionOfRook];
	upMoves^=rookUpBoard[bitPositionOfRook]; 
	upMoves&=enemyAndEmptySquares;

	downMoves=rookDownBoard[bitPositionOfRook] & fullBoard;
	downMoves=(downMoves>>8) | (downMoves>>16) | (downMoves>>24) | (downMoves>>32) | (downMoves>>40) | (downMoves>>48);
	downMoves&=rookDownBoard[bitPositionOfRook];
	downMoves^=rookDownBoard[bitPositionOfRook];
	downMoves&=enemyAndEmptySquares;

	rookMoves=rightMoves | leftMoves | upMoves | downMoves;
	return rookMoves;
}
#include "Headers/Rook.h"
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
    
    if (color=='w')
        rightMoves&=enemyAndEmptySquares;
    else if(color='b')
        rightMoves&=enemyAndEmptySquares;
    return rightMoves;
    //displayBoard(rightMoves);
}
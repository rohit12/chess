#include "../Headers/King.h"
#include <iostream>
using namespace std;
King::King()
{
	hasWhiteKingMoved=false;
	hasBlackKingMoved=false;

	isWhiteLongCastlingPossible=false;
	isWhiteShortCastlingPossible=false;

	isBlackLongCastlingPossible=false;
	isBlackShortCastlingPossible=false;

	setKingBoard();
}

void King::setKingBoard()
{
	for (int i = 0; i < 64; i++)
	{
		if ( !((i%8)==0 || (i>=0 && i<=7) || (i>=56 && i<=63) || ((i+1)%8==0)) )
			kingMovesBoard[i] = (1ULL<<(i+7)) | (1ULL<<(i+8)) | (1ULL<<(i+9)) | (1ULL<<(i+1)) | (1ULL<<(i-7)) | (1ULL<<(i-8)) | (1ULL<<(i-9)) | (1ULL<<(i-1)) ;

		if(i%8==0 && (i!=56) && (i!=0))
			kingMovesBoard[i] = (1ULL<<(i+8)) | (1ULL<<(i+1)) | (1ULL<<(i+9)) | (1ULL<<(i-7)) | (1ULL<<(i-8));

		if((i+1)%8==0 && (i!=7) && (i!=63))
			kingMovesBoard[i] = (1ULL<<(i+8)) | (1ULL<<(i+7)) | (1ULL<<(i-8)) | (1ULL<<(i-9)) | (1ULL<<(i-1));

		if (i>=57 && i<=62)
			kingMovesBoard[i] = (1ULL<<(i+1)) | (1ULL<<(i-1)) | (1ULL<<(i-7)) | (1ULL<<(i-8)) | (1ULL<<(i-9));

		if (i>=1 && i<=6)
			kingMovesBoard[i] = (1ULL<<(i+1)) | (1ULL<<(i-1)) | (1ULL<<(i+7)) | (1ULL<<(i+8)) | (1ULL<<(i+9));
		
		if(i==56)
			kingMovesBoard[i] = (1ULL<<57) | (1ULL<<48) | (1ULL<<49);

		if(i==63)
			kingMovesBoard[i] = (1ULL<<(i-1)) | (1ULL<<(i-8)) | (1ULL<<(i-9));

		if (i==0)
			kingMovesBoard[i] = (1ULL<<(i+1)) | (1ULL<<(i+8)) | (1ULL<<(i+9));

		if(i==7)
			kingMovesBoard[i] = (1ULL<<(i-1)) | (1ULL<<(i+8)) | (1ULL<<(i+7));
	}

}

long King::generateLegalMovesForKing(int bitPositionOfKing,char color,long enemyAndEmptySquares,long fullBoard)
{
	long kingMoves;

	kingMoves=kingMovesBoard[bitPositionOfKing]&enemyAndEmptySquares;

	return kingMoves;
}

void King::display(long xyz)
{
	for(int i=0;i<64;i++)
	{
	   if(i%8==0)
		{
			cout<<endl;
		}
		if(xyz & (1ULL<<i))
		{
			cout<<"1";
		}
		else
		{
			cout<<"0";
		}
		
	} 
	cout<<endl;
}

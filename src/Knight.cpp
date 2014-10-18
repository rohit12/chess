#include "../Headers/Knight.h"
#include <iostream>

Knight::Knight()
{
	setKnightBoard();
}

void Knight::setKnightBoard()
{

	knightMovesBoard[0] = (1ULL<<10) | (1ULL<<17); 
	knightMovesBoard[6] = 1ULL<<12 | 1ULL<<21 | 1ULL<<23;
	knightMovesBoard[7] = (1ULL<<13) | (1ULL<<22);
	knightMovesBoard[1] = 1ULL<<11 | 1ULL<<18 | 1ULL<<16;
	knightMovesBoard[8] = 1ULL<<2 | 1ULL<<18 | 1ULL<<25;
	knightMovesBoard[9] = 1ULL<<3 | 1ULL<<19 | 1ULL<<24 | 1ULL<<26;
	knightMovesBoard[56] = (1ULL<<50) | (1ULL<<41);
	knightMovesBoard[63] = (1ULL<<53) | (1ULL<<46);
	
	knightMovesBoard[48] = (1ULL<<58) | (1ULL<<42) | (1ULL<<33);
	knightMovesBoard[49] = (1ULL<<59) | (1ULL<<43) | (1ULL<<34) | (1ULL<<34);
	knightMovesBoard[57] = 1ULL<<51 | 1ULL<<42 | 1ULL<<40;

	knightMovesBoard[62] = 1ULL<<52 | 1ULL<<45 | 1ULL<<47;
	knightMovesBoard[54] = 1ULL<<60 | 1ULL<<44 | 1ULL<<37 | 1ULL<<39;
	knightMovesBoard[55] = 1ULL<<61 | 1ULL<<45 | 1ULL<<39;

	knightMovesBoard[14] = 1ULL<<4 | 1ULL<<20 | 1ULL<<29 | 1ULL<<31;
	knightMovesBoard[15] = 1ULL<<5 | 1ULL<<21 | 1ULL<<30;

	for (int i = 16; i < 48; i+=8)
		knightMovesBoard[i] = (1ULL<<(i+17)) | (1ULL<<(i+10)) | (1ULL<<(i-6)) | (1ULL<<(i-15));

	for (int i = 17; i < 49; i+=8)
		knightMovesBoard[i] = (1ULL<<(i+17)) | (1ULL<<(i+10)) | (1ULL<<(i-6)) | (1ULL<<(i-15)) | (1ULL<<(i+15)) | (1ULL<<(i-17));

	for (int i = 0; i < 64; i++)
	{
		if ((i>=18 && i<=21) || (i>=26 && i<=29) || (i>=34 && i<=37) || (i>=42 && i<=45))
			knightMovesBoard[i] = (1ULL<<(i+17)) | (1ULL<<(i+10)) | (1ULL<<(i-6)) | (1ULL<<(i-15)) | (1ULL<<(i+15)) | (1ULL<<(i-17)) | (1ULL<<(i-10)) | (1ULL<<(i+6));

		else if ((i>=50 && i<=53))
			knightMovesBoard[i] = (1ULL<<(i+10)) | (1ULL<<(i+6)) | (1ULL<<(i-10)) | (1ULL<<(i-6)) | (1ULL<<(i-17)) | (1ULL<<(i-15));

		else if ((i>=10 && i<=13))
			knightMovesBoard[i] = (1ULL<<(i-10)) | (1ULL<<(i-6)) | (1ULL<<(i+6)) | (1ULL<<(i+10)) | (1ULL<<(i+15)) | (1ULL<<(i+17));

		else if (i>=58 && i<=61)
			knightMovesBoard[i] = (1ULL<<(i-10)) | (1ULL<<(i-6)) | (1ULL<<(i-15));

		else if (i>=2 && i<=5)
			knightMovesBoard[i] = (1ULL<<(i+6)) | (1ULL<<(i+10)) | (1ULL<<(i+17)) | (1ULL<<(i+15));
	}

	for (int i = 22; i <= 46; i+=8)
		knightMovesBoard[i] = (1ULL<<(i+15)) | (1ULL<<(i+17)) | (1ULL<<(i-15)) | (1ULL<<(i-17)) | (1ULL<<(i+6)) | (1ULL<<(i-10));

	for (int i = 23; i <= 47; i+=8)
		knightMovesBoard[i] = (1ULL<<(i+15)) | (1ULL<<(i+6)) | (1ULL<<(i-10)) | (1ULL<<(i-17));
}

long Knight::generateLegalMovesForKnight(int bitPositionOfKnight,char color,long enemyAndEmptySquares,long fullBoard)
{
	long knightMoves;

	knightMoves=knightMovesBoard[bitPositionOfKnight] & enemyAndEmptySquares;

	return knightMoves;
}
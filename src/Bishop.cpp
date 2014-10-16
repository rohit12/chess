#include "../Headers/Bishop.h"
#include <bitset>
#include <iostream>
using namespace std;
Bishop::Bishop()
{
	setBishopBoards();
}

void Bishop::setBishopBoards()
{
	int j;
	for (int i = 0; i < 64; i++)
	{
		for (j = i+9; (j+1)%8!=0; j+=9)
		{
			if ((j-8)%8==0)
				break;
			fortyFiveDegreeBoard[i]|=(1ULL<<j);
		}
		if((j-8)%8!=0)
			fortyFiveDegreeBoard[i]|=(1ULL<<j);

		for (j = i-9; (j)%8!=0; j-=9)
		{
			if(j<0)
				break;
			twoTwentyFiveDegreeBoard[i]|=(1ULL<<j);	
		}
		if(!(j<0))
			twoTwentyFiveDegreeBoard[i]|=(1ULL<<j);

		for (j = i+7; j%8!=0;j+=7)
		{
			if(j==7 || j==15 || j==23 || j==31 || j==39 || j==47 || j==55 || (j>=56 && j<=63))
				break;
			oneThirtyFiveDegreeBoard[i]|=(1ULL<<j);
		}
		oneThirtyFiveDegreeBoard[i]|=(1ULL<<j);

		for(j = i-7;(j+1)%8!=0 ; j-=7)
		{
			if (j<0)
				break;
			threeHundredFifteenDegreeBoard[i]|=(1ULL<<j);
		}
		if(!(j<0))
			threeHundredFifteenDegreeBoard[i]|=(1ULL<<j);
	}
}

long Bishop::generateLegalMovesForBishop(int bitPositionOfBishop,char color,long enemyAndEmptySquares,long fullBoard)
{
	long fortyFiveDegreeMoves;
	long twoTwentyFiveDegreeMoves;
	long oneThirtyFiveDegreeMoves;
	long threeHundredFifteenDegreeMoves;
	long bishopMoves;

	fortyFiveDegreeMoves=fortyFiveDegreeBoard[bitPositionOfBishop] & fullBoard;
	fortyFiveDegreeMoves=(fortyFiveDegreeMoves<<9) | (fortyFiveDegreeMoves<<18) | (fortyFiveDegreeMoves<<27) | (fortyFiveDegreeMoves<<36)| (fortyFiveDegreeMoves<<45) | (fortyFiveDegreeMoves<<54);
	fortyFiveDegreeMoves&=fortyFiveDegreeBoard[bitPositionOfBishop];
	fortyFiveDegreeMoves^=fortyFiveDegreeBoard[bitPositionOfBishop];
	fortyFiveDegreeMoves&=enemyAndEmptySquares;

	twoTwentyFiveDegreeMoves=twoTwentyFiveDegreeBoard[bitPositionOfBishop] & fullBoard;
	twoTwentyFiveDegreeMoves=(twoTwentyFiveDegreeMoves>>9) | (twoTwentyFiveDegreeMoves>>8) | (twoTwentyFiveDegreeMoves>>27) | (twoTwentyFiveDegreeMoves>>36)| (twoTwentyFiveDegreeMoves>>45) | (twoTwentyFiveDegreeMoves>>54);
	twoTwentyFiveDegreeMoves&=twoTwentyFiveDegreeBoard[bitPositionOfBishop];
	twoTwentyFiveDegreeMoves^=twoTwentyFiveDegreeBoard[bitPositionOfBishop];
	twoTwentyFiveDegreeMoves&=enemyAndEmptySquares;

	oneThirtyFiveDegreeMoves=oneThirtyFiveDegreeBoard[bitPositionOfBishop] & fullBoard;
	oneThirtyFiveDegreeMoves=(oneThirtyFiveDegreeMoves<<7) | (oneThirtyFiveDegreeMoves<<14) | (oneThirtyFiveDegreeMoves<<21) | (oneThirtyFiveDegreeMoves<<28)| (oneThirtyFiveDegreeMoves<<35) | (oneThirtyFiveDegreeMoves<<42);
	oneThirtyFiveDegreeMoves&=oneThirtyFiveDegreeBoard[bitPositionOfBishop];
	oneThirtyFiveDegreeMoves^=oneThirtyFiveDegreeBoard[bitPositionOfBishop];
	oneThirtyFiveDegreeMoves&=enemyAndEmptySquares;

	threeHundredFifteenDegreeMoves=threeHundredFifteenDegreeBoard[bitPositionOfBishop] & fullBoard;
	threeHundredFifteenDegreeMoves=(threeHundredFifteenDegreeMoves>>7) | (threeHundredFifteenDegreeMoves>>14) | (threeHundredFifteenDegreeMoves>>21) | (threeHundredFifteenDegreeMoves>>28)| (threeHundredFifteenDegreeMoves>>35) | (threeHundredFifteenDegreeMoves>>42);
	threeHundredFifteenDegreeMoves&=threeHundredFifteenDegreeBoard[bitPositionOfBishop];
	threeHundredFifteenDegreeMoves^=threeHundredFifteenDegreeBoard[bitPositionOfBishop];
	threeHundredFifteenDegreeMoves&=enemyAndEmptySquares;

	bishopMoves=fortyFiveDegreeMoves | twoTwentyFiveDegreeMoves | oneThirtyFiveDegreeMoves | threeHundredFifteenDegreeMoves;
	return bishopMoves;
}

void Bishop::display(long xyz)
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
}

/*int main()
{
	Bishop bishop=Bishop();
	return 0;
}*/
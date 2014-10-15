#pragma once
class Bishop
{
public:
	Bishop();
	long generateLegalMovesForBishop(int bitPositionOfBishop,char color,long enemyAndEmptySquares,long fullBoard);
	void setBishopBoards();
	void display(long xyz);

	long fortyFiveDegreeBoard[64]={0};
	long twoTwentyFiveDegreeBoard[64]={0};
	long oneThirtyFiveDegreeBoard[64]={0};
	long threeHundredFifteenDegreeBoard[64]={0};
};
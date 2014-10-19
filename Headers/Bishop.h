#pragma once
class Bishop
{
public:
	Bishop();
	long generateLegalMovesForBishop(int bitPositionOfBishop,char color,long enemyAndEmptySquares,long fullBoard);
	void setBishopBoards();
	void display(long xyz);

	long fortyFiveDegreeBoard[64];
	long twoTwentyFiveDegreeBoard[64];
	long oneThirtyFiveDegreeBoard[64];
	long threeHundredFifteenDegreeBoard[64];
};
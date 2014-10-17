#pragma once
class King
{
public:
	King();
	int isCastlingPossible(char color,int length);
	bool getkingMovedStatus(char color);
	void setKingMovedStatus(char color,bool movement);
	long generateLegalMovesForKing(int bitPositionOfKing,char color,long enemyAndEmptySquares,long fullBoard);
	void setKingBoard();
	void display(long xyz);
	
private:
	bool hasWhiteKingMoved;
	bool hasBlackKingMoved;

	bool isWhiteLongCastlingPossible;
	bool isWhiteShortCastlingPossible;

	bool isBlackLongCastlingPossible;
	bool isBlackShortCastlingPossible;

	long kingMovesBoard[64]={0};
};
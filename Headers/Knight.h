class Knight
{
public:
	Knight();
	void setKnightBoard();
	long generateLegalMovesForKnight(int bitPositionOfKnight,char color,long enemyAndEmptySquares,long fullBoard);
	
private:
	long knightMovesBoard[64]={0};
};
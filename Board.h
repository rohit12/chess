class Board
{
private:
	long whitePawn;
	long whiteKnight;
	long whiteBishop;
	long whiteRook;
	long whiteQueen;
	long whiteKing;

	long blackPawn;
	long blackKnight;
	long blackBishop;
	long blackRook;
	long blackQueen;
	long blackKing;	

	long whitePieces;
	long blackPieces;

	long fullBoard;
    long emptySquares;
    long whiteEnemyAndEmptySquares;
    long blackEnemyAndEmptySquares;

    long rookRightBoard[64]={0}; // set all squares to the right of each square
    long rookLeftBoard[64]={0}; // set all squares to the left of each square
    long rookUpBoard[64]={0}; // set all squares to the up of each square
    long rookDownBoard[64]={0}; // set all squares to the down of each square

	char pieceRepresentation[8][8];
	char sourceSquare[2];
	char destinationSquare[2];
	char pieceToMove;
    int turn;

public:
	Board();
    void clearPieceRepresentation();
	void fillPieceArray();
	void displayBoard(long xyz);
	void recomputeBitboards();
	void makeMove();
    void movePiece(char sourceSquare[],char destinationSquare[],char pieceToMove, int turn);
    int getSquare(char sourceSquare[]);
    void setRookBoards();
    void generateLegalMovesForRook(int bitPositionOfRook,char color);
};

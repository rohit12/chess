#pragma once
#include "../Headers/Rook.h"
#include "../Headers/Bishop.h"

class Board
{
public:
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

    int validMove;
    
    Rook rook;
	Bishop bishop;
	
	char pieceRepresentation[8][8];
	char sourceSquare[2];
	char destinationSquare[2];
	char pieceToMove;
    int turn;

	Board();
    void clearPieceRepresentation();
	void fillPieceArray();
	void displayBoard(long xyz);
	void recomputeBitboards();
	void makeMove();
    void movePiece(char sourceSquare[],char destinationSquare[],char pieceToMove, int turn);
    int getSquare(char sourceSquare[]);
};

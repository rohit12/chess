#pragma once
#include "../Headers/Rook.h"
#include "../Headers/Bishop.h"
#include "../Headers/King.h"
#include "../Headers/Knight.h"
#include "../Headers/Pawn.h"

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
	King king;
	Knight knight;
	Pawn pawn;
	
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
	char getPieceOnSquare(int square);
	void deletePieceFromSquare(char piece,char color, int destination);
	void movePawn(int source, int destination, int turn);
	void moveRook(int source, int destination, int turn);
	void moveBishop(int source, int destination, int turn);
	void moveKnight(int source, int destination, int turn);
	void moveQueen(int source, int destination, int turn);
	void moveKing(int source, int destination, int turn);
	int getSquare(char sourceSquare[]);
};

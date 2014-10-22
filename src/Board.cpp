#include "../Headers/Board.h"
#include "../Headers/Rook.h"
#include "../Headers/Bishop.h"
#include "../Headers/King.h"
#include "../Headers/Knight.h"
#include "../Headers/Pawn.h"
#include <iostream>
#include <bitset>
#include <vector>
using namespace std;

Board::Board()
{
	rook=Rook();
	bishop=Bishop();
	king=King();
	knight=Knight();
	pawn=Pawn();
	turn=0;

	whitePieces=0x000000000000FFFF;
	blackPieces=0xFFFF000000000000;

	whitePawn=0x000000000000FF00;
	blackPawn=0x00FF000000000000;

	whiteKnight=0x0000000000000042;
	blackKnight=0x4200000000000000;

	whiteBishop=0x0000000000000024;
	blackBishop=0x2400000000000000;

	whiteRook=0x0000000000000081;
	blackRook=0x8100000000000000;

	whiteQueen=0x0000000000000008;
	blackQueen=0x0800000000000000;

	whiteKing=0x0000000000000010;
	blackKing=0x1000000000000000;

	fullBoard=whitePieces|blackPieces;
	emptySquares=fullBoard ^ 0xFFFFFFFFFFFFFFFF;
	whiteEnemyAndEmptySquares=blackPieces | emptySquares;
	blackEnemyAndEmptySquares=whitePieces | emptySquares;

	clearPieceRepresentation();	
	storeBitboardsInArray();
	validMove=1;
}

void Board::storeBitboardsInArray()
{
	bitboards[0]=whitePawn;
	bitboards[1]=blackPawn;
	bitboards[2]=whiteKnight;
	bitboards[3]=blackKnight;
	bitboards[4]=whiteBishop;
	bitboards[5]=blackBishop;
	bitboards[6]=whiteRook;
	bitboards[7]=blackRook;
	bitboards[8]=whiteQueen;
	bitboards[9]=blackQueen;
	bitboards[10]=whiteKing;
	bitboards[11]=blackKing;

	bitboards[12]=fullBoard;
	bitboards[13]=emptySquares;
	bitboards[14]=whiteEnemyAndEmptySquares;
	bitboards[15]=blackEnemyAndEmptySquares;
}


void Board::clearPieceRepresentation() //clearing the 8*8 char array
{
	for (int i = 0; i < 64; i++)
	{
		pieceRepresentation[i/8][i%8]=' ';
	}
}

void Board::fillPieceArray() //fills the char array with the appropriate pieces
{
	long temp;
	clearPieceRepresentation();
	temp=(fullBoard&whitePawn)|(fullBoard&blackPawn);
	for (int i = 0; i < 64; i++)
		if(temp & (1ULL<<i))
			pieceRepresentation[i/8][i%8]='P';
		
	temp=(fullBoard&whiteKnight)|(fullBoard&blackKnight);
	for (int i = 0; i < 64; i++)
		if(temp & (1ULL<<i))
			pieceRepresentation[i/8][i%8]='N';

	temp=(fullBoard&whiteQueen)|(fullBoard&blackQueen);
	for (int i = 0; i < 64; i++)
		if(temp & (1ULL<<i))
			pieceRepresentation[i/8][i%8]='Q';

	temp=(fullBoard&whiteKing)|(fullBoard&blackKing);
	for (int i = 0; i < 64; i++)
		if(temp & (1ULL<<i))
			pieceRepresentation[i/8][i%8]='K';
		
	temp=(fullBoard&whiteRook)|(fullBoard&blackRook);
	for (int i = 0; i < 64; i++)
		if(temp & (1ULL<<i))
			pieceRepresentation[i/8][i%8]='R';

	temp=(fullBoard&whiteBishop)|(fullBoard&blackBishop);
	for (int i = 0; i < 64; i++)
		if(temp & (1ULL<<i))
			pieceRepresentation[i/8][i%8]='B';

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			cout<<pieceRepresentation[i][j];
		cout<<endl;
	}
}

void Board::displayBoard(long xyz) //displays binary representation of xyz variable in chessboard format
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

void Board::recomputeBitboards() //recomputes bitboards according to the changes that have taken place in them
{
	whitePieces=whitePawn|whiteBishop|whiteRook|whiteKing|whiteQueen|whiteKnight;
	blackPieces=blackPawn|blackBishop|blackRook|blackKing|blackQueen|blackKnight;
	fullBoard=whitePieces|blackPieces;
	emptySquares=fullBoard ^ 0xFFFFFFFFFFFFFFFF;
	whiteEnemyAndEmptySquares=blackPieces | emptySquares;
	blackEnemyAndEmptySquares=whitePieces | emptySquares;

}

void Board::makeMove() //makes a move
{
	if(validMove)
	{
		turn++;
	}
	else
	{
		validMove=1;
	}
	cout<<"Enter starting square: "<<endl;
	cin>>sourceSquare;
	if(turn%2==1) //if it is white's turn, check whether a white piece exists on that square
	{
		if(!(whitePieces&(1ULL<<getSquare(sourceSquare))))
		{
			cout<<"No white piece exists on that square"<<endl;
			turn--;
			return;
		}
	}
	else //if it is black's turn, check whether a black piece exists on that square
	{
		if(!(blackPieces&(1ULL<<getSquare(sourceSquare))))
		{
			cout<<"No black piece exists on that square"<<endl;
			turn--;
			return;
		}
	}
	cout<<"Enter destinationSquare: "<<endl;
	cin>>destinationSquare;

	pieceToMove=getPieceOnSquare(getSquare(sourceSquare));
	movePiece(sourceSquare,destinationSquare,pieceToMove,turn);
}

char Board::getPieceOnSquare(int square)
{
	if (((1ULL<<square)&whitePawn) || ((1ULL<<square)&blackPawn))
		return 'P';

	if (((1ULL<<square)&whiteRook) || ((1ULL<<square)&blackRook))
		return 'R';

	if (((1ULL<<square)&whiteBishop) || ((1ULL<<square)&blackBishop))
		return 'B';

	if (((1ULL<<square)&whiteKnight) || ((1ULL<<square)&blackKnight))
		return 'N';

	if (((1ULL<<square)&whiteQueen) || ((1ULL<<square)&blackQueen))
		return 'Q';

	if (((1ULL<<square)&whiteKing) || ((1ULL<<square)&blackKing))
		return 'K';
	return 'X';
}

void Board::deletePieceFromSquare(char piece, char color, int destination)
{
	switch(color)
	{
		case 'w':
			if (piece=='P')
				whitePawn&=~(1ULL<<destination);

			else if (piece=='N')
				whiteKnight&=~(1ULL<<destination);

			else if(piece=='K')
				whiteKing&=~(1ULL<<destination);

			else if(piece=='Q')
				whiteQueen&=~(1ULL<<destination);

			else if(piece=='B')
				whiteQueen&=~(1ULL<<destination);

			else if(piece=='R')
				whiteRook&=~(1ULL<<destination);
		break;

		case 'b':
			if(piece=='P')
				blackPawn&=~(1ULL<<destination);

			else if(piece=='N')
				blackKnight&=~(1ULL<<destination);

			else if(piece=='K')
				blackKing&=~(1ULL<<destination);

			else if(piece=='Q')
				blackQueen&=~(1ULL<<destination);

			else if(piece=='B')
				blackQueen&=~(1ULL<<destination);

			else if(piece=='R')
				blackRook&=~(1ULL<<destination);
		break;
	}
}

void Board::movePiece(char sourceSquare[],char destinationSquare[],char pieceToMove, int turn) //actually moves a piece
{
	int source,destination;
	source=getSquare(sourceSquare);
	destination=getSquare(destinationSquare);
	
	if(pieceToMove=='p' || pieceToMove=='P')
		movePawn(source,destination,turn);

	else if(pieceToMove=='r' || pieceToMove=='R')
		moveRook(source,destination,turn);

	else if(pieceToMove=='B' || pieceToMove=='b')
		moveBishop(source,destination,turn);

	else if(pieceToMove=='N' || pieceToMove=='n')
		moveKnight(source,destination,turn);

	else if(pieceToMove=='Q' || pieceToMove=='q')
		moveQueen(source,destination,turn);
	
	else if(pieceToMove=='K' || pieceToMove=='k')
		moveKing(source,destination,turn);
		
	recomputeBitboards();
	storeBitboardsInArray();
	fillPieceArray();
}

void Board::moveKing(int source, int destination, int turn)
{
	long legalMovesKing;
	char piece='X';
	if (turn%2==1)
	{
		legalMovesKing=king.generateLegalMovesForKing(source,'w',whiteEnemyAndEmptySquares,fullBoard);
		if ((1ULL<<destination)&legalMovesKing)
		{
			piece=getPieceOnSquare(destination);

			if(piece!='X')
				deletePieceFromSquare(piece,'b',destination);

			whiteKing&=~(1ULL<<source);
			whiteKing|=(1ULL<<destination);
		}
		else
			validMove=0;
	}
	else
	{
		legalMovesKing=king.generateLegalMovesForKing(source,'b',blackEnemyAndEmptySquares,fullBoard);
		if ((1ULL<<destination)&legalMovesKing)
		{
			piece=getPieceOnSquare(destination);

			if(piece!='X')
				deletePieceFromSquare(piece,'w',destination);
			blackKing&=~(1ULL<<source);
			blackKing|=(1ULL<<destination);
		}
		else
			validMove=0;
	}
}

void Board::movePawn(int source,int destination,int turn)
{
	long legalMovesPawn;
	char piece='X';
	if(turn%2==1)
	{
		legalMovesPawn=pawn.generateLegalMovesForPawn(source,'w',emptySquares,whitePieces,blackPieces,fullBoard);
		if (legalMovesPawn & (1ULL<<destination))
		{
			piece=getPieceOnSquare(destination);

			if(piece!='X')
				deletePieceFromSquare(piece,'b',destination);
			whitePawn&=~(1ULL<<source);
			whitePawn|=(1ULL<<destination);
		}
		else
			validMove=0;
	}
	else if(turn%2==0)
	{
		legalMovesPawn=pawn.generateLegalMovesForPawn(source,'b',emptySquares,whitePieces,blackPieces,fullBoard);
		if (legalMovesPawn & (1ULL<<destination))
		{
			piece=getPieceOnSquare(destination);

			if(piece!='X')
				deletePieceFromSquare(piece,'w',destination);

			blackPawn&=~(1ULL<<source);
			blackPawn|=(1ULL<<destination);
		}
		else
			validMove=0;
	}
}

void Board::moveBishop(int source, int destination, int turn)
{
	long legalMovesBishop;
	char piece='X';
	if(turn%2==1)
	{
		legalMovesBishop=bishop.generateLegalMovesForBishop(source,'w',whiteEnemyAndEmptySquares,fullBoard);
		if((1ULL<<destination)&legalMovesBishop)
		{
			piece=getPieceOnSquare(destination);

			if(piece!='X')
				deletePieceFromSquare(piece,'b',destination);

			whiteBishop&=~(1ULL<<source);
			whiteBishop|=(1ULL<<destination);
		}
		else
			validMove=0;
	}
	else
	{
		legalMovesBishop=bishop.generateLegalMovesForBishop(source,'b',blackEnemyAndEmptySquares,fullBoard);
		if ((1ULL<<destination)&legalMovesBishop)
		{
			piece=getPieceOnSquare(destination);

			if(piece!='X')
				deletePieceFromSquare(piece,'w',destination);

			blackBishop&=~(1ULL<<source);
			blackBishop|=(1ULL<<destination);
		}
		else
			validMove=0;
	}
}

void Board::moveKnight(int source, int destination, int turn)
{
	long legalMovesKnight;
	char piece='X';
	if (turn%2==1)
	{
		legalMovesKnight=knight.generateLegalMovesForKnight(source,'w',whiteEnemyAndEmptySquares,fullBoard);
		if ((1ULL<<destination) & legalMovesKnight)
		{
			piece=getPieceOnSquare(destination);

			if(piece!='X')
				deletePieceFromSquare(piece,'b',destination);

			whiteKnight&=~(1ULL<<source);
			whiteKnight|=(1ULL<<destination);
		}
		else
			validMove=0;
	}
	else
	{
		legalMovesKnight=knight.generateLegalMovesForKnight(source,'b',blackEnemyAndEmptySquares,fullBoard);
		if ((1ULL<<destination) & legalMovesKnight)
		{
			piece=getPieceOnSquare(destination);

			if(piece!='X')
				deletePieceFromSquare(piece,'w',destination);

			blackKnight&=~(1ULL<<source);
			blackKnight|=(1ULL<<destination);
		}
		else
			validMove=0;
	}
}

void Board::moveRook(int source, int destination, int turn)
{
	long legalMovesRook;
	char piece='X';
	if (turn%2==1)
	{
		legalMovesRook=rook.generateLegalMovesForRook(source,'w',whiteEnemyAndEmptySquares,fullBoard);
		if((1ULL<<destination)&legalMovesRook)
		{
			piece=getPieceOnSquare(destination);

			if(piece!='X')
				deletePieceFromSquare(piece,'b',destination);

			whiteRook&=~(1ULL<<source);
			whiteRook|=(1ULL<<destination);
		}
		else
			validMove=0;

	}
	else
	{
		legalMovesRook=rook.generateLegalMovesForRook(source,'b',blackEnemyAndEmptySquares,fullBoard);
		if ((1ULL<<destination)&legalMovesRook)
		{
			piece=getPieceOnSquare(destination);

			if(piece!='X')
				deletePieceFromSquare(piece,'w',destination);

			blackRook&=~(1ULL<<source);
			blackRook|=(1ULL<<destination);	
		}
		else
			validMove=0;
	}
}

void Board::moveQueen(int source,int destination,int turn)
{
	char piece='X';
	if (turn%2==1)
	{
		long legalMovesQueen=rook.generateLegalMovesForRook(source,'w',whiteEnemyAndEmptySquares,fullBoard) | bishop.generateLegalMovesForBishop(source,'w',whiteEnemyAndEmptySquares,fullBoard);
		if ((1ULL<<destination)&legalMovesQueen)
		{	
			piece=getPieceOnSquare(destination);

			if(piece!='X')
				deletePieceFromSquare(piece,'b',destination);

			whiteQueen&=~(1ULL<<source);
			whiteQueen|=(1ULL<<destination);
		}
		else
			validMove=0;
	}
	else
	{
		long legalMovesQueen=rook.generateLegalMovesForRook(source,'b',blackEnemyAndEmptySquares,fullBoard) | bishop.generateLegalMovesForBishop(source,'b',blackEnemyAndEmptySquares,fullBoard);
		if ((1ULL<<destination)&legalMovesQueen)
		{
			piece=getPieceOnSquare(destination);

			if(piece!='X')
				deletePieceFromSquare(piece,'w',destination);

			blackQueen&=~(1ULL<<source);
			blackQueen|=(1ULL<<destination);
		}
		else
			validMove=0;
	}
}

int Board::getSquare(char sourceSquare[]) //converts a square to a bit number. Eg: D2=11
{

	int letter=sourceSquare[0]-'A';
	int digit=sourceSquare[1]-48;
	return letter+(digit-1)*8;
}
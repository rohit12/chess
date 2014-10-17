#include "../Headers/Board.h"
#include "../Headers/Rook.h"
#include "../Headers/Bishop.h"
#include <iostream>
#include <bitset>
using namespace std;

Board::Board()
{
	rook=Rook();
	bishop=Bishop();
	turn=0;
	hasKingMoved=0;

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
	validMove=1;
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
	/*bitset<64>x(fullBoard);
	cout<<x<<fullBoard<<endl;*/
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
			cout<<"It is White's turn. Do not move black pieces."<<endl;
			turn--;
			return;
		}
	}
	else //if it is black's turn, check whether a black piece exists on that square
	{
		if(!(blackPieces&(1ULL<<getSquare(sourceSquare))))
		{
			cout<<"It is Black's turn. Do not move white pieces."<<endl;
			turn--;
			return;
		}
	}
	cout<<"Enter destinationSquare: "<<endl;
	cin>>destinationSquare;

	cout<<"Enter piece to move: P R B N Q K"<<endl;
	cin>>pieceToMove;
	movePiece(sourceSquare,destinationSquare,pieceToMove,turn);
}

void Board::movePiece(char sourceSquare[],char destinationSquare[],char pieceToMove, int turn) //actually moves a piece
{
	int source,destination;
	source=getSquare(sourceSquare);
	destination=getSquare(destinationSquare);
	if(pieceToMove=='p' || pieceToMove=='P')
	{
		if(turn%2==1)
		{
			whitePawn&=~(1ULL<<source);
			whitePawn|=(1ULL<<destination);
		}
		else if(turn%2==0)
		{
			blackPawn&=~(1ULL<<source);
			blackPawn|=(1ULL<<destination);
		}
		
	}
	else if(pieceToMove=='r' || pieceToMove=='R')
	{
		long legalMovesRook;
		if (turn%2==1)
		{
			legalMovesRook=rook.generateLegalMovesForRook(source,'w',whiteEnemyAndEmptySquares,fullBoard);
			if((1ULL<<destination)&legalMovesRook)
			{
				whiteRook&=~(1ULL<<source);
				whiteRook|=(1ULL<<destination);
			}
			else
			{
				//cout<<"The move is not legal"<<endl;
				fillPieceArray();
				validMove=0;
				return;
			}

		}
		else
		{
			legalMovesRook=rook.generateLegalMovesForRook(source,'b',blackEnemyAndEmptySquares,fullBoard);
			if ((1ULL<<destination)&legalMovesRook)
			{
				blackRook&=~(1ULL<<source);
				blackRook|=(1ULL<<destination);	
			}
			else
			{
				fillPieceArray();
				//cout<<"The move is not legal"<<endl;
				validMove=0;
				return;
			}
		}
		displayBoard(legalMovesRook);
		
	}
	else if(pieceToMove=='B' || pieceToMove=='b')
	{
		long legalMovesBishop;
		if(turn%2==1)
		{
			legalMovesBishop=bishop.generateLegalMovesForBishop(source,'w',whiteEnemyAndEmptySquares,fullBoard);
			if((1ULL<<destination)&legalMovesBishop)
			{
				whiteBishop&=~(1ULL<<source);
				whiteBishop|=(1ULL<<destination);
			}
			else
			{
				fillPieceArray();
				validMove=0;
			}
		}
		else
		{
			legalMovesBishop=bishop.generateLegalMovesForBishop(source,'b',blackEnemyAndEmptySquares,fullBoard);
			if ((1ULL<<destination)&legalMovesBishop)
			{
				blackBishop&=~(1ULL<<source);
				blackBishop|=(1ULL<<destination);
			}
			else
			{
				fillPieceArray();
				validMove=0;
			}
		}
	}
	else if(pieceToMove=='N' || pieceToMove=='n')
	{
		if (turn%2==1)
		{
			whiteKnight&=~(1ULL<<source);
			whiteKnight|=(1ULL<<destination);
		}
		else
		{
			blackKnight&=~(1ULL<<source);
			blackKnight|=(1ULL<<destination);
		}
	}
	else if(pieceToMove=='Q' || pieceToMove=='q')
	{
		if (turn%2==1)
		{
			long legalMovesQueen=rook.generateLegalMovesForRook(source,'w',whiteEnemyAndEmptySquares,fullBoard) | bishop.generateLegalMovesForBishop(source,'w',whiteEnemyAndEmptySquares,fullBoard);
			if ((1ULL<<destination)&legalMovesQueen)
			{	
				whiteQueen&=~(1ULL<<source);
				whiteQueen|=(1ULL<<destination);
			}
			else
			{
				//fillPieceArray();
				validMove=0;
			}
		}
		else
		{
			long legalMovesQueen=rook.generateLegalMovesForRook(source,'b',blackEnemyAndEmptySquares,fullBoard) | bishop.generateLegalMovesForBishop(source,'b',blackEnemyAndEmptySquares,fullBoard);
			if ((1ULL<<destination)&legalMovesQueen)
			{
				blackQueen&=~(1ULL<<source);
				blackQueen|=(1ULL<<destination);
			}
			else
			{
				fillPieceArray();
				validMove=0;
			}
		}
	}
	else if(pieceToMove=='K' || pieceToMove=='k')
	{
		if (turn%2==1)
		{
			whiteKing&=~(1ULL<<source);
			whiteKing|=(1ULL<<destination);
		}
		else
		{
			blackKing&=~(1ULL<<source);
			blackKing|=(1ULL<<destination);
		}
	}
	recomputeBitboards();
	fillPieceArray();
}

int Board::getSquare(char sourceSquare[]) //converts a square to a bit number. Eg: D2=11
{

	int letter=sourceSquare[0]-'A';
	int digit=sourceSquare[1]-48;
	return letter+(digit-1)*8;
}
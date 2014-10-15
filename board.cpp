#include<iostream>
#include<bitset>
#include<string>
using namespace std;

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


Board::Board() //constructor
{
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
    setRookBoards();
        //fillPieceArray();
}

void Board::generateLegalMovesForRook(int bitPositionOfRook,char color)
{
    long rightMoves;
    long leftMoves;
    long upMoves;
    long downMoves;
    long rookMoves;
    
    rightMoves=rookRightBoard[bitPositionOfRook] & fullBoard;
    rightMoves=(rightMoves<<1) | (rightMoves<<2) | (rightMoves<<3) | (rightMoves<<4) | (rightMoves<<5) | (rightMoves<<6);
    rightMoves&=rookRightBoard[bitPositionOfRook];
    rightMoves^=rookRightBoard[bitPositionOfRook];
    
    if (color=='w')
        rightMoves&=whiteEnemyAndEmptySquares;
    else if(color='b')
        rightMoves&=blackEnemyAndEmptySquares;
    displayBoard(rightMoves);

}

void Board::setRookBoards()
{
    int j;
    for (int i = 0; i < 64; i++)
    {
        for (j = i+1; (j%8)!=0; j++)
            rookRightBoard[i]|=(1ULL<<j);

        for (j = i-1; (j%8)!=0; j--)
            rookLeftBoard[i]|=(1ULL<<j);
        rookLeftBoard[i]|=(1ULL<<j);

        for (j=i+8;j<=63;j+=8)
            rookUpBoard[i]|=(1ULL<<j);

        for(j=i-8;j>=0;j-=8)
            rookDownBoard[i]|=(1ULL<<j);

    }
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
    bitset<64> x(fullBoard);
    cout<<x<<endl;
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
    /*cout<<"moving d2 pawn to d3"<<endl;;
    whitePawn&=~(1<<12);
    whitePawn|=(1<<20);
    recomputeBitboards();
    fillPieceArray();*/
    turn++;
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
        if (turn%2==1)
        {
            generateLegalMovesForRook(destination,'w');
            whiteRook&=~(1ULL<<source);
            whiteRook|=(1ULL<<destination);                
        }
        else
        {
            generateLegalMovesForRook(destination,'b');
            blackRook&=~(1ULL<<source);
            blackRook|=(1ULL<<destination);
        }
        
    }
    else if(pieceToMove=='B' || pieceToMove=='b')
    {
        if(turn%2==1)
        {
            whiteBishop&=~(1ULL<<source);
            whiteBishop|=(1ULL<<destination);
        }
        else
        {
            blackBishop&=~(1ULL<<source);
            blackBishop|=(1ULL<<destination);
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
            whiteQueen&=~(1ULL<<source);
            whiteQueen|=(1ULL<<destination);
        }
        else
        {
            blackQueen&=~(1ULL<<source);
            blackQueen|=(1ULL<<destination);
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

int main()
{
	Board board=Board();
	cout<<endl;
    while(1)
    {
	   board.makeMove();
    }
	return 0;
}
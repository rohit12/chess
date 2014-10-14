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
	long magicNumberRook[64]={0xa180022080400230, 0x40100040022000, 0x80088020001002, 0x80080280841000, 0x4200042010460008, 0x4800a0003040080, 0x400110082041008, 0x8000a041000880, 0x10138001a080c010, 0x804008200480, 0x10011012000c0, 0x22004128102200, 0x200081201200c, 0x202a001048460004, 0x81000100420004, 0x4000800380004500, 0x208002904001, 0x90004040026008, 0x208808010002001, 0x2002020020704940, 0x8048010008110005, 0x6820808004002200, 0xa80040008023011, 0xb1460000811044, 0x4204400080008ea0, 0xb002400180200184, 0x2020200080100380, 0x10080080100080, 0x2204080080800400, 0xa40080360080, 0x2040604002810b1, 0x8c218600004104, 0x8180004000402000, 0x488c402000401001, 0x4018a00080801004, 0x1230002105001008, 0x8904800800800400, 0x42000c42003810, 0x8408110400b012, 0x18086182000401, 0x2240088020c28000, 0x1001201040c004, 0xa02008010420020, 0x10003009010060, 0x4008008008014, 0x80020004008080, 0x282020001008080, 0x50000181204a0004, 0x102042111804200, 0x40002010004001c0, 0x19220045508200, 0x20030010060a900, 0x8018028040080, 0x88240002008080, 0x10301802830400, 0x332a4081140200, 0x8080010a601241, 0x1008010400021, 0x4082001007241, 0x211009001200509, 0x8015001002441801, 0x801000804000603, 0xc0900220024a401, 0x1000200608243};

	char pieceRepresentation[8][8];
	char sourceSquare[2];
	char destinationSquare[2];
	char pieceToMove;
    int turn;
public:
	Board();
    void clearPieceRepresentation();
	void fillPieceArray();
	void displayBoard();
	void recomputeBitboards();
	void makeMove();
    void movePiece(char sourceSquare[],char destinationSquare[],char pieceToMove, int turn);
    int getSquare(char sourceSquare[]);
};

Board::Board()
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
    clearPieceRepresentation();
        //fillPieceArray();
}

void Board::clearPieceRepresentation()
{
    for (int i = 0; i < 64; i++)
    {
        pieceRepresentation[i/8][i%8]=' ';
    }
}

void Board::fillPieceArray()
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
void Board::displayBoard()
{
    /*bitset<64>x(fullBoard);
    cout<<x<<fullBoard<<endl;*/
    for(int i=0;i<64;i++)
    {
       if(i%8==0)
        {
            cout<<endl;
        }
        if(fullBoard & (1ULL<<i))
        {
            cout<<"1";
        }
        else
        {
            cout<<"0";
        }
        
    }
        
}

void Board::recomputeBitboards()
{
    whitePieces=whitePawn|whiteBishop|whiteRook|whiteKing|whiteQueen|whiteKnight;
    blackPieces=blackPawn|blackBishop|blackRook|blackKing|blackQueen|blackKnight;
    fullBoard=whitePieces|blackPieces;
}
void Board::makeMove()
{
    /*cout<<"moving d2 pawn to d3"<<endl;;
    whitePawn&=~(1<<12);
    whitePawn|=(1<<20);
    recomputeBitboards();
    fillPieceArray();*/
    turn++;
    cout<<turn;
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

void Board::movePiece(char sourceSquare[],char destinationSquare[],char pieceToMove, int turn)
{
    int source,destination;
    source=getSquare(sourceSquare);
    destination=getSquare(destinationSquare);
    if(pieceToMove=='p' || pieceToMove=='P')
    {
        cout<<"Piece to move is pawn"<<endl;
        if(turn%2==1)
        {
            whitePawn&=~(1ULL<<source);
            whitePawn|=(1ULL<<destination);
        }
        else if(turn%2==0)
        {
            cout<<"black pawn moved";
            bitset<64> x(blackPawn);
            cout<<x<<endl<<"source:"<<source<<"destination"<<destination<<endl;
            blackPawn&=~(1ULL<<source);
            blackPawn|=(1ULL<<destination);
        }
        
    }
    else if(pieceToMove=='r' || pieceToMove=='R')
    {
        if (turn%2==1)
        {
            whiteRook&=~(1ULL<<source);
            whiteRook|=(1ULL<<destination);                
        }
        else
        {
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

int Board::getSquare(char sourceSquare[])
{
    switch(sourceSquare[1])
    {
        case '1':
            switch(sourceSquare[0])
            {
                case 'A':
                case 'a':
                    return 0;
                break;

                case 'B':
                case 'b':
                    return 1;
                break;

                case 'C':
                case 'c':
                    return 2;
                break;

                case 'D':
                case 'd':
                    return 3;
                break;

                case 'E':
                case 'e':
                    return 4;
                break;

                case 'F':
                case 'f':
                    return 5;
                break;

                case 'G':
                case 'g':
                    return 6;
                break;

                case 'H':
                case 'h':
                    return 7;
                break;
            }
        break;
        case '2':
            switch(sourceSquare[0])
            {
                case 'A':
                case 'a':
                    return 8;
                break;

                case 'B':
                case 'b':
                    return 9;
                break;

                case 'C':
                case 'c':
                    return 10;
                break;

                case 'D':
                case 'd':
                    return 11;
                break;

                case 'E':
                case 'e':
                    return 12;
                break;

                case 'F':
                case 'f':
                    return 13;
                break;

                case 'G':
                case 'g':
                    return 14;
                break;

                case 'H':
                case 'h':
                    return 15;
                break;
            }
        break;
        case '3':
            switch(sourceSquare[0])
            {
                case 'A':
                case 'a':
                    return 16;
                break;

                case 'B':
                case 'b':
                    return 17;
                break;

                case 'C':
                case 'c':
                    return 18;
                break;

                case 'D':
                case 'd':
                    return 19;
                break;

                case 'E':
                case 'e':
                    return 20;
                break;

                case 'F':
                case 'f':
                    return 21;
                break;

                case 'G':
                case 'g':
                    return 22;
                break;

                case 'H':
                case 'h':
                    return 23;
                break;
            }
        break;
        case '4':
            switch(sourceSquare[0])
            {
                case 'A':
                case 'a':
                    return 24;
                break;

                case 'B':
                case 'b':
                    return 25;
                break;

                case 'C':
                case 'c':
                    return 26;
                break;

                case 'D':
                case 'd':
                    return 27;
                break;

                case 'E':
                case 'e':
                    return 28;
                break;

                case 'F':
                case 'f':
                    return 29;
                break;

                case 'G':
                case 'g':
                    return 30;
                break;

                case 'H':
                case 'h':
                    return 31;
                break;
            }
        break;
        case '5':
            switch(sourceSquare[0])
            {
                case 'A':
                case 'a':
                    return 32;
                break;

                case 'B':
                case 'b':
                    return 33;
                break;

                case 'C':
                case 'c':
                    return 34;
                break;

                case 'D':
                case 'd':
                    return 35;
                break;

                case 'E':
                case 'e':
                    return 36;
                break;

                case 'F':
                case 'f':
                    return 37;
                break;

                case 'G':
                case 'g':
                    return 38;
                break;

                case 'H':
                case 'h':
                    return 39;
                break;
            }
        break;
        case '6':
            switch(sourceSquare[0])
            {
                case 'A':
                case 'a':
                    return 40;
                break;

                case 'B':
                case 'b':
                    return 41;
                break;

                case 'C':
                case 'c':
                    return 42;
                break;

                case 'D':
                case 'd':
                    return 43;
                break;

                case 'E':
                case 'e':
                    return 44;
                break;

                case 'F':
                case 'f':
                    return 45;
                break;

                case 'G':
                case 'g':
                    return 46;
                break;

                case 'H':
                case 'h':
                    return 47;
                break;
            }
        break;
        case '7':
            switch(sourceSquare[0])
            {
                case 'A':
                case 'a':
                    return 48;
                break;

                case 'B':
                case 'b':
                    return 49;
                break;

                case 'C':
                case 'c':
                    return 50;
                break;

                case 'D':
                case 'd':
                    return 51;
                break;

                case 'E':
                case 'e':
                    return 52;
                break;

                case 'F':
                case 'f':
                    return 53;
                break;

                case 'G':
                case 'g':
                    return 54;
                break;

                case 'H':
                case 'h':
                    return 55;
                break;
            }
        break;
        case '8':
            switch(sourceSquare[0])
            {
                case 'A':
                case 'a':
                    return 56;
                break;

                case 'B':
                case 'b':
                    return 57;
                break;

                case 'C':
                case 'c':
                    return 58;
                break;

                case 'D':
                case 'd':
                    return 59;
                break;

                case 'E':
                case 'e':
                    return 60;
                break;

                case 'F':
                case 'f':
                    return 61;
                break;

                case 'G':
                case 'g':
                    return 62;
                break;

                case 'H':
                case 'h':
                    return 63;
                break;
            }
        break;
    }
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
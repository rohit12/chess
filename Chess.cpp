#include "Headers/Board.h"
#include "Headers/Rook.h"
#include <iostream>
using namespace std;

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
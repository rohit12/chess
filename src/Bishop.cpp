#include "../Headers/Bishop.h"
#include <bitset>
#include <iostream>
using namespace std;
Bishop::Bishop()
{
	setBishopBoards();
}

void Bishop::setBishopBoards()
{
	int j;
	for (int i = 0; i < 64; i++)
	{
		for (j = i+9; (j+1)%8!=0; j+=9)
		{
			if ((j-8)%8==0)
			{
				break;
			}
			fortyFiveDegreeBoard[i]|=(1ULL<<j);
		}
		if((j-8)%8!=0)
			fortyFiveDegreeBoard[i]|=(1ULL<<j);
	}
	//bitset<64> x(fortyFiveDegreeBoard[3]);
	display(fortyFiveDegreeBoard[54]);
}

void Bishop::display(long xyz)
{
	cout<<"displaying board"<<endl;
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

int main()
{
	Bishop bishop=Bishop();
	return 0;
}
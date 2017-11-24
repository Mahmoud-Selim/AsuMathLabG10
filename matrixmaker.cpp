#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h> 
using namespace std;
int main()
{
	ofstream outfile("/media/mahmoud/7618274718270629/F/Comp-Third\ year/Software\ Engineering/Project/testmatrix.m");
	if (!outfile.bad())
	{
	outfile<<"A = ["<<endl;
	for ( int i = 0 ; i < 32 ; i++)
	{
		for ( int j = 0 ; j < 32 ; j++)
		{
			outfile<<rand()%100<<"  ";
		}
		outfile<<";"<<endl;
	}
		outfile<<"];"<<endl;	
	outfile<<"B = ["<<endl;
	for ( int i = 0 ; i < 32 ; i++)
	{
		for ( int j = 0 ; j < 32 ; j++)
		{
			outfile<<rand()%100<<"  ";
		}
		outfile<<";"<<endl;
	}
		outfile<<"];"<<endl;	
		outfile.close();
		cout<<"File write succeeded."<<endl;
	}
	else
	cout<<"File write failed."<<endl;
	return 0;
}

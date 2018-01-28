/*
 * Team10.cpp
 *
 *  Created on: Oct 26, 2017
 *      Author: mahmoud
 */
#include "MatLibrary.h"
#include "assistingfunctions.h"
#include "Mystring.h"
#include <fstream>
#include "MatLibrary.h"
#include "assistingfunctions.h"
#include "Mystring.h"
#include <fstream>
#include "linked.h"

int main(int argc ,char* argv[])
{
	/*string s;
	ifstream infile("bigexample.m");
	if(!infile.bad())
	{
		while(getline(infile, s))
		{
//				std::cout<<s<<std::endl;
			start_f(s);
//			std::cout<<std::endl;
		}
		infile.close();
	}*/
	string s;
	if (argc > 1 )
	{
		ifstream infile(argv[1]);
		if(!infile.bad())
		{
			while(getline(infile, s))
			{
//				std::cout<<s<<std::endl;
				start_f(s);
//				std::cout<<std::endl;
			}
			infile.close();
		}
	}
	else
	{
		while(1)
		{
			std::getline(cin , s);
			start_f(s);
		}
	}
    KILLLIST();
    return 0;
}






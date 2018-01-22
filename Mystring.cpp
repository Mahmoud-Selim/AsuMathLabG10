/*
 * Mystring.cpp
 *
 *  Created on: Oct 28, 2017
 *      Author: mohamed
 */

#include "Mystring.h"
#include "MatLibrary.h"
#include "linked.h"
char* trim(char* text)
{
	char* p = text + strlen(text) - 1;//pointing pointer to the end of the string
	while(*p == ' ' || *p == '\t' || *p == '\r')
	{
		*p--='\0';
	}
	p = text; //pointing pointer to the start of the string
	while(*p == ' ' || *p == '\t' || *p == '\r')
	{
		p++;
	}
	return p;
}
/*
 *
 *
 * getOperand1 function
 *
 */
string getOperand1( string s)
{
	int i =0 ;
	char *text=new char [s.length()+1];
	strcpy(text,s.c_str());
	char *ttext =trim(text);
	char separators[] = "=+-*/\' ";
	char* token = strtok(ttext, separators);
	if (getOperation(s) == NoOperation)
	{
		token  = strtok(NULL , separators);
		if (ISEXISTING(token))
		{
			return token;
		}
		return "no operand";
	}
	while(token)
	{
		i++;
		token = strtok(NULL, separators);
		while(token)
		{
			if(i == 1 ) // it expects first operand in first iteration
			{
				return token ;//it will find the second operand in the second iteration
			}

		}

	}
	return "no operand";
}
/*
 *
 *
 * getOperand2 function
 *
 */
string getOperand2( string s)
{
	int i=0;//counter
	char *text=new char [s.length()+1];
	strcpy(text,s.c_str()); //converting string into array of characters
	char *ttext =trim(text);//trimmed array
	char spearators[] = "=+-*\'/. ";
	char* token = strtok(ttext, spearators);
	while(token)
	{
		i++;
		token = strtok(NULL, spearators);
		if(token)// condition da 3asha case law "A=B"
		{
			if(i==2)
				{
					return token ;//it will find the second operand in the second iteration
				}
		}
		else return"No operand";

	}
	return"No operand";
}
/*
 *
 *
 * getOperation function
 *
 */
int getOperation ( string s )
{
	for (unsigned int i = 0 ; i < s.length(); i++ )
	{
		if ( s[i] == '+' ) { return addition ; }
		if ( s[i] == '-' ) { return subtraction ; }
		if ( s[i] == '/' ) { return division ; }
		if ( s[i] == '*' ) { return multiplication ; }
		if ( s[i] == '\'' ) { return transpose;}
		if ( s[i] == '.' && s[i+1] == '/') {return elementWiseDivision;}
		if ( s[i] == '.' && s[i+1] == '+') { return elementWiseAddition ; }
		if ( s[i] == '.' && s[i+1] == '-') { return elementWiseSubtraction ; }
		if ( s[i] == '.' && s[i+1] == '*') { return elementWiseMultiplication ; }
		if ( s[i] == '&' ) { return and ; }
		if ( s[i] == 'b' && s[i+1] == 'i' && s[i+2] == 't' && s[i+3] == 'a') { return bitand ; }
		if ( s[i] == 'f' && s[i+1] == 'a' && s[i+1] == 'c') { return factorial ; }

	}
	return NoOperation ;
}
/*
 *
 *
 * getRows
 *
 */

int getRowsNumber ( string s )
{
	int i=0 , flag;//counter
	char *text=new char [s.length()+1];
	strcpy(text,s.c_str()); //converting string into array of characters
	char *ttext =trim(text); //trimmed array
	char spearators[] = "=;";
	char* token = strtok(ttext, spearators);
	while(token)
	{
		token = strtok(NULL, spearators);
		i++;
	}
	for (int j = 0 ; j < s.length()-1 ; j++)
	{
		if (s[s.length()-j] == ']')
		{
			flag = 1;
		}
		if ( flag == 1 && s[s.length()-(j+1)] == ' ')
		{
			continue;
		}
		if (flag == 1 && s[s.length() - (j+1)] == ';')
		{
			i--;
			break;
		}
		else
		{
			if ( flag == 1)
			{
				break;
			}
		}
	}
	return i-1;
}
/*
 *
 *
 * getColumns
 *
 */
int getColumnsNumber (string s)
{
	int i=-1;
	char *text=new char [s.length()+1];
	strcpy(text,s.c_str()); //converting string into array of characters
	text =trim(text);//trimmed array
	char spearators[] = "=;][ ";
	char* token = strtok(text, spearators);
	while(token)
	{
		token = strtok(NULL, spearators);
		i++;
	}
	return i/getRowsNumber(s);
}



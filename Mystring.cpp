/*
 * Mystring.cpp
 *
 *  Created on: Oct 28, 2017
 *      Author: mohamed
 */

#include "Mystring.h"
#include "MatLibrary.h"
#include "linked.h"
#include <cstdlib>
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
	char separators[] = "=+-*/\'^&| ";
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
 * getOperand1 if between brackets()
 *
 */
 string getOperand1Bracket( string s)
 {
     int pos1=s.find("(");
     int pos2=s.find(")");
    string temp= s.substr(pos1+1,pos2-pos1-1);
     char* str=new char[temp.length() + 1];;
    strcpy(str,temp.c_str());
    return trim(str);
 }

 string getbase(string s)
{
    int pos1=s.find("g");
    int pos2=s.find("(");

    string string_base=s.substr(pos1+1,pos2-pos1-1);
    char* str;

    return string_base;
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
	char spearators[] = "=+-*\'/.^&| ";
	char separators [] = "=+-*\'/^&| ";
	char* token = strtok(ttext, spearators);
	while(token)
	{
		i++;
		if(i < 2)
		{
			token = strtok(NULL, spearators);
		}
		else
		{
			token = strtok(NULL, separators);
			if(*token == '.')
			token = strtok(NULL , separators);
		}
		if(token)// condition da 3asha case law "A=B"
		{
			if(i==2)
			{
				if(*(token-1) == '-')
				token = token -1;
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
		if ( s[i] == '^' ) { return Power;}
		if ( s[i] == '.' && s[i+1] == '/') {return elementWiseDivision;}
     		if ( s[i] == '.' && s[i+1] == '^') {return elementWisePower;}
		if ( s[i] == 's' && s[i+1] == 'q' ) { return squareRoot ; }
		if ( s[i] == 's' && s[i+1] == 'i' && s[i+2] == 'n' ) { return SinFn ; }
		if ( s[i] == 'c' && s[i+1] == 'o' && s[i+2] == 's') { return CosFn ; }
		if ( s[i] == 't' && s[i+1] == 'a' && s[i+2] == 'n') { return TanFn ; }
		if ( s[i] == 's' && s[i+1] == 'e' && s[i+2] == 'c') { return SecFn ; }
		if ( s[i] == 'c' && s[i+1] == 's' && s[i+2] == 'c') { return CscFn ; }
		if ( s[i] == 'c' && s[i+1] == 'o' && s[i+2] == 't') { return CotFn ; }
		if ( s[i] == 'l' && s[i+1] == 'o' && s[i+2] == 'g') { return LogFn ; }
		if ( s[i] == 'l' && s[i+1] == 'n') { return ln ; }
		if ( s[i] == '&' ) { return AND ; }
		if ( s[i] == '|' ) { return OR ; }
		if ( s[i] == 'f' && s[i+1] == 'a' && s[i+2] == 'c') { return factorial ; }
		if ((s[i] == 'o')&&(s[i+1] == 'n')&&(s[i+2] == 'e')&&(s[i+3] == 's'))
		{return ones;}
		if (s[i] == 'z'&&s[i+1] == 'e'&&s[i+2] == 'r'&&s[i+3] == 'o'&&s[i+4] == 's')
		{return zeros;}
		if (s[i] == 'e'&&s[i+1] == 'y'&&s[i+2] == 'e')
		{return eye;}
		if (s[i] == 'r'&&s[i+1] == 'a'&&s[i+2] == 'n'&&s[i+3] == 'd')
		{return Rand;}

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
	if (getOperation (s) ==zeros ||getOperation (s) ==eye||getOperation (s) ==Rand||getOperation (s) ==ones)
	{
	int f=0,n=0;;
	int nR=0,nC=0;
	f=s.find ("(");
	f++;
	n=s.find(",");
	string x=s.substr(f,f-n);
	nR=atoi(x.c_str());
	return nR;
	}
	else
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
}
/*
 *
 *
 * getColumns
 *
 */
int getColumnsNumber (string s)
{
	if (getOperation (s) ==zeros ||getOperation (s) ==eye||getOperation (s) ==Rand||getOperation (s) ==ones)
	{
	int f=0,n=0;
	int nR=0,nC=0;
	f=s.find ("(");
	f++;
	n=s.find(",");
n++;
f=s.find (")");
	string x=s.substr(n,f-n);
	nC=atoi(x.c_str());
	return nC;
	}
	else
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
}




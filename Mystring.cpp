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
string trimString(string s)
{
	unsigned long i;
	for(i = 0; i < s.length(); i++)
	{
		if(s[i] != ' ')
			break;
	}
	s = s.substr(i);
	for(i = s.length(); i > 0; i--)
	{
		if(s[i] != ' ')
			break;
	}
	s = s.substr(0,i);
	return s;
}
/*char* trim(char* text)
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
}*/
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
	char separators[] = "=+-*/\'^ ";
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

 bool isOperation(char s)
 {
	 if(s == '+' || s == '-' || s == '*' || s == '/' || s == '.')
		 return 1;
	 return 0;
 }

 bool isTringometric(string s)
 {
	 if(s == "sin")
		 return 1;
	 else if (s == "cos")
		 return 1;
	 else if (s == "tan")
		 return 1;
	 else if (s == "cot")
		 return 1;
	 else if (s == "sec")
		 return 1;
	 else if (s == "csc")
		 return 1;
	 else
		 return 0;
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
	char spearators[] = "=+-*\'/.^ ";
	char separators [] = "=+-*\'/^ ";
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
	int bracesNumber = 0;
	for (unsigned int i = 0 ; i < s.length(); i++ )
	{
		if(s[i] == '[')
			bracesNumber++;
		else if(s[i] == ']')
			bracesNumber--;
		if(bracesNumber == 0)
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
	int operation = getOperation(s);
	if (operation  ==zeros ||operation==eye||operation ==Rand||operation ==ones)
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
/*		unsigned int i  , rowsNumber = 0 , concatLength, bracesNumber = 1;//bracesNumber = 1;
		string accumulator = "";
		CMatrix* elementMatrix = NULL;
		for (i = s.find('[')+1; i < s.length()  ; i++)
		{
			if((s[i] == '[' && s[i-1] !=';') && (s[i] == '[' && s[i-1] != '['))
			{
				if((s[i] == '[' && s[i-1] !=';') || (s[i] == '[' && s[i-1] != '['))
				{
					bracesNumber++;
	//				i++;
					do
					{
						i++;
						if(s[i] == '[')
							bracesNumber++;
						if(s[i] == ']')
							bracesNumber--;
					}
					while(bracesNumber != 1);
				}
				if(s[i] == ' ' && (s[i-1] == ';' || s[i-1] == '['))
				{
					s.erase(s.begin()+i);
		//			i--;
				}
				if((s[i-1] == ';' || s[i-1] == '[') )
				{
					if((s[i] >='0' && s[i] <= '9') || s[i] == '-')
					{
						rowsNumber++;
					}

					else if(isalpha(s[i]))
					{
						do
						{
							accumulator += s[i];
							i++;
						}
						while(s[i] != ' ' && s[i] != ';' && s[i] != '[');
						i--;
						elementMatrix = ISEXISTING(accumulator);
						if(elementMatrix == NULL)
						{
							throw("Error, invalid input matrix");
						}
						else
						{
							rowsNumber += elementMatrix->getRowsNumber();
						}
						accumulator = "";
					}
					else if(s[i] == '[')
					{
						unsigned int start = i;
						bracesNumber++;
		//				i++;
						do
						{
							i++;
							if(s[i] == '[')
								bracesNumber++;
							if(s[i] == ']')
								bracesNumber--;
						}
						while(bracesNumber != 1);
						concatLength = i-start+1;
						rowsNumber += getRowsNumber(s.substr(i,concatLength));
						i += concatLength;
					}
					//i = s.find(';',i);
				}
			}
			return rowsNumber;
		}*/
		unsigned int i  , rowsNumber = 0 , concatLength;//bracesNumber = 1;
		string accumulator = "";
		CMatrix* elementMatrix = NULL;
		for (i = s.find('[')+1; i < s.length() -1 ; i++)
		{
			if((s[i] == '[' && s[i-1] !=';') && (s[i] == '[' && s[i-1] != '['))
			{
				i = s.find(']',i);
			}
			if((s[i] == ' ' && (s[i-1] == ';' || s[i-1] == '[')) || (s[i] == ' ' && s[i-1]==' '))
			{
				s.erase(s.begin()+i);
				i--;
				continue;
			}
			if((s[i-1] == ';' || s[i-1] == '[') )
			{
				if((s[i] >='0' && s[i] <= '9') || s[i] == '-')
				{
					rowsNumber++;
				}

				else if(isalpha(s[i]) || s[i] == '#')
				{
					do
					{
						accumulator += s[i];
						i++;
					}
					while(s[i] != ' ' && s[i] != ';' && s[i] != '[' && s[i] != ']');
					i--;
					elementMatrix = ISEXISTING(accumulator);
					if(elementMatrix == NULL)
					{
						throw("Error, invalid input matrix");
					}
					else
					{
						rowsNumber += elementMatrix->getRowsNumber();
					}
					accumulator = "";
				}
				else if(s[i] == '[')
				{
					concatLength = 1;
					unsigned int internalBracesNumber =2, counter = 0;
					while(internalBracesNumber != 1)
					{
						concatLength++;
						if(s[i+concatLength] =='[')
							internalBracesNumber++;
						else if(s[i+concatLength]  == ']')
							internalBracesNumber--;
					}

					rowsNumber += getRowsNumber(s.substr(i,concatLength+1));
					i += concatLength;
				}
				//i = s.find(';',i);
			}
		}
		return rowsNumber;
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
	int operation = getOperation(s);
	if (operation ==zeros ||operation ==eye||operation ==Rand||operation==ones)
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

		unsigned int i ,columnsNumber = 0 , concatLength, internalColumnsNumber, internalStringBraces = 0, safeRecursion = 0;
		string row = "" , elementMatrix = "", internalString, ID;
		CMatrix* elementMatrix_ptr = NULL;
		ID = getID(s);
		s = s.substr(s.find('=')+1);
		s = trimString(s);
		while(s[0] == '[' && s[s.length()-1] == ']')
		{
			s = s.substr(1,s.length()-2);
			s = trimString(s);
		}
		s = '[' + s + ']';
		for(i = s.find('[')+1 ; i < s.length() - 1 ; i++)
		{
			if(s[i - 1] == '[' && s[i] == ' ')
			{
				s.erase(s.begin()+i);
			}
			if(s[i] == '[')
			{
				concatLength = s.find(']' , i) - i;
				row += s.substr(i,concatLength+1);
				i = s.find(']' , i);
			}
			else if (s[i] == ';')
			{
				break;
			}
			else
			{
				row += s[i];
			}
		}
		internalString = s.substr(0,s.find('[')+1)+s.substr(s.find('[')+row.length()+2);
		for(i = 0; i < internalString.length(); i++)
		{

			if(internalString[i] == '[')
				internalStringBraces++;
			else if(internalString[i] == ']')
				internalStringBraces--;
			else if(internalString[i] != ' ' && internalStringBraces == 1)
			{
				safeRecursion = 1;
				break;
			}
		}
		if(safeRecursion)
			internalColumnsNumber = getColumnsNumber(internalString);
		for(i = 0; i < row.length() ; i++)
		{
			if((row[i] >= '0' && row[i] <= '9') || row[i] == '-')
			{
				columnsNumber++;
				while(row[i+1] != ' ' && row[i+1] != ',' && row[i+1] != '[' && row[i+1] != ';' && i+1 <row.length())
				{
					i++;
				}
			}
			else if(isalpha(row[i]) || row[i] == '#')
			{
				elementMatrix += row[i];
				while(row[i+1] != ' ' && row[i+1] != ',' && row[i+1] != '[' && row[i+1] != ']' && row[i+1] != ';' && i+1 <row.length())
				{
					i++;
					elementMatrix += row[i];
				}
				elementMatrix_ptr = ISEXISTING(elementMatrix);
				if(elementMatrix_ptr == NULL)
					throw("Error, invalid input matrix");
				else columnsNumber += elementMatrix_ptr->getColumnsNumber();
				elementMatrix = "";
			}
			else if(row[i] == '[')
			{
				concatLength = row.find(']',i)-i+1;
				columnsNumber += getColumnsNumber(row.substr(i,concatLength));
				i += concatLength -1;
			}
		}
		if(internalColumnsNumber != columnsNumber && safeRecursion)
			throw("Error... invalid matrix assignment\n");
		return columnsNumber;
	}
}








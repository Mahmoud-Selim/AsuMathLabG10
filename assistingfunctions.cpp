/*
 * assistingfunctions.cpp
 *
 *  Created on: Oct 28, 2017
 *      Author: mahmoud
 */
#include "MatLibrary.h"
#include "assistingfunctions.h"
#include "Mystring.h"
#include "linked.h"
#include "cstdlib"
#include <string>
using namespace std;
void extractAndAssign (string s, CMatrix* M, unsigned long noRows, unsigned long noCoulmns)
{
    int loc1    = s.find("[") ;
    int loc2    = s.find("]") ;
    string text = s.substr(loc1 + 1 , loc2-loc1-1);
    char* C_text = new char[text.length()+1];
    strcpy(C_text , text.c_str());
    C_text = trim(C_text);
    double** mPtr = M->getMatrixPtr();
    char separators[] = " ;,";
    char* token = strtok(C_text, separators);
    for (unsigned int i=0; i<noRows ; i++)
    {
        for(unsigned int y=0; y<noCoulmns; y++)
        {
            mPtr[i][y] = atof(token);
            token = strtok(NULL, separators);
        }
    }
   // delete[] C_text;
}

CMatrix* createAndAssign(string s)
{
	string ID = getID(s);
	string operand1 = getOperand1(s);
	CMatrix* result_ptr;
	if (operand1 == "no operand")
	{
		unsigned long rowsNumber    = getRowsNumber(s);
		unsigned long columnsNumber = getColumnsNumber(s);
		result_ptr = INSERT(ID , rowsNumber , columnsNumber);
		extractAndAssign(s , result_ptr , rowsNumber , columnsNumber);
	}
	else
	{
		CMatrix* operand = ISEXISTING(operand1);
		unsigned long rowsNumber    = operand->getRowsNumber();
		unsigned long columnsNumber = operand->getColumnsNumber();
		result_ptr = INSERT(ID , rowsNumber , columnsNumber);
		(*result_ptr) = operand;
	}
	return result_ptr;
}

void assignMatrix (string s)
{
	string ID = getID(s);
	string operand1 = getOperand1(s);
	CMatrix* result = ISEXISTING(ID);
	if (operand1 == "no operand")
	{
		unsigned long rowsNumber    = getRowsNumber(s);
		unsigned long columnsNumber = getColumnsNumber(s);
		extractAndAssign(s , result , rowsNumber , columnsNumber);
	}
	else
	{
		CMatrix* operand = ISEXISTING(operand1);
		*result = operand;
	}
}

CMatrix* createAndEvaluate (string s)
{
	/*
	 * -opernadState  specifies which of the operands is double
	 * -operationMode specifies whether the element wise functions should
	 *   operate properly of in the inverted mode
	 */
	unsigned long i = 0, operandState = None , operationMode , operandValueFlag = 0;
	double operand1Value,operand2Value;
	string ID = getID(s);
	CMatrix* result_ptr;
    string operand1 , operand2;
    int j = s.find("(");
    int k = s.find("sqrt");
	if(j>0)
    {
        operand1 = getOperand1Bracket(s);
        std::cout<<std::endl<<" "<<operand1<<std::endl;
        if(k>0)
            operand2 = "0.5";
        else
            operand2 = "0";
    }
    else
    {
        operand1 = getOperand1(s);
    	operand2 = getOperand2(s);
    }
	if (operand1[0] == '-')
	{
		i++;
		operand1Value = -1.0 * ( (double) atof(operand1.substr(i).c_str()) );
		operandValueFlag = 1;
	}
	if (operand1[i] >= '0' && operand1[i] <= '9')
	{
		operandState = Operand1;
		if (operandValueFlag == 0)
		{
			operand1Value = (double) atof(operand1.substr(i).c_str()) ;
			operandValueFlag = 0;
		}
		i = 0;
	}
	if (operand2[0] == '-')
	{
		i++;
		operand2Value = -1.0 * ( (double) atof(operand2.substr(i).c_str()) );
		operandValueFlag = 1;
	}
	if (operand2[i] >= '0' && operand2[i] <= '9')
	{
		if (operandState == Operand1)
		{
			operandState = Both;
			i = 0;
		}
		else
		{
			operandState = Operand2;
			i = 0;
		}
		operationMode = NormalOperation;
		if (operandValueFlag == 0)
		{
			operand2Value = (double) atof(operand2.substr(i).c_str()) ;
			operandValueFlag = 0;
		}
	}
	if (operandState == Operand1)
	{
		operand2Value = operand1Value;
		operand1 = operand2;
		operationMode = InvertedOperation;
		operandState = Operand2;
	}
	if (operandState == None)
	{
		CMatrix* operand1_ptr = ISEXISTING(operand1);
		CMatrix* operand2_ptr = ISEXISTING(operand2);
		int operation = getOperation(s);
		unsigned long rowsNumber , columnsNumber;
		switch(operation)
		{
			case addition:
				rowsNumber    = operand1_ptr->getRowsNumber();
				columnsNumber = operand1_ptr->getColumnsNumber();
				result_ptr = INSERT(ID , rowsNumber ,columnsNumber);
				result_ptr->add(operand1_ptr , operand2_ptr);
				break;

			case subtraction:
				rowsNumber    = operand1_ptr->getRowsNumber();
				columnsNumber = operand1_ptr->getColumnsNumber();
				result_ptr = INSERT(ID , rowsNumber ,columnsNumber);
				result_ptr->subtract(operand1_ptr , operand2_ptr);
				break;

			case multiplication:
				rowsNumber    = operand1_ptr->getRowsNumber();
				columnsNumber = operand2_ptr->getColumnsNumber();
				result_ptr = INSERT(ID , rowsNumber ,columnsNumber);
				result_ptr->multiply(operand1_ptr , operand2_ptr);
				break;

			case division:
				rowsNumber    = operand1_ptr->getRowsNumber();
				columnsNumber = operand2_ptr->getColumnsNumber();
				result_ptr = INSERT(ID , rowsNumber ,columnsNumber);
				result_ptr->divide(operand1_ptr , operand2_ptr);
				break;


			case transpose:
				rowsNumber    = operand1_ptr->getColumnsNumber();
				columnsNumber = operand1_ptr->getRowsNumber();
				result_ptr = INSERT(ID , rowsNumber ,columnsNumber);
				result_ptr->transpose(operand1_ptr);
				break;
			case elementWiseDivision:
				rowsNumber    = operand1_ptr->getRowsNumber();
				columnsNumber = operand1_ptr->getColumnsNumber();
				result_ptr = INSERT(ID , rowsNumber ,columnsNumber);
				result_ptr->elementWiseDivide(operand1_ptr , operand2_ptr);
				break;
			case elementWisePower:
				rowsNumber    = operand1_ptr->getRowsNumber();
				columnsNumber = operand1_ptr->getColumnsNumber();
				result_ptr = INSERT(ID , rowsNumber ,columnsNumber);
				result_ptr->elementwisepower(operand1_ptr , operand2_ptr);
				break;
		}
	}
	else if (operandState == Operand1)
	{
	}
	else if (operandState == Operand2)
	{
		CMatrix* operand1_ptr = ISEXISTING(operand1);
		int operation = getOperation(s);
		unsigned long rowsNumber    = operand1_ptr->getRowsNumber();
		unsigned long columnsNumber = operand1_ptr->getColumnsNumber();
		result_ptr = INSERT(ID , rowsNumber ,columnsNumber);
		switch (operation)
		{
			case elementWiseDivision:
				result_ptr->elementWiseDivide(operand1_ptr , operand2Value , operationMode);
				break;

			case elementWisePower:
				result_ptr->elementwisepower(operand1_ptr , operand2Value);
				break;

            case Power:
                 result_ptr->power(operand1_ptr , operand2Value );
                 break;
			case squareRoot:
				result_ptr->elementwisepower(operand1_ptr , operand2Value);
				break;
            case SinFn:
				result_ptr->_Sin(operand1_ptr);
				break;
            case CosFn:
				result_ptr->_Cos(operand1_ptr);
				break;
            case TanFn:
				result_ptr->_Tan(operand1_ptr);
				break;
            case SecFn:
				result_ptr->_Sec(operand1_ptr);
				break;
            case CscFn:
				result_ptr->_Csc(operand1_ptr);
				break;
            case CotFn:
				result_ptr->_Cot(operand1_ptr);
				break;
		}
	}
	else if (operandState == Both)
	{
		int operation = getOperation(s);
		unsigned long rowsNumber    = 1;
		unsigned long columnsNumber = 1;
		result_ptr = INSERT(ID , rowsNumber ,columnsNumber);
		switch (operation)
        {
            case Power:
                 result_ptr->power(operand1Value , operand2Value );
        }
	}
	return result_ptr;
}
string getID ( string s )
{
	int loc = s.find("=") ;
	string ID = s.substr(0 , loc);
	char* C_ID = new char[ID.length() + 1];
	strcpy(C_ID , ID.c_str());
	C_ID = trim(C_ID);
	return C_ID ;
}
void Evaluate (string s)
{
	unsigned long i = 0, operandState = None , operationMode , operandValueFlag = 0;
	double operand1Value,operand2Value;
	string ID = getID(s);
	string operand1 , operand2;
    int j = s.find("(");
    int k = s.find("sqrt");
	if(j>0)
    {
        operand1 = getOperand1Bracket(s);

        if(k>0)
            operand2 = "0.5";
        else
            operand2 = "0";
    }
    else
    {
        operand1 = getOperand1(s);
    	operand2 = getOperand2(s);
    }

	CMatrix* result_ptr = ISEXISTING(ID);
	if (operand1[0] == '-')
	{
		i++;
		operand1Value = -1.0 * ( (double) atof(operand1.substr(i).c_str()) );
		operandValueFlag = 1;
	}
	if (operand1[i] >= '0' && operand1[i] <= '9')
	{
		operandState = Operand1;
		if (operandValueFlag == 0)
		{
			operand1Value = (double) atof(operand1.substr(i).c_str()) ;
			operandValueFlag = 0;
		}
		i = 0;
	}
	if (operand2[0] == '-')
	{
		i++;
		operand2Value = -1.0 * ( (double) atof(operand2.substr(i).c_str()) );
		operandValueFlag = 1;
	}
	if (operand2[i] >= '0' && operand2[i] <= '9')
	{
		if (operandState == Operand1)
		{
//			operandState == Both;
			i = 0;
		}
		else
		{
			operandState = Operand2;
			i = 0;
		}
		operationMode = NormalOperation;
		if (operandValueFlag == 0)
		{
			operand2Value = (double) atof(operand2.substr(i).c_str()) ;
			operandValueFlag = 0;
		}
	}
	if (operandState == Operand1)
	{
		operand2Value = operand1Value;
		operand1 = operand2;
		operationMode = InvertedOperation;
		operandState = Operand2;
	}
	if (operandState == None)
	{
		CMatrix* operand1_ptr = ISEXISTING(operand1);
		CMatrix* operand2_ptr = ISEXISTING(operand2);
		int operation = getOperation(s);
		switch (operation)
		{
			case addition:
				result_ptr->add(operand1_ptr , operand2_ptr);
				break;
			case subtraction:
				result_ptr->subtract(operand1_ptr , operand2_ptr);
				break;
			case multiplication:
				result_ptr->multiply(operand1_ptr , operand2_ptr);
				break;
			case division:
				result_ptr->divide(operand1_ptr , operand2_ptr);
				break;
			case transpose:
				result_ptr->transpose(operand1_ptr);
				break;
			case elementWiseDivision:
				result_ptr->elementWiseDivide(operand1_ptr , operand2_ptr);
				break;
			case elementWisePower:
				result_ptr->elementwisepower(operand1_ptr , operand2_ptr);
				break;
		}
	}
	else if (operandState == Operand1)
	{
	}
	else if (operandState == Operand2)
	{
		CMatrix* operand1_ptr = ISEXISTING(operand1);
		int operation = getOperation(s);
		switch (operation)
		{
			case elementWiseDivision:
				 result_ptr->elementWiseDivide(operand1_ptr , operand2Value , operationMode);
                break;
            case elementWisePower:
                 result_ptr->elementwisepower(operand1_ptr , operand2Value );
                 break;
            case Power:
                 result_ptr->power(operand1_ptr , operand2Value );
                 break;
            case squareRoot:
                 result_ptr->elementwisepower(operand1_ptr , operand2Value );
                 break;
            case SinFn:
				result_ptr->_Sin(operand1_ptr);
				break;
            case CosFn:
				result_ptr->_Cos(operand1_ptr);
				break;
            case TanFn:
				result_ptr->_Tan(operand1_ptr);
				break;
            case SecFn:
				result_ptr->_Sec(operand1_ptr);
				break;
            case CscFn:
				result_ptr->_Csc(operand1_ptr);
				break;
            case CotFn:
				result_ptr->_Cot(operand1_ptr);
				break;
		}
	}
	else if (operandState == Both)
	{
          int operation = getOperation(s);
		switch (operation)
        {
            case Power:
                 result_ptr->power(operand1Value , operand2Value );
        }
	}
}
void startOperation(string s)
{
	char* C_S = new char[s.length()+1];
	strcpy(C_S , s.c_str());
	C_S = trim(C_S);
	if (s == "\n" || s == "\r" || s == "")
	{
		return;
	}
	string ID = getID(C_S);
	CMatrix* result_ptr = ISEXISTING(ID);
	int operation = getOperation(s);
	if (operation == NoOperation)
	{
		if (result_ptr == NULL)
		{
			result_ptr = createAndAssign(s);
		}
		else
		{
			assignMatrix(s);
		}
	}
	else
	{
		try
		{
			if (result_ptr == NULL)
			{
				result_ptr = createAndEvaluate(s);
			}
			else
			{
				Evaluate(s);
			}
		}
		catch(char const* Error )
		{
			std::cout<<Error<<std::endl;
			return;
		}
	}
	if(C_S[strlen(C_S)-1] != ';')
	{
		std::cout<<std::endl<<" "<<ID<<" ="<<std::endl;
		result_ptr->printMatrix();
	}
}

void start_f(string lineStr)
{
	static string s = "";
	if (lineStr[lineStr.length()-1] == '\r' || lineStr[lineStr.length()-1] == '\n')
	{
		s += lineStr.substr(0,lineStr.length()-1);
	}
	else
	{
		s += lineStr.substr(0,lineStr.length());
	}
	if ( (s.find('[') != (size_t)-1) && (s.find(']') ==(size_t) -1) )
	{
		return;
	}
	if (s == "\n" || s == "\r" || s == "")
	{
		return;
	}
//	std::cout<<s<<std::endl;
	startMatlab(s);
	s = "";
}
void startMatlab(string str)
{
	    //////////////// intialization
		int StartPos=0; //starting position for command
		int SemiPos=0; //pos for semi colon
		string str1;   //the new string which contains only 1 command
		int counter =0; // counter to count number of '='
		int i =0;
		////////////////


	int strlength=str.length();// length of origin string
		for(i=0;i<strlength;i++)
		{
			if(str[i]=='=')
			{

				if(counter>=1) // checking for muli command
				{
					SemiPos =str.rfind(';',i); // parameters of .find(character to find ,starting pos)
					str1=str.substr(StartPos,SemiPos+1-StartPos);//subtring (start position ,number of elements )
					//which is pos of ';' - start position

					StartPos=SemiPos+1; // new start postion is last ';' postion

					startOperation(str1); // call startOperation
				}

				counter++;
			}
		}
		// getting last command
		int y=str.rfind('=',strlength); //finding last command
		int z =str.rfind(';',y); //finding the last ';' before last command
		str1=str.substr(z+1,strlength-z); // getting last command
		startOperation(str1); //call startOperation for last command
}




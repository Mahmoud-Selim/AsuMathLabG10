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
#include "AdvancedMatrixString.h"
#include "AdvancedNumbersString.h"
using namespace std;

void extractAndAssign (string s, double** matrix_ptr, unsigned long rowsIterator, unsigned long columnsIterator)
{
	unsigned long i, k = 1, increaseRowsBy = 0;
	unsigned long startingColumn = columnsIterator;
	//double **matrix_ptr = M->getMatrixPtr();
	std::string accumlator;
	for(i = s.find('[') + 1; i < s.length(); i++)
	{
		if(s[i] == ';' && k == 1)
		{
			rowsIterator += increaseRowsBy;
			columnsIterator = startingColumn;
			continue;
		}
		if(s[i] == ' ' || s[i] == ',')
			continue;
		else if(s[i] == '[')
		{
			k++;
	//		continue;
		}
		else if(s[i] == ']')
		{
			k--;
	//		continue;
		}
		else
		{
			do
			{
				accumlator += s[i++];
			}
			while(s[i] != ' ' && s[i] != ';' && s[i] != ']' && s[i] != '[');
			i--;
		}
		if(((accumlator[0] >= '0' && accumlator[0] <= '9') || accumlator[0] == '-') && k == 1)
		{
			matrix_ptr[rowsIterator][columnsIterator] = (double)atof(accumlator.c_str());
			accumlator = "";
			columnsIterator++;
			increaseRowsBy = 1;
		}
		else if ((accumlator[0] >= 'a' && accumlator[0] <= 'z') || (accumlator[0] >= 'A' && accumlator[0] <= 'Z') || accumlator[0] == '#')
		{
			CMatrix *matrix = ISEXISTING(accumlator);
			increaseRowsBy = matrix->getRowsNumber();
			double **internalMatrix_ptr = matrix->getMatrixPtr();
			for(unsigned long rowsCounter = 0; rowsCounter < matrix->getRowsNumber(); rowsCounter++)
			{
				for(unsigned long columnsCounter = 0; columnsCounter <  matrix->getColumnsNumber(); columnsCounter++)
				{
					matrix_ptr[rowsIterator+rowsCounter][columnsIterator+columnsCounter] =
											internalMatrix_ptr[rowsCounter][columnsCounter];
				}
			}
			columnsIterator += matrix->getColumnsNumber();
			accumlator = "";
		}
		else if ( k > 1)
		{
			//accumlator = s.substr(i,s.find(']',i)-i);
			//accumlator = s.substr(i+1,s.find(']',i)-i+1);
			unsigned int accumlatorLength = 0;
			while(k != 1)
			{
				accumlatorLength++;
				if(s[i+accumlatorLength] == '[')
				{
					k++;
				}
				else if (s[i+accumlatorLength] == ']')
				{
					k--;
				}
				if(k == 1)
					break;
			}
			accumlator = s.substr(i,accumlatorLength+1);
			unsigned long accumlatorRowsNumber    = getRowsNumber(accumlator);
			unsigned long accumlatorColumnsNumber = getColumnsNumber(accumlator);
			extractAndAssign(accumlator, matrix_ptr, rowsIterator, columnsIterator);
/*			char* Caccumlator = new char[accumlator.length()+1];
			strcpy(Caccumlator,accumlator.c_str());
			char separators[] = "], ;";
			char *token = strtok(Caccumlator, separators);
			for(unsigned long rowsCounter = 0; rowsCounter < accumlatorRowsNumber; rowsCounter++)
			{
				for(unsigned long columnsCounter = 0; columnsCounter < accumlatorColumnsNumber; columnsCounter++)
				{
					if(!(rowsCounter == 0 && columnsCounter == 0))
					{
						token = strtok(NULL, separators);
					}
					matrix_ptr[rowsIterator+rowsCounter][columnsIterator+columnsCounter] = atof(token);

				}
			}
			*/
			columnsIterator += accumlatorColumnsNumber;
			increaseRowsBy = accumlatorRowsNumber;
			i += accumlator.length() - 1;
			accumlator = "";
		}
	}
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
		double** matrix_ptr = result_ptr->getMatrixPtr();
		extractAndAssign(s , matrix_ptr , 0 , 0);
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
		if(rowsNumber != result->getRowsNumber() || columnsNumber != result->getColumnsNumber())
		{
			CMatrix TempMatrix(rowsNumber, columnsNumber);
			double **TempMatrix_ptr = TempMatrix.getMatrixPtr();
			extractAndAssign(s,TempMatrix_ptr, 0, 0);
			result->copy(&TempMatrix);
			return;
		}
		double** matrix_ptr = result->getMatrixPtr();
		extractAndAssign(s , matrix_ptr, 0, 0);
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
    int z = s.find("log");
    int w= s.find("ln");
	int o =s.find ("ones");
	int ze =s.find ("zeros");
	int e =s.find("eye");
	int r =s.find("rand");

     if(j>0 && o<0 && ze<0 && e<0 && r<0)
    {
        operand1 = getOperand1Bracket(s);
        std::cout<<std::endl<<" "<<operand1<<std::endl;
        if(k>0)
            operand2 = "0.5";
        else if(z>0)
        {

        operand2=getbase(s);
           if (operand2=="")
                operand2="2.718281828459";

        }

        else if(w>0)
            operand2="2.718281828459";
	    
	else if (s.find("factorial") != string::npos)
	    operand2 = "1.0" ;

        else
            operand2 = "0";

    }
 else if ( o>0 || ze>0 || e>0 || r>0)
    {
        operand1=operand2="nonFound";
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
			case elementWiseMultiplication:
				result_ptr-> elementWiseMultiplication (operand1_ptr , operand2Value);
				break;
				
			case AND:
				rowsNumber    = operand1_ptr->getRowsNumber();
				columnsNumber = operand1_ptr->getColumnsNumber();
				result_ptr = INSERT(ID , rowsNumber ,columnsNumber);
				result_ptr-> AND (operand1_ptr , operand2_ptr);
				break;
				
			case OR:
				rowsNumber    = operand1_ptr->getRowsNumber();
				columnsNumber = operand1_ptr->getColumnsNumber();
				result_ptr = INSERT(ID , rowsNumber ,columnsNumber);
				result_ptr-> OR (operand1_ptr , operand2_ptr);
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

            		case LogFn:
				result_ptr->_Log(operand1_ptr,operand2Value);
               			break;

            		case ln:
               			result_ptr->_Log(operand1_ptr,operand2Value);
                		break;
				
	    		case factorial:
				result_ptr-> factorial (operand1_ptr );
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
if (o>0|| ze>0|| e>0|| r>0)
    {
        int operation = getOperation(s);
		//result_ptr = INSERT(ID , getRowsNumber(s) , getColumnsNumber(s));
        switch (operation)
        {
            case eye:
		result_ptr = INSERT(ID , getRowsNumber(s)  ,getColumnsNumber(s));
		result_ptr->eye(getRowsNumber(s) , getColumnsNumber(s));
		break;
            case zeros:
		result_ptr = INSERT(ID , getRowsNumber(s) ,getColumnsNumber(s));
                result_ptr->zeros(getRowsNumber(s) , getColumnsNumber(s));
                break;
            case ones:
		result_ptr = INSERT(ID , getRowsNumber(s) ,getColumnsNumber(s));
		result_ptr->ones(getRowsNumber(s) , getColumnsNumber(s));
		break;
            case Rand:
		result_ptr = INSERT(ID , getRowsNumber(s) ,getColumnsNumber(s));
		result_ptr->Rand(getRowsNumber(s) , getColumnsNumber(s));
		break;
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
    int z = s.find("log");
     int w=  s.find("ln");
	int o =s.find ("ones");
	int ze =s.find ("zeros");
	int e =s.find("eye");
	int r =s.find("rand");

	 if(j>0 && o<0 && ze<0 && e<0 && r<0)
    {
        operand1 = getOperand1Bracket(s);
        std::cout<<std::endl<<" "<<operand1<<std::endl;
        if(k>0)
            operand2 = "0.5";
        else if(z>0)
        {
            operand2=getbase(s);
           if (operand2=="")
                operand2="2.718281828459";


        }
        else if(w>0)
            operand2="2.718281828459";
		
	else if (s.find("factorial") != string::npos)
	    operand2 = "1.0" ;
		
        else
            operand2 = "0";

    }
else if ( o>0 || ze>0 || e>0 || r>0)
    {
        operand1=operand2="nonFound";
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
				
			case AND:
				result_ptr->AND(operand1_ptr , operand2_ptr);
				break;
			case OR:
				result_ptr->OR(operand1_ptr , operand2_ptr);
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
			case elementWiseAddition:
				result_ptr-> elementWiseAddition (operand1_ptr , operand2Value);
				break;
			case elementWiseSubtraction:	
				result_ptr-> elementWiseSubtraction (operand1_ptr , operand2Value, operationMode);
				break;
				
            		case Power:
                 		result_ptr->power(operand1_ptr , operand2Value );
                 		break;
				
			case addition:
				result_ptr-> elementWiseAddition (operand1_ptr , operand2Value);
				break;
				
			case subtraction:	
				result_ptr-> elementWiseSubtraction (operand1_ptr , operand2Value, operationMode);
				break;
				
			case elementWiseMultiplication:
				result_ptr-> elementWiseMultiplication (operand1_ptr , operand2Value);
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

            		case LogFn:
				result_ptr->_Log(operand1_ptr,operand2Value);
                		break;

            		case ln:
                		result_ptr->_Log(operand1_ptr,operand2Value);
                		break;
				
			case factorial:
				result_ptr-> factorial (operand1_ptr );
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
if  (o>0|| ze>0|| e>0|| r>0)
    {
        int operation = getOperation(s);
        switch (operation)
        {
            case eye:
		result_ptr->eye(getRowsNumber(s) , getColumnsNumber(s));
		break;
            case zeros:
                result_ptr->zeros(getRowsNumber(s) , getColumnsNumber(s));
                break;
            case ones:
		result_ptr->ones(getRowsNumber(s) , getColumnsNumber(s));
		break;
            case Rand:
		result_ptr->Rand(getRowsNumber(s) , getColumnsNumber(s));
		break;
        }
    }
}
void startOperation(string s)
{
	unsigned long i = 0;
	char* C_S = new char[s.length()+1];
	strcpy(C_S , s.c_str());
	C_S = trim(C_S);
	if (s == "\n" || s == "\r" || s == "")
	{
		return;
	}
	string ID = getID(C_S);
	CMatrix* result_ptr = ISEXISTING(ID);
	try
	{
		if ((int)s.find('=') > 0)
		{
			int operation = getOperation(s);
			if (operation == NoOperation)
			{
				s = s.substr(0,s.find('=')+1) + '[' + s.substr(s.find('=')+1) + ']';
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
				for(i = s.length()-1 ; i > 0 ; i--)
				{
					if(s[i] ==' ')
					{
						continue;
					}
					if(s[i] =='+')
					{
						throw("Error... Invalid expression");
					}
					else
					{
						break;
					}
				}
				if (result_ptr == NULL)
				{
					result_ptr = createAndEvaluate(s);
				}
				else
				{
					Evaluate(s);
				}
			}
		}
	}
	catch(char const* Error )
	{
			std::cout<<Error<<std::endl;
			return;
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
	unsigned long i,j = 0; static int missingbracelinestr = 0;
	if(missingbracelinestr == 1)
	{
		for(i = 0; i < lineStr.length(); i++)
		{
			if(lineStr[i] == ' ')
				continue;
			else if(lineStr[i] != ';')
			{
				s = s + ';';
				missingbracelinestr = 0;
				break;
			}
		}
	}
	if (lineStr[lineStr.length()-1] == '\r' || lineStr[lineStr.length()-1] == '\n')
	{
		s += lineStr.substr(0,lineStr.length()-1);
	}
	else
	{
		s += lineStr.substr(0,lineStr.length());
	}
	if (s == "\n" || s == "\r" || s == "" )
	{
		return;
	}
/*	if ( (s.find('[') != (size_t)-1) && (s.find(']') ==(size_t) -1) )
	{
		return;
	}*/
	for( i = 0 ; i < (unsigned long)s.length() ; i++)
	{
		if(s[i] == '[')
			j++;
		else if(s[i] == ']')
			j--;
	}

	if(j !=0)
	{
		unsigned int k = 0;
		for(k = s.length()-1 ; k > 0 ; k--)
		{
			if(s[k] ==' ')
				continue;
			if(s[k] != ';')
			{
				missingbracelinestr = 1;
				return;
			}

		}
	}
	for(i = s.length()-1 ; i > 0 ; i--)
	{
		if(s[i] ==' ')
		{
			continue;
		}
		if(s[i] =='+')
		{
			continue;
		}
	}
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

					complexExpressionHandler(str1); // call startOperation
				}

				counter++;
			}
		}
		// getting last command
		int y=str.rfind('=',strlength); //finding last command
		int z =str.rfind(';',y); //finding the last ';' before last command
		str1=str.substr(z+1,strlength-z); // getting last command
		complexExpressionHandler(str1); //call startOperation for last command
}
string expressionWhiteSpaceEraser(string s)
{
	unsigned long i, j;
	for(i = 0; i < s.length(); i++)
	{
		if(s[i] == ' '&& s[i + 1] == ' ')
		{
			s.erase(i+1,1);
			i -= 2;
		}
		if((s[i] == '(' || s[i] == '[' ||s[i] == ')' || s[i] == ']' || isOperation(s[i]))&& s[i + 1] == ' ')
		{
			s.erase(i+1,1);
			i -= 2;
		}
		if((s[i] == '(' || s[i] == '[' ||s[i] == ')' || s[i] == ']'  || isOperation(s[i])) && s[i-1] == ' ')
		{
			s.erase(i-1, 1);
			i -= 3;
		}
	}
	return s;
}
void complexExpressionHandler(string s)
{
	s = expressionWhiteSpaceEraser(s);
	int i, j, k, operation, previousNumberFlag = 0, MatOperation = 0;
	string accumulator;
	char previousLetter = s[s.find('[') + 1];
	operation = getOperation(s);
	if(operation == NoOperation)
	{
		for(i = s.find('[')+1; i < s.length(); i++)
		{
			//if(s[i] == '[' || s[i] == ']' || s[i] == ';' || s[i] == ',')
				//continue;
			if(s[i] != ' ' && !(s[i] == '[' || s[i] == ']' || s[i] == ';' || s[i] == ','))
			{
				if (accumulator == "")
					j = i;
				accumulator += s[i];
				continue;
			}
			if(accumulator == "")
				continue;
			for(k = 0; k < accumulator.length(); k++)
			{
				if(k < (int)accumulator.length() - 6)
				{
					string tringometricFunction;
					tringometricFunction = accumulator[k] + accumulator[k+1] + accumulator[k+2];
					if (isTringometric(tringometricFunction))
						k += 3;
				}
				if(isalpha(accumulator[k]))
				{
					MatOperation = 1;
				}
			}
			if(MatOperation == 1)
			{
				string temp = TokenMat(accumulator);
				s.replace(j, i-j, temp);
				i = i - (i - j) + temp.length();
				accumulator = "";
				MatOperation = 0;
			}
			else
			{
				string temp = TokenNum(accumulator);
				s.replace(j, i-j, temp);
				i = i - (i - j) + temp.length();
				accumulator = "";
			}
		}
		startOperation(s);
		/*if(MatOperation == 1)
		{
			string temp = TokenMat(accumulator);
			s.replace(j, j-i, temp);
			i = i - (j - i) + temp.length();
			accumulator = "";
		}
		else
		{
			string temp = TokenNum(accumulator);
			s.replace(j, i-j, temp);
			i = i - (i - j) + temp.length();
			accumulator = "";
		}
		startOperation(s);
		previousLetter = s[i];*/
	}
	else
	{
		for(i = s.find('=')+1; i < s.length(); i++)
		{
			if(s[i] == 'A')
			{
				AdOperation1Mat(s);
				return;
			}
		}
		Adoperation1Num(s);
	}
}



/*
 * assistingfunctions.h
 *
 *  Created on: Oct 28, 2017
 *      Author: mahmoud
 */



#ifndef ASSISTINGFUNCTIONS_H_
#define ASSISTINGFUNCTIONS_H_
#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include "AdvancedMatrixString.h"
#include "AdvancedNumbersString.h"
#include "MatLibrary.h"

using namespace std;
enum
{
	None,Operand1,Operand2,Both
};
void extractAndAssign (string s) ;
CMatrix* createAndAssign(string s );
void assignMatrix (string s);
CMatrix* createAndEvaluate (string s);
void Evaluate (string s);
char* trim(char*);
string getID(string s);
void startOperation(string s);
void start_f(string );
void startMatlab(string);
void complexExpressionHandler(string s);

#endif /* ASSISTINGFUNCTIONS_H_ */

/*
 * assistingfunctions.h
 *
 *  Created on: Oct 28, 2017
 *      Author: mahmoud
 */

#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
using namespace std;
#ifndef ASSISTINGFUNCTIONS_H_
#define ASSISTINGFUNCTIONS_H_


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

#endif /* ASSISTINGFUNCTIONS_H_ */

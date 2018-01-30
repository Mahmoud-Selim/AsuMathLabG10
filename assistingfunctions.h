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
#include "AdvMatrices.h"
#include "AdvNumbers.h"
#include "MatLibrary.h"

using namespace std;

enum
{
	None,Operand1,Operand2,Both
};


/*
 * @brief: This function parses a definition of a matrix and assigns it to the matrix.
 *        example A = [ 1 2 3]; so it takes the [1 2 3]; string and assigned it to A
 * @param string			   : it takes the definition of the matrix. the [1 2 3]; in the previous example.
 * @param CMatrix*			   : a pointer to the matrix that the definition will be assigned to( A in out example)
 * @param first unsigned long  : rows number of the matrix.
 * @param Second unsigned long : columns number of the matrix.
 * @return: void.
 */
void extractAndAssign (string s) ;

/*
 *@brief: This function is used when the user wants to define a new matrix, whether the user enters the definition
 *        him self or used a previously defined matrix. Example: A = [ 1 2 3]; or A = B;
 *@param string: the whole string that is entered by the user. In our example: A = [ 1 2 3]; or A = B;
 *@return CMatrix*: pointer the to result matrix(A in our example). This pointer is used for
 *					printing the matrix if the user wants to.
 */
CMatrix* createAndAssign(string s );

/*
 * @brief: This function is used when the user wants to define a previously defined matrix, whether the user
 * 		   enters the definition him self or used a previously defined matrix. Example: A = [ 1 2 3]; or A = B; and A is
 * 		   defined before.
 * @param string: the whole string entered by the user, for example A = [ 1 2 3]; or A = B; and A is defined before.
 * @return: void.
 */
void assignMatrix (string s);

/*
 * @brief: This function is used when the user wants to evaluate a statement and store the result in a new matrix.
 * 		   Example: A = C + D * E - F; and A is not defined before in the program.
 * @param string   : the whole string entered by the user. In our example, the string will be A = C + D * E - F;
 * @return CMatrix*: A pointer to the new matrix that will be used later for printing the matrix when required.
 */
CMatrix* createAndEvaluate (string s);

/*
 *@brief: This function is used when the user wants to evaluate a statement and store the result in a previously defined
 	 	  matrix, for example: A = C + D * E - F; and A is a previously defined matrix in the program.
 *@param string: the whole string entered by the user.  In our example, the string will be A = C + D * E - F;
 *@return: void.
 */
void Evaluate (string s);

/*
 * @brief: This function is used to eliminate the white spaces at the beginning and the end of a string.
 * 		   Example: if the string is "  A = B;  " the result will be "A = B;"
 * @param char* : C string that needs to be trimmed.
 * @return char*: A trimmed C string.
 */
char* trim(char*);

/*
 * @brief: This function is used to get the name- the ID we call it- of the result matrix.
 * 		   Example: if the input is A = B; then the output should be A;
 * @param string : the whole string of a statement entered by the user.
 * @return string: the ID( or the name) of the result matrix.
 */
string getID(string s);

/*
 *@brief: This function is used to operate on one and only one statement from the user input.
 *		  Example: A = B; or C = D;(note that A = B; C = D; is considered two statements in our case.)
 *@param string: the whole string of only one statement.
 *@return: void.
 */
void startOperation(string s);

/*
 * @brief: This function is used to handle files. It's main task is to add strings if a statement is written on several
 * 		   lines (note that this function does nothing if a line contains more than one statement like
 * 		   		  A = B; C = D; E = C * D;) and it only deals with statement written on many lines.
 * 		   Example: A = [ 1 2 3;
 * 		   				  4 5 6;
 * 		   				  7 8 9;];
 * @param string: only one line read from a specific file.
 * @return: void.
 */
void start_f(string );

/*
 * @brief: This function is used to handle many statements in one line. It evaluates a statement by statement.
 * 			Example: A = B; C = D;
 * @param string: one line entered from the user or read from the file.
 * @return: void.
 */
void startMatlab(string);

/*
 * @brief: This function replaces log functions for numeric values with matrices.
 * @Example: A = log10(5) becomes A=log10(B) where B is a 1x1 matrix
 * @param strring: input expression
 * @output string: output expression.
 */
string LogHandler(string s);

/*
 * @brief: This function handles complex expression input for matrix assignment.
 * @Example: A = [2+3 4*5 sin(0)] becomes A = [5 20 0]
 * @param strring: input expression
 * @output string: output expression.
 */
void complexExpressionHandler(string s);


#endif /* ASSISTINGFUNCTIONS_H_ */


/*
 * Mystring.h
 *
 *  Created on: Oct 28, 2017
 *      Author: mohamed
 */

#ifndef MYSTRING_H_
#define MYSTRING_H_
#include <string>
#include <string.h>
#include <iostream>
using namespace std;
char * Mytrim(char* text);
 /*
  * function used to trim string
  * parameter: input address of an array of string
  * return type :pointer to the trimmed string
  */
string getID(string s);
string getOperand1( string s);
/*
 * parameters :input string
 * return type : string containing first operand
 */
/*
 * parameters :input string
 * return type: string containg first operand if it is included between brackets
 */
string getOperand1Bracket( string s);
/*
 * parameters :input string
 * return type: string containg first operand if it is included between brackets
 */
string getOperand2( string s);
/*
 * parameters :input string
 * return type : string containing second operand
 */
int getOperation ( string s );
/*
 * parameters :input string
 * return type : int which determines operation
 * 0 -> NoPeration found
 * 1 -> Addition
 * 2 -> Subtraction
 * 3 -> Multiplication
 * 4 -> Division
 * 5 -> Transpose
 */
int getRowsNumber ( string s );
/*
 * used to get number of rows of a matrix
 * paramters :
 * input: string containing matrix
 * return :int number of rows
 */
int getColumnsNumber (string s);
/*
 * used to get number of columns of a matrix
 * paramters :
 * input: string containing matrix
 * return :int number of columns
 */

#endif /* MYSTRING_H_ */

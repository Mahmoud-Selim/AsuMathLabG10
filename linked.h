/*
 * linked.h
 *
 *  Created on: Oct 23, 2017
 *      Author: mohamed
 */

#ifndef LINKED_H_
#define LINKED_H_
#include <string>
#include <string.h>
using namespace std;

  struct node {
	string ID; //unique ID for every matrix
	node *next;//pointer to next structure in list
	CMatrix* Matrix ;  // pointer to Matrix
};


CMatrix* INSERT(string ID,int Nrows,int Ncolumns);
/*
 * Parameters : ID to the matrix ,number of rows,number of columns
 * return type : pointer to matrix
 * used to insert a new matrix in linked list
 */
CMatrix* ISEXISTING (string id);
/*
 * Parameters : Unique ID for Matrix
 * return type : pointer to Matrix for the given ID
 * used to get a pointer to the matrix of the given ID
 */

void KILLLIST(void);


#endif /* LINKED_H_ */

/*
 * MatLibrary.h
 *
 *  Created on: Oct 24, 2017
 *      Author: mahmoud
 */

#ifndef MATLIBRARY_H_
#define MATLIBRARY_H_

enum
{
	NoOperation,addition,subtraction,multiplication,division,transpose,elementWiseDivision,elementWisePower,Power,squareRoot,elementWiseMultiplication,OR,AND,factorial
};
enum
{
	NormalOperation,InvertedOperation
};

class CMatrix
{
	/*
	 * -Specifies the rows number and columns number in the matrix respectively.
	 */
	unsigned long rowsNumber , columnsNumber;


	/*
	 * -A 2-d pointer to the matrix.
	 * -matrix_ptr[row number][column number].
	 */
	double **matrix_ptr;

public:
	/*
	 * -Default constructor.
	 * -Parameters : void.
	 * -Sets the number of columns and the number of rows to zeros.
	 * -Sets the array_ptr and matrix_ptr to NULL.
	 */
	CMatrix(void);

	/*
	 * -Constructor.
	 * -Parameters : unsigned long , unsigned long.
	 * -Sets the number of columns and the number of rows to
	 *   columnsNumber and rowsNumber sent as function arguments respectively.
	 * -Sets the array_ptr and matrix_ptr to NULL
	 */
	CMatrix(unsigned long rowsNumber , unsigned long columnsNumber);

	/*
	 * -Parameters : void.
	 * -Return type: a 2-d pointer to the matrix(matrix_ptr).
	 * -A function that returns a 2-d pointer to the matrix.
	 */
	double** getMatrixPtr(void);

	/*
	 * -Parameters : void.
	 * -Return type: unsigned long (rowsNumber.)
	 * -A function that returns the number of rows in the matrix.
	 */
	//double* getArrayPtr(void);
	double** createMatrix(unsigned int nR , unsigned int nC);

	unsigned long getRowsNumber(void);

	/*
	 * -Parameters : void.
	 * -Return type: unsigned long (columnsNumber.)
	 * -A function that returns the number of columns in the matrix.
	 */
	unsigned long getColumnsNumber(void);

	/*
	 * -Parameters  : 2 pointers to the matrix class.
	 * -Return type : void.
	 * -A function that takes 2 pointers to the CMatrix class, the first one is
	 *   operand1 and the second one is operand2.
	 * -It adds operand1 and operand2 and puts the result in the calling object.
	 */
	void add(CMatrix* , CMatrix*);

	/*
	 * -Parameters  : 2 pointers to the matrix class.
	 * -Return type : void.
	 * -A function that takes 2 pointers to the CMatrix class, the first one is
	 *   operand1 and the second one is operand2.
	 * -It subtracts operand2 from operand1 and puts the result in the calling object Matrix.
	 */
	void subtract(CMatrix* , CMatrix*);

	/*
	 * -Parameters  : 2 pointers to the matrix class.
	 * -Return type : void.
	 * -A function that takes 2 pointers to the CMatrix class, the first one is
	 *   operand1 and the second one is operand2.
	 * -It multiplies operand1 and operand2,and puts the result in the calling object Matrix.
	 */
	void multiply(CMatrix* , CMatrix*);

	/*
	 * -Parameters  : 2 pointers to the matrix class.
	 * -Return type : void.
	 * -A function that takes 2 pointers to the CMatrix class, the first one is
	 *   operand1,and the second one is operand2.
	 * -It divides operand1 by operand2,and puts the result in the calling object Matrix.
	 */
	void divide(CMatrix* , CMatrix*);

	/*
	 * -Parameters  : 1 pointers to the matrix class.
	 * -Return type : void.
	 * -A function that takes 1 pointers to the CMatrix class,which is the operand.
	 * -It gets the transpose of the operand and puts it in calling object Matrix.
	 */
	void transpose(CMatrix* );

	/*
	 * -Copy operator.
	 * -Parameters  : a pointer to the matrix class
	 * -Return type : a pointer to the matrix class
	 * -A function that takes a pointer the matrix class, the operand pointer and returns
	 * 	 pointer to this.
	 * - It copies the operand matrix to the matrix of this class
	 */
	void operator=(CMatrix*);
	/*
	 * -Parameters  : 1 pointer to a matrix class.
	 * -Return type : void.
	 * -A function that takes 1 pointer to a matrix class which is the operand pointer.
	 * -it copies the operand matrix into the calling object matrix.
	 */
	void copy(CMatrix*);
	/*
	 * -Destructor Method.
	 * -takes no arguments.
	 * -It frees the dynamically allocated memory for the matrix
	 */

	void elementWiseDivide(CMatrix* operand1_ptr , CMatrix* operand2_ptr);
	void elementWiseDivide(CMatrix* operand1_ptr , double operand2 , int operation);
	~CMatrix(void);
	void CMatrix::elementWiseAddition(CMatrix* operand1_ptr , double operand2  );
	void CMatrix::elementWiseSubtraction(CMatrix* operand1_ptr , double operand2 , int operation );
	void CMatrix::elementWiseMultiplication(CMatrix* operand1_ptr , double operand2  );
	void CMatrix::elementWiseMultiplication(CMatrix* operand1_ptr , CMatrix* operand2_ptr );
	void AND ( CMatrix* , CMatrix* );
	void OR ( CMatrix* , CMatrix* );
	void factorial ( CMatrix* );
	

	void printMatrix(void);
};


#endif /* MATLIBRARY_H_ */

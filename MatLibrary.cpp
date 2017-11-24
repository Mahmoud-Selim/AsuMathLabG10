/*
 * MatLibrary.c
 *
 *  Created on: Oct 24, 2017
 *      Author: mahmoud
 */

#include "MatLibrary.h"
#include <stdio.h>
#include <iostream>
#include <iomanip>
	CMatrix::CMatrix()
	{
		rowsNumber    = 0;
		columnsNumber = 0;
		matrix_ptr    = NULL;
	}

	CMatrix::CMatrix(unsigned long rowsNumber , unsigned long columnsNumber)
	{
		this->rowsNumber    = rowsNumber;
		this->columnsNumber = columnsNumber;
		matrix_ptr = new double* [rowsNumber];
		for (unsigned int i = 0 ; i < rowsNumber ; i++)
		{
			matrix_ptr[i] = new double [columnsNumber];
		}
	}

	double** CMatrix::createMatrix(unsigned int nR , unsigned int nC)
	{
		double** newMatrix_ptr = new double* [nR];
		for (unsigned int i = 0 ; i < nR ; i++)
		{
			newMatrix_ptr[i] = new double [nC];
		}
		return newMatrix_ptr;
	}

	double** CMatrix::getMatrixPtr(void)
	{
		return matrix_ptr;
	}

	unsigned long CMatrix::getRowsNumber(void)
	{
		return rowsNumber;
	}

	unsigned long CMatrix::getColumnsNumber(void)
	{
		return columnsNumber;
	}

	void CMatrix::add(CMatrix* operand1_ptr , CMatrix* operand2_ptr)
	{
		if(operand1_ptr->rowsNumber!= operand2_ptr->rowsNumber || operand1_ptr->columnsNumber != operand2_ptr->columnsNumber )
		{
			throw("Error invalid operand dimensions");
			return;
		}
		unsigned long i , j;
        double** operand1Matrix_ptr = operand1_ptr->matrix_ptr;
        double** operand2Matrix_ptr = operand2_ptr->matrix_ptr;
        if(this-> rowsNumber==operand1_ptr->rowsNumber&&this->columnsNumber==operand1_ptr->columnsNumber)
        {
        	for (i = 0; i < rowsNumber ; i++)
        	{
                for (j = 0 ; j < columnsNumber ; j++ )
                {
                	matrix_ptr[i][j] = operand1Matrix_ptr[i][j] + operand2Matrix_ptr[i][j];
                }
        	}
        }
        else
        {
        	double**newMatrix=  createMatrix(operand1_ptr->rowsNumber,operand1_ptr->columnsNumber);
        	for (i = 0; i < operand1_ptr->rowsNumber ; i++)
            {
        		for (j = 0 ; j < operand1_ptr->columnsNumber ; j++ )
                {
        			newMatrix[i][j] = operand1Matrix_ptr[i][j] + operand2Matrix_ptr[i][j];
                }
            }
        	for (i = 0; i < rowsNumber ; i++)
        	{
        		delete[] matrix_ptr[i];
        	}
        	delete []matrix_ptr ;
        	matrix_ptr = newMatrix;
        	this->rowsNumber    = operand1_ptr->rowsNumber;
        	this->columnsNumber = operand1_ptr->columnsNumber;

        }
	}

	void CMatrix::subtract(CMatrix* operand1_ptr , CMatrix* operand2_ptr)
	{
		if(operand1_ptr->rowsNumber != operand2_ptr->rowsNumber||operand1_ptr->columnsNumber!= operand2_ptr->columnsNumber )
		{
			throw("Error invalid operand dimensions");
			return;
		}
        unsigned long i , j;
        double** operand1Matrix_ptr = operand1_ptr->matrix_ptr;
        double** operand2Matrix_ptr = operand2_ptr->matrix_ptr;
        if(this-> rowsNumber==operand1_ptr->rowsNumber&&this->columnsNumber==operand1_ptr->columnsNumber)
        {
        	for (i = 0; i < rowsNumber ; i++)
        	{
                for (j = 0 ; j < columnsNumber ; j++ )
                {
                	matrix_ptr[i][j] = operand1Matrix_ptr[i][j] - operand2Matrix_ptr[i][j];
                }
        	}
        }
        else
        {
        	double**newMatrix=  createMatrix(operand1_ptr->rowsNumber,operand1_ptr->columnsNumber);
        	for (i = 0; i < operand1_ptr->rowsNumber ; i++)
            {
        		for (j = 0 ; j < operand1_ptr->columnsNumber ; j++ )
                {
        			newMatrix[i][j] = operand1Matrix_ptr[i][j] - operand2Matrix_ptr[i][j];
                }
            }
        	for (i = 0; i < rowsNumber ; i++)
        	{
        		delete[] matrix_ptr[i];
        	}
        	delete []matrix_ptr ;
        	matrix_ptr = newMatrix;
        	this->rowsNumber    = operand1_ptr->rowsNumber;
        	this->columnsNumber = operand1_ptr->columnsNumber;

        }
	}

	void CMatrix::multiply(CMatrix* operand1_ptr , CMatrix* operand2_ptr)
	{
		if(operand1_ptr->columnsNumber != operand2_ptr->rowsNumber)
		{
			throw("Error invalid operand dimensions");
			return;
		}
		unsigned long i,j,k;
		double** operand1Matrix = (*operand1_ptr).matrix_ptr;
		double** operand2Matrix = (*operand2_ptr).matrix_ptr;
		/// to check different dimensions of the actual result compared to the expected result ///

		unsigned long operand1NoRows = operand1_ptr->rowsNumber;                    // also expected result no. rows
		unsigned long operand1NoCols =   operand1_ptr->columnsNumber;
		unsigned long operand2NoRows = operand2_ptr->rowsNumber;
		unsigned long operand2NoCols =   operand2_ptr->columnsNumber;             // also expected result no. cols

		if ( rowsNumber != operand1NoRows || columnsNumber != operand2NoCols || operand1_ptr == this || operand2_ptr == this )
        {
            double** new_matrix_ptr = createMatrix(operand1NoRows , operand2NoCols);
             for(i=0;i<operand1NoRows;i++)
            {
                for(j=0;j<operand2NoCols;j++)
                {
                    new_matrix_ptr[i][j]=0;
                    for(k=0;k<operand1NoCols;k++)
                    {
                        new_matrix_ptr[i][j]+=operand1Matrix[i][k]*operand2Matrix[k][j];
                    }
                }
            }
            // delete old
			for (i = 0; i < rowsNumber ; i++)
			{
				delete[] matrix_ptr[i];
			}
			delete [] matrix_ptr ;
            // equate old with new
            matrix_ptr = new_matrix_ptr ;
            this->rowsNumber    = operand1NoRows;
            this->columnsNumber = operand2NoCols;
        }

        else
        {
            for(i=0;i<rowsNumber;i++)
            {
                for(j=0;j<columnsNumber;j++)
                {
                    matrix_ptr[i][j]=0;
                    for(k=0;k<operand1_ptr->columnsNumber;k++)
                    {
                        matrix_ptr[i][j]+=operand1Matrix[i][k]*operand2Matrix[k][j];
                    }
                }
            }
        }
	}


	void CMatrix::divide(CMatrix* operand1_ptr , CMatrix* operand2_ptr)
	{
		if(operand1_ptr->columnsNumber != operand2_ptr->rowsNumber)
		{
			throw("Error invalid operand dimensions");
			return;
		}
           // operand1_ptr->printMatrix();
            //operand2_ptr->printMatrix();
			unsigned long l,k,r,c;
	       double temp, t;
	       short flag = 0;
			double** p1 = (*operand1_ptr).matrix_ptr;
			double** p2old = (*operand2_ptr).matrix_ptr;
	        CMatrix INV(operand2_ptr->rowsNumber,operand2_ptr->columnsNumber);
	        double ** b = INV.getMatrixPtr();
	        CMatrix p2new(operand2_ptr->rowsNumber,operand2_ptr->columnsNumber);
	        p2new.copy(operand2_ptr);
	        double ** p2 = p2new.getMatrixPtr();

	           /////constrains/////
	       if((operand2_ptr->columnsNumber!=operand2_ptr->rowsNumber) || (operand1_ptr->columnsNumber!=operand2_ptr->rowsNumber)){
	       printf("Can't divide these two Matrices -_- \n");
	       //exit(0);
	      }
	       ///////////////////Calculating Inverse (B^-1)//////////////////////////

	       for (r = 0; r<operand2_ptr->rowsNumber; r++){
	       for (c=r; c<operand2_ptr->columnsNumber; c++){
	           b[r][c]= (r==c)?1.0:0;
	       }
	       }

	   for(r=0; r<operand2_ptr->rowsNumber; r++){
	   for (c=r; c<operand2_ptr->columnsNumber; c++){

	       if( p2[r][r] == 0.0 ){        ///Swaping if element = zero
	            for(k=r+1; k<operand2_ptr->rowsNumber; ++k){
	           if( p2[k][r] != 0.0 ){
	               for(unsigned long c=0; c<operand2_ptr->rowsNumber; ++c)
	               {
	                       temp = p2[r][c];
	                   p2[r][c] = p2[k][c];
	                   p2[k][c] = temp;
	               }
	                               for(unsigned long c=0; c<operand2_ptr->rowsNumber; ++c)
	               {
	                       temp = b[r][c];
	                   b[r][c] = b[k][c];
	                   b[k][c] = temp;
	               }
	                               break;
	                           }
	                       }
	                   }
	           //////////////Elementary Row Operations//////////
	       if (p2[c][r] != 0.0){
	           t = 1.0/p2[r][r];
	           for (k = 0; k<operand2_ptr->rowsNumber; k++){
	               p2[r][k] *= t;
	               b[r][k] *= t;
	           }
	           for (l = 0; l<operand2_ptr->rowsNumber; l++){
	               if (l != r){
	                   t = -p2[l][r];
	                   for (k = 0; k<operand2_ptr->rowsNumber; k++){
	                       p2[l][k] = p2[l][k] + t*p2[r][k];
	                       b[l][k] = b[l][k] + t*b[r][k];
	                   }
	               }
	          }
	       }
	   }
	}
        //INV.printMatrix();
	   for (int i= 0 ; i < operand1_ptr->rowsNumber ; i++)
	   {
		   flag = 0;
		   for (int j = 0 ; j < operand2_ptr->rowsNumber ; j++)
		   {
			   if (p2[i][j] != 0)
			   {
				   flag = 1;
				   break;
			   }
		   }
		   if (flag == 0)
		   {
			   throw("Error,can't divide by a singular matrix ");
			   return;
		   }
	   }
	/////////////Multipling B^-1 with A ////////////
	   multiply( operand1_ptr , &INV);
}


	void CMatrix::transpose(CMatrix* operand_ptr)
	{
		unsigned long i,j;
		double** operandMatrix  = (*operand_ptr).matrix_ptr;
		//double* operandArray = operand_ptr->array_ptr;
		if (operand_ptr == this)
		{
			unsigned int temp = this->columnsNumber;
			this->columnsNumber = this->rowsNumber;
			this->rowsNumber = temp;
			double** newMatrix_ptr = createMatrix(rowsNumber , columnsNumber);
			for(i = 0 ; i < rowsNumber ; i++)
			{
				for(j = 0 ;j < columnsNumber ; j++)
				{
					newMatrix_ptr[i][j] = operandMatrix[j][i];
				}
			}
			for (i = 0; i < columnsNumber ; i++)
			{
				delete[] matrix_ptr[i];
			}
			delete[] matrix_ptr;
			matrix_ptr = createMatrix(rowsNumber , columnsNumber);
			for (i = 0 ; i < rowsNumber ; i++)
			{
				matrix_ptr[i] = newMatrix_ptr[i];
			}
			matrix_ptr = newMatrix_ptr;
			return;
		}
		else if ((operand_ptr->rowsNumber != columnsNumber) || (operand_ptr->columnsNumber != rowsNumber))
		{
			unsigned int oldRowsNumber = this->rowsNumber;
			this->columnsNumber = operand_ptr->rowsNumber;
			this->rowsNumber    = operand_ptr->columnsNumber;
			double** newMatrix_ptr = createMatrix(rowsNumber , columnsNumber);
			for(i = 0 ; i < rowsNumber ; i++)
			{
				for(j = 0 ;j < columnsNumber ; j++)
				{
					newMatrix_ptr[i][j] = operandMatrix[j][i];
				}
			}
			for (i = 0; i < oldRowsNumber; i++)
			{
				delete[] matrix_ptr[i];
			}
			delete[] matrix_ptr;
			matrix_ptr = createMatrix(rowsNumber , columnsNumber);
			for (i = 0 ; i < rowsNumber ; i++)
			{
				matrix_ptr[i] = newMatrix_ptr[i];
			}
			matrix_ptr = newMatrix_ptr;
			return;
		}
		for(i = 0 ; i < rowsNumber ; i++)
		{
			for(j = 0 ;j < columnsNumber ; j++)
			{
				matrix_ptr[i][j] = operandMatrix[j][i];
			}
		}
	}

	void CMatrix::copy( CMatrix* operand_ptr)
	{
		unsigned long i , j;
		double** operand1Matrix_ptr = operand_ptr->matrix_ptr;
		if (operand_ptr->rowsNumber != this->rowsNumber || operand_ptr->columnsNumber != this->columnsNumber)
		{
			double** newMatrixPtr = createMatrix(operand_ptr->rowsNumber , operand_ptr->columnsNumber);
			for (i = 0; i < operand_ptr->rowsNumber ; i++)
			{
				for (j = 0 ; j < operand_ptr->columnsNumber ; j++ )
				{
					newMatrixPtr[i][j] = operand1Matrix_ptr[i][j];
				}
			}
			for (i = 0 ; i < rowsNumber ; i++)
			{
				delete[] matrix_ptr[i];
			}
			delete [] matrix_ptr;
			matrix_ptr = newMatrixPtr;
			rowsNumber = operand_ptr->rowsNumber ;
			columnsNumber = operand_ptr->columnsNumber;
		}
		for (i = 0; i < rowsNumber ; i++)
		{
			for (j = 0 ; j < columnsNumber ; j++ )
			{
				matrix_ptr[i][j] = operand1Matrix_ptr[i][j];
			}
		}
	}

	void CMatrix::operator=(CMatrix* operand_ptr)
	{
		this->copy(operand_ptr);
		//return (*this); // return *this gives error.!!!
	}

	void CMatrix::elementWiseDivide(CMatrix* operand1_ptr , CMatrix* operand2_ptr)
	{
		if(operand1_ptr->rowsNumber != operand2_ptr->rowsNumber||operand1_ptr->columnsNumber!= operand2_ptr->columnsNumber )
		{
			throw("Error invalid operand dimensions");
			return;
		}
		unsigned long i , j;
		double** operand1Matrix = operand1_ptr->matrix_ptr;
		double** operand2Matrix = operand2_ptr->matrix_ptr;
		if ((operand1_ptr->rowsNumber != rowsNumber) || (operand1_ptr->columnsNumber != columnsNumber))
		{
			unsigned int oldRowsNumber = this->rowsNumber;
			this->columnsNumber = operand1_ptr->columnsNumber;
			this->rowsNumber    = operand1_ptr->rowsNumber;
			double** newMatrix_ptr = createMatrix(rowsNumber , columnsNumber);
			for(i = 0 ; i < rowsNumber ; i++)
			{
				for(j = 0 ;j < columnsNumber ; j++)
				{
					newMatrix_ptr[i][j] = operand1Matrix[i][j] / operand2Matrix[i][j] ;
				}
			}
			for (i = 0; i < oldRowsNumber ; i++)
			{
				delete[] matrix_ptr[i];
			}
			delete[] matrix_ptr;
			matrix_ptr = createMatrix(rowsNumber , columnsNumber);
			for (i = 0 ; i < rowsNumber ; i++)
			{
				matrix_ptr[i] = newMatrix_ptr[i];
			}
			matrix_ptr = newMatrix_ptr;
			return;
		}

			for(i = 0 ; i < rowsNumber ; i++)
			{
				for(j = 0 ;j < columnsNumber ; j++)
				{
					matrix_ptr[i][j] = operand1Matrix[i][j] / operand2Matrix[i][j] ;
				}
			}
	}

	void CMatrix::elementWiseDivide(CMatrix* operand1_ptr , double operand2 , int operation )
	{
		unsigned long i,j;
		double** operand1Matrix  = (*operand1_ptr).matrix_ptr;
		if ((operand1_ptr->rowsNumber != rowsNumber) || (operand1_ptr->columnsNumber != columnsNumber))
		{
			unsigned int oldRowsNumber = this->rowsNumber;
			this->columnsNumber = operand1_ptr->columnsNumber;
			this->rowsNumber    = operand1_ptr->rowsNumber;
			double** newMatrix_ptr = createMatrix(rowsNumber , columnsNumber);
			if (operation == NormalOperation)
			{
				for(i = 0 ; i < rowsNumber ; i++)
				{
					for(j = 0 ;j < columnsNumber ; j++)
					{
						newMatrix_ptr[i][j] = operand1Matrix[i][j] / operand2 ;
					}
				}
			}
			else if (operation == InvertedOperation)
			{
				for(i = 0 ; i < rowsNumber ; i++)
				{
					for(j = 0 ;j < columnsNumber ; j++)
					{
						newMatrix_ptr[i][j] = operand2 / operand1Matrix[i][j];
					}
				}
			}
			for (i = 0; i < oldRowsNumber ; i++)
			{
				delete[] matrix_ptr[i];
			}
			delete[] matrix_ptr;
			matrix_ptr = createMatrix(rowsNumber , columnsNumber);
			for (i = 0 ; i < rowsNumber ; i++)
			{
				matrix_ptr[i] = newMatrix_ptr[i];
			}
			matrix_ptr = newMatrix_ptr;
			return;
		}
		if(operation == NormalOperation)
		{
			for(i = 0 ; i < rowsNumber ; i++)
			{
				for(j = 0 ;j < columnsNumber ; j++)
				{
					matrix_ptr[i][j] = operand1Matrix[i][j] / operand2 ;
				}
			}
		}else if(operation == InvertedOperation)
		{
			for(i = 0 ; i < rowsNumber ; i++)
			{
				for(j = 0 ;j < columnsNumber ; j++)
				{
					matrix_ptr[i][j] = operand2 / operand1Matrix[i][j] ;
				}
			}
		}

	}

	CMatrix::~CMatrix(void)
	{
		if(matrix_ptr != NULL)
		{
			for (unsigned long i = 0; i < rowsNumber ; i++)
			{
				delete[] matrix_ptr[i];
			}
			delete[] matrix_ptr;
		}
	}

	void CMatrix::printMatrix(void)
	{
		unsigned long i = 0, j = 0 , k = 0;
		if (columnsNumber <= 6 )
		{
			for (i = 0 ; i < rowsNumber ; i++ )
			{
				for( j = 0 ; j < columnsNumber ; j++)
				{
					std::cout<<std::setprecision(5)<<std::setw(11)<<matrix_ptr[i][j]<<" ";
				}
				std::cout<<std::endl;
			}
		}
		else
		{
			for (i = 0 ; i < columnsNumber ; i=i+6)
			{
				std::cout<<std::endl<<"columns From column: "<<i+1<<" to: "<<i+(i+6 > columnsNumber ? columnsNumber-i:6)<<std::endl<<std::endl;
				for(j = 0 ; j < rowsNumber ; j++)
				{
					for (k = i ; k < i+6 && k < columnsNumber ; k++ )
					{
						std::cout<<std::setprecision(5)<<std::setw(11)<<matrix_ptr[j][k]<<" ";
					}
					std::cout<<std::endl;
				}
			}
		}
	}





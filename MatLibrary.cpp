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
#include <math.h>
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

	    int i,j,k,n = operand2_ptr->rowsNumber,pivotMaxIndex;
	    CMatrix INV(n,n);
	    double d;
	    double** a ;
	    a = new double* [(2*n)];
	    for(i = 0 ; i < (2*n) ; i++)
	    {
	    	a[i] = new double [(2*n)];
	    }
	    for(i=0;i<n;i++)
	        for(j=0;j<n;j++)
	            a[i][j] = operand2_ptr->matrix_ptr[i][j];


	    for(i=0;i<n;i++)
	        for(j=n;j<2*n;j++)
	            if(j==(i+n))
	                a[i][j]=1;
	            else
	            	a[i][j] = 0;
	    /********** reducing to diagonal  matrix ***********/
	    for(i=0;i<n;i++)
	    {
	    	pivotMaxIndex = i;
	    	for(j = i+1 ; j < n ; j++)
	    	{
	    		if(fabs(a[j][i]) > fabs(a[pivotMaxIndex][i]))
	    		{
	    			pivotMaxIndex = j;
	    		}
	    	}
	    	for(j = 0 ; j < 2*n ; j++)
	    	{
	    		double temp = a[pivotMaxIndex][j];
	    		a[pivotMaxIndex][j] = a[i][j];
	    		a[i][j] = temp;
	    	}
	    	/****************makin zeros obove and below pivot element*********************/
	        for(j=0;j<n*2;j++)
	        if(j!=i)
	        {
	            d=a[j][i]/a[i][i];
	            for(k=0;k<n*2;k++)
	                a[j][k]-=a[i][k]*d;
	        }
	    /************** reducing to unit matrix *************/
	    	d=a[i][i];
	        for(j=0;j<n*2;j++)
	            a[i][j]=a[i][j]/d;
	    }

	/*    for (i = 0 ; i <= 6 ;i++)
	     {
	     	for(j = 0; j <= 6 ; j++)
	     	{
	     		cout<<a[i][j]<<"	";
	     	}
	     	cout<<endl;

	     }*/


/*	    std::cout<<"your solutions: "<<std::endl;
	    for(i=0;i<n;i++)
	    {
	        for(j=n;j<n*2;j++)
	            std::cout<<a[i][j]<<"    ";
	        std::cout<<std::endl;
	    }*/
	    double** inv_matrix_ptr = INV.matrix_ptr;
	    for (i = 0 ; i < n ; i ++)
	    {
	    	for (j = n; j <n*2 ; j++)
	    	{
	    		inv_matrix_ptr[i][j-n] = a[i][j];
	    	}
	    }

	    for(i = 0 ; i < n ; i++)
	    {
	    	delete [] a[i];
	    }
	    delete [] a;


		/////////////Multipling B^-1 with A ////////////
	   multiply( operand1_ptr , &INV);
}

        void CMatrix::power(CMatrix* operand1_ptr ,double value)
    {
        unsigned int i,j;
        CMatrix powered(operand1_ptr->rowsNumber,operand1_ptr->columnsNumber);
        powered.copy(operand1_ptr);
        int valueINT = value;
    if((operand1_ptr->rowsNumber==1)&&(operand1_ptr->columnsNumber==1)&&(value-valueINT))
    {
            printf("d5l fl fn\n");
        matrix_ptr[0][0]=pow(operand1_ptr->matrix_ptr[0][0],value);
            
    }
    else if (value == 0)
        for(i=0;i<rowsNumber;i++)
            {
                for(j=0;j<columnsNumber;j++)
                {
                    
                matrix_ptr[i][j]=(i==j)?1.0:0.0;
                }
            }
    else if (value<0)
        {
            if(operand1_ptr->columnsNumber != operand1_ptr->rowsNumber)
		{
			throw("Error invalid operand dimensions");
			return;
		}

	    int i,j,k,n = operand1_ptr->rowsNumber,pivotMaxIndex;
	    CMatrix INV(n,n);
	    double d;
	    double** a ;
	    a = new double* [(2*n)];
	    for(i = 0 ; i < (2*n) ; i++)
	    {
	    	a[i] = new double [(2*n)];
	    }
	    for(i=0;i<n;i++)
	        for(j=0;j<n;j++)
	            a[i][j] = operand1_ptr->matrix_ptr[i][j];


	    for(i=0;i<n;i++)
	        for(j=n;j<2*n;j++)
	            if(j==(i+n))
	                a[i][j]=1;
	            else
	            	a[i][j] = 0;
	    /********** reducing to diagonal  matrix ***********/
	    for(i=0;i<n;i++)
	    {
	    	pivotMaxIndex = i;
	    	for(j = i+1 ; j < n ; j++)
	    	{
	    		if(fabs(a[j][i]) > fabs(a[pivotMaxIndex][i]))
	    		{
	    			pivotMaxIndex = j;
	    		}
	    	}
	    	for(j = 0 ; j < 2*n ; j++)
	    	{
	    		double temp = a[pivotMaxIndex][j];
	    		a[pivotMaxIndex][j] = a[i][j];
	    		a[i][j] = temp;
	    	}
	    	/****************makin zeros obove and below pivot element*********************/
	        for(j=0;j<n*2;j++)
	        if(j!=i)
	        {
	            d=a[j][i]/a[i][i];
	            for(k=0;k<n*2;k++)
	                a[j][k]-=a[i][k]*d;
	        }
	    /************** reducing to unit matrix *************/
	    	d=a[i][i];
	        for(j=0;j<n*2;j++)
	            a[i][j]=a[i][j]/d;
	    }


	    double** inv_matrix_ptr = INV.matrix_ptr;
	    for (i = 0 ; i < n ; i ++)
	    {
	    	for (j = n; j <n*2 ; j++)
	    	{
	    		inv_matrix_ptr[i][j-n] = a[i][j];
	    	}
	    }

	    for(i = 0 ; i < n ; i++)
	    {
	    	delete [] a[i];
	    }
	    delete [] a;
        for( i=0;i>value;i--)
                powered.multiply( &INV , &powered);
            multiply( &INV , &powered);
        }
        else if(value>1)
        {
            for( i=1;i<value-1;i++)
                powered.multiply( operand1_ptr , &powered);
            multiply( operand1_ptr , &powered);
        }

        else if (value == 1)
            for(i=0;i<rowsNumber;i++)
            {
                for(j=0;j<columnsNumber;j++)
                {
                    
                matrix_ptr[i][j]=operand1_ptr->matrix_ptr[i][j];
                }
            }
            

    }
    void CMatrix::power(double operandV,double value2)
    {
        matrix_ptr[0][0]=pow(operandV,value2);
    }
    void CMatrix::elementwisepower(CMatrix* operand1_ptr ,double value)
    {
        double** p1 = (*operand1_ptr).matrix_ptr;
        for(unsigned int i=0;i<operand1_ptr->rowsNumber;i++)
            for(unsigned int j=0;j<operand1_ptr->columnsNumber;j++)
                matrix_ptr[i][j]=pow(p1[i][j],value);

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











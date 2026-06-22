// SerialGauss.cpp
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <omp.h>

void DummyDataInitialization(double* pMatrix, double* pVector, int Size);
void RandomDataInitialization(double* pMatrix, double* pVector, int Size);
void ProcessInitialization(double* &pMatrix, double* &pVector, double* &pResult, int &Size);
void PrintMatrix(double* pMatrix, int RowCount, int ColCount);
void PrintVector(double* pVector, int Size);
void ProcessTermination(double* pMatrix, double* pVector, double* pResult);

const double eps = 0.1; ///< желаема€ точность 


// Function for the execution of Jacobi algorithm-----------------------------------------------------------------
void SerialResultCalculation(double* pMatrix, double* pVector, double* pResult, int Size)
{
	/// N - размерность матрицы,
	/// A[N][N] - матрица коэффициентов,
	/// F[N] - столбец свободных членов,
	/// X[N] - начальное приближение, ответ записываетс€ также в X[N];
	//double** A;
	//for (int i = 0; i < Size; i++)
	//	for (int j = 0; j < Size; j++)
	//		A[i][j] = pMatrix[i*Size + j];
		
	int N = Size;
	double* F = pVector;
	double* X = pResult;

//void Jacobi (int N, double** A, double* F, double* X)
//++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++
		double* TempX = new double[N];
		double norm; // норма, определ€ема€ как наибольша€ разность компонент столбца иксов соседних итераций.

		do {
			
			

			for (int i = 0; i < N; i++) 
			{
				TempX[i] = F[i];

//#pragma omp parallel for //private (i)	
				for (int g = 0; g < N; g++)
				{
					if (i != g)
						TempX[i] -= pMatrix[i*Size + g] * X[g];
				//	printf("Local thread (id = %i) (num_threads = %i)\n", 
				//		omp_get_thread_num(), omp_get_num_threads());
				
				}
				
				TempX[i] /= pMatrix[i*Size + i];
			}



			norm = fabs(X[0] - TempX[0]);
			for (int h = 0; h < N; h++) {
				if (fabs(X[h] - TempX[h]) > norm)
					norm = fabs(X[h] - TempX[h]);
				X[h] = TempX[h];
			}

			printf(".");
		} while (norm > eps);
		
		delete[] TempX;
//++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++
}





int main() {
	double* pMatrix;		// The matrix of the linear system
	double* pVector;		// The right parts of the linear system
	double* pResult;		// The result vector
	int Size;				// The sizes of the initial matrix and the vector
	double start, finish, duration;
	printf("Series Jacobi algorithm for solving linear systems\n");
	
	// Memory allocation and definition of objects' elements
	ProcessInitialization(pMatrix, pVector, pResult, Size);
	//»нициализаци€ начальных членов дл€ алгоритма якоби
	for (int i = 0; i < Size; i++)
	{
		pResult[i] = 0;
	}

	// The matrix and the vector output
	//printf("Initial Matrix \n");
	//PrintMatrix(pMatrix, Size, Size);
	//printf("Initial Vector \n");
	//PrintVector(pVector, Size);
	//printf("\n");

	// Execution of Jacobi algorithm
	start = omp_get_wtime();
	SerialResultCalculation(pMatrix, pVector, pResult, Size);//---------------------------------------------------
	finish = omp_get_wtime();;
	duration = (finish - start) ;
	
	// Printing the result vector
//	printf("\n Result Vector: \n");
//	PrintVector(pResult, Size);
	
	// Printing the execution time of Gauss method
	printf("\n");
	printf("Start: %7.10f , Finish: %7.10f ", start, finish);
	printf("\n Time of execution: %f\n", duration);
	
	// Computational process termination
	ProcessTermination(pMatrix, pVector, pResult);
	return 0;
}





//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// Function for simple initialization of the matrix
// and the vector elements
void DummyDataInitialization(double* pMatrix, double* pVector, int Size)
{
	int i, j;			// Loop variables
	for (i = 0; i < Size; i++) {
		pVector[i] = i + 1;
		for (j = 0; j < Size; j++) {
			if (j <= i)
				pMatrix[i*Size + j] = 1;
			else
				pMatrix[i*Size + j] = 0;
		}
	}
}


// Function for random initialization of the matrix
// and the vector elements
void RandomDataInitialization(double* pMatrix, double* pVector, int Size)
{
	int i, j;			// Loop variables
	srand(unsigned(clock()));
	for (i = 0; i < Size; i++) {
		pVector[i] = rand() / double(1000);
		for (j = 0; j < Size; j++) {
			if (j <= i)
				pMatrix[i*Size + j] = rand() / double(1000);
			else
				pMatrix[i*Size + j] = 0;
		}
	}
}


// Function for memory allocation and definition of the objects elements
void ProcessInitialization(double* &pMatrix, double* &pVector, double* &pResult, int &Size)
{
	// Setting the size of the matrix and the vector
	do
	{
		printf("\nEnter size of the matrix and the vector: ");
		scanf("%d", &Size);
		printf("\nChosen size = %d \n", Size);
		if (Size <= 0)
			printf("\nSize of objects must be greater than 0!\n");
	} while (Size <= 0);
	// Memory allocation
	pMatrix = new double[Size*Size];
	pVector = new double[Size];
	pResult = new double[Size];
	// Initialization of the matrix and the vector elements
//	DummyDataInitialization(pMatrix, pVector, Size);
	RandomDataInitialization(pMatrix, pVector, Size);
}


// Function for formatted matrix output
void PrintMatrix(double* pMatrix, int RowCount, int ColCount)
{
	int i, j;				// Loop variables
	for (i = 0; i < RowCount; i++) {
		for (j = 0; j < ColCount; j++)
			printf("%7.4f ", pMatrix[i*RowCount + j]);
		printf("\n");
	}
}


// Function for formatted vector output
void PrintVector(double* pVector, int Size)
{
	int i;
	for (i = 0; i < Size; i++)
		printf("%7.4f ", pVector[i]);
}


// Function for computational process termination
void ProcessTermination(double* pMatrix, double* pVector, double* pResult)
{
	delete[] pMatrix;
	delete[] pVector;
	delete[] pResult;
}
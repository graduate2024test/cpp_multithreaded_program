
#include <iostream>
#include <time.h>
#include "mpi.h"

#define MASTER 0

using namespace std;

// Число pi
#define PI 3.1415926535897932384626433832795
double foo(double x);
void simpsonIntegral(const double a, const double b, const double h, double *res);

int main(int argc, char *argv[])
{
	double end_res, res;				// значение вычисленного интеграла
	int myrank, nprocs;					// номер и количество процессов
	double a = 0.0;						// левая граница интегрирования
	double b1 = 0.4999;					// правая граница интегрирования
	double b2 = 0.5;					// правая граница интегрирования
	double b3 = 1.0;					// правая граница интегрирования
	double h = 0.0000001;				// шаг интегрирования
	//********************************************************************
	//метод Симпсона******************************************************
	//********************************************************************
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	if (nprocs != 2)
	{
		cerr << "World size must be equals 2 !" << endl;
		MPI_Abort(MPI_COMM_WORLD, 1);
	}
	if (myrank == 0)
	{
		simpsonIntegral(a, b1, h, &res);
	}
	else
	{
		simpsonIntegral(b2, b3, h, &res);
	}
	MPI_Reduce(&res, &end_res, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if (myrank == MASTER)
	{
		cout << " *** Simpson integral *** " << endl;
		cout.precision(8);
		cout << "integral value : " << end_res << endl;
	}
	MPI_Finalize();
	return 0;
	//********************************************************************
	//********************************************************************
}


void simpsonIntegral(const double a, const double b, const double h, double *res)
{
	int n = (int)((b - a) / h);	// количество точек сетки интегрирования
	double x1, x2;
	double simpson_integral = 0;
	for (int step = 0; step < (n - 1); step++) {
		x1 = a + step * h;
		x2 = a + (step + 1)*h;

		simpson_integral += ((x2 - x1) / 6.0)*(foo(x1) + 4.0*foo(0.5*(x1 + x2)) + foo(x2));
	}
	*res = simpson_integral;
}


double foo(double x)		//интегрируемая функция
{
	return(1 / sqrt(1 - x * x));
}
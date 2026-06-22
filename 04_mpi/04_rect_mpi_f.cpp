#include <iostream>
#include <cmath>
#include <time.h>
#include "mpi.h"

#define MASTER 0

using namespace std;

#define EXP 2.71828
#define PI 3.1415926535897932384626433832795
double experiment(double *res);
void rectangleIntegral(const double a1, const double b1, const double h1,
	const double a2, const double b2, const double h2,
	double *res);
double foo(double x, double y);

int main(int argc, char *argv[])
{
	double stime, ftime, time;							// время начала и конца расчета
	double end_res, res;								// значение вычисленного интеграла
	int myrank, nprocs;									// номер и количество процессов
	double a1 = 0.0;									// левая граница интегрирования
	double b1_1 = 7.999;									// правая граница интегрирования
	double b1_2 = 8;										// правая граница интегрирования
	double b1_3 = 16;										// правая граница интегрирования
	double h1 = 0.01;									// шаг интегрирования
	double a2 = 0.0;									// левая граница интегрирования
	double b2 = 16;										// правая граница интегрирования
	double h2 = 0.01;									// шаг интегрирования
	stime = clock();
	//********************************************************************
	//метод прямоугольников***********************************************
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
		rectangleIntegral(a1, b1_1, h1, a2, b2, h2, &res);
	}
	else
	{
		rectangleIntegral(b1_2, b1_3, h1, a2, b2, h2, &res);
	}
	MPI_Reduce(&res, &end_res, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if (myrank == MASTER)
	{
		cout << " *** Integral *** " << endl;
		cout.precision(8);
		cout << "integral value : " << end_res << endl;
	}
	MPI_Finalize();
	ftime = clock();
	time = (ftime - stime) / CLOCKS_PER_SEC;
	//**************************************************
	cout << "MPI Test" << endl;
	// вывод результатов эксперимента
	cout << "execution time : " << time << endl;

	return 0;
}


void rectangleIntegral(const double a1, const double b1, const double h1,
	const double a2, const double b2, const double h2,
	double *res)
{
	int i, n, j, m;
	double sum;					// локальная переменная для подсчета интеграла
	double x, y;						// координата точки сетки
	n = (int)((b1 - a1) / h1);			// количество точек сетки интегрирования
	m = (int)((b2 - a2) / h2);

	//Реализуйте цикл вычисления интеграла :
	sum = 0.0;


	for (i = 0; i < n; i++)
	{

		for (j = 0; j < m; j++)
		{
			x = a1 + i * h1 + h1 / 2.0;
			y = a2 + i * h2 + h2 / 2.0;
			sum += (foo(x, y) * h1 * h2);
		}
	}
	*res = sum;
}



double foo(double x, double y)			//интегрируемая функция
{
	return ((pow(EXP, (sin(PI*x)*cos(PI*y))) + 1) / (16.0*16.0));
}
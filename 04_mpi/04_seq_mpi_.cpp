#include <stdio.h>
#include <mpi.h>
#include <cmath>

#define PI 3.1415926535897932384626433832795
double f(double y) { return(4.0 / (1.0 + y * y)); }
double foo(double x) { return(1 / sqrt(1 - x * x)); }

int main(int argc, char* argv[])
{
	//---------------------PI----------------
	/*double w, x, sumPI, locpi, pi, t1, t2;
	int i, rank, size;
	int n = 1000;*/
	//---------------------------------------
	
	//---------------------Integral----------
	double h, xINT, sumINT, locINT, resINT, t1, t2;
	int iINT, rank, size;
	int m = 1000000;
	//double a = 0.0;
	//double b = 1.0;
	//h = 0.0000001;
	//int m = (int)((b - a) / h);
	//---------------------------------------
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Barrier(MPI_COMM_WORLD);
	t1 = MPI_Wtime();
	
	//---------------------PI----------------
	/*w = 1.0 / (double)n;
	sumPI = 0.0;
	for (i = rank + 1; i <= n; i += size)
	{
		x = w * (i - 0.5);
		sumPI = sumPI + f(x);
	}
	locpi = w * sumPI;
	MPI_Reduce(&locpi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);*/
	//---------------------------------------
	
	//---------------------Integral----------
	h = 1.0 / (double)m;
	sumINT = 0.0;
	for (iINT = rank + 1; iINT <= m; iINT += size)
	{
		//xINT = a + iINT * h;
		xINT = h * (iINT - 0.5);
		sumINT = sumINT + foo(xINT);
	}
	locINT = h * sumINT;
	MPI_Reduce(&locINT, &resINT, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	//---------------------------------------
		
	MPI_Barrier(MPI_COMM_WORLD);
	t2 = MPI_Wtime();
	
	//if (rank == 0) printf("N= %d, Nproc=%d, pi = %lf, Time=%lf \n", n, size, pi, t2 - t1);
	if (rank == 0)
	{
		printf("N= %d, Nproc=%d, integral value = %lf, Time=%lf \n", m, size, resINT, t2 - t1);
		double half_pi = (PI / 2.0);
		printf("PI/2 value : %lf", half_pi);
	}
	
	MPI_Finalize();
}
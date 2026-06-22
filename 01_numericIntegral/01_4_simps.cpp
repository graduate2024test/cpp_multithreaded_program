/*
#include <iostream>
#include <time.h>
#include <omp.h>
using namespace std;

// Число pi
#define PI 3.1415926535897932384626433832795
double foo(double x);
double experiment1(double *res);
double experiment2(double *res);
void rectangleIntegral(const double a, const double b, const double h, double *res);
void simpsonIntegral(const double a, const double b, const double h, double *res);

int main()
{
	
	int i;					// переменная цикла
	double time;			// время проведенного эксперимента
	double res;				// значение вычисленного интеграла
	double min_time;		// минимальное время работы
							// реализации алгоритма
	double max_time;		// максимальное время работы
							// реализации алгоритма
	double avg_time;		// среднее время работы
							// реализации алгоритма
	int numbExp = 10;		// количество запусков программы




	//********************************************************************
	//метод прямоугольников***********************************************
	//********************************************************************
							// первый запуск
	min_time = max_time = avg_time = experiment1(&res);
							// оставшиеся запуски
	
	int thread = 0;
	
	for (i = 0; i < numbExp - 1; i++)
	{
		time = experiment1(&res);
		avg_time += time;
		if (max_time < time) max_time = time;
		if (min_time > time) min_time = time;
		thread++;
	}
	cout << "OpenMP threads: " << thread << endl;

	
	// вывод результатов эксперимента
	cout << " *** Rectangle integral *** " << endl;
	cout << "execution time : " << avg_time / numbExp << "; " << min_time << "; " << max_time << endl;
	cout.precision(8);
	cout << "integral value : " << res << endl;
	//********************************************************************
	//********************************************************************
	



	int i2;					// переменная цикла
	double time2;			// время проведенного эксперимента
	double res2;				// значение вычисленного интеграла
	double min_time2;		// минимальное время работы
							// реализации алгоритма
	double max_time2;		// максимальное время работы
							// реализации алгоритма
	double avg_time2;		// среднее время работы
							// реализации алгоритма
	int numbExp2 = 10;		// количество запусков программы
	
	//********************************************************************
	//метод Симпсона******************************************************
	//********************************************************************
							// первый запуск
	min_time2 = max_time2 = avg_time2 = experiment2(&res2);
							// оставшиеся запуски

	int thread2 = 0;	
	
	for (i2 = 0; i2 < numbExp2 - 1; i2++)
	{
		time2 = experiment2(&res2);
		avg_time2 += time2;
		if (max_time2 < time2) max_time2 = time2;
		if (min_time2 > time2) min_time2 = time2;
		thread2++;
	}
	cout << "OpenMP threads: " << thread2 << endl;


	// вывод результатов эксперимента
	cout << " *** Simpson integral *** " << endl;
	cout << "execution time : " << avg_time2 / numbExp2 << "; " << min_time2 << "; " << max_time2 << endl;
	cout.precision(8);
	cout << "integral value : " << res2 << endl;
	//********************************************************************
	//********************************************************************
	
	return 0;
}



//**********************************************************
//**********************************************************
//**********************************************************
double experiment1(double *res)
{
	double stime, ftime;	// время начала и конца расчета
	double a = 0.0;			// левая граница интегрирования
	double b = 1.0;			// правая граница интегрирования
	double h = 0.0000001;	// шаг интегрирования
	stime = clock();
	rectangleIntegral(a, b, h, res); // вызов функции интегрирования
	ftime = clock();
	return (ftime - stime) / CLOCKS_PER_SEC;
}


double experiment2(double *res)
{
	double stime, ftime;	// время начала и конца расчета
	double a = 0.0;			// левая граница интегрирования
	double b = 1.0;			// правая граница интегрирования
	double h = 0.0000001;		// шаг интегрирования
	stime = clock();
	simpsonIntegral(a, b, h, res); // вызов функции интегрирования
	ftime = clock();
	return (ftime - stime) / CLOCKS_PER_SEC;
}


void rectangleIntegral(const double a, const double b, const double h, double *res)
{
	int i, n;
	double sum;				// локальная переменная для подсчета интеграла
	double x;				// координата точки сетки
	n = (int)((b - a) / h);	// количество точек сетки интегрирования
							//Реализуйте цикл вычисления интеграла :
	sum = 0.0;

#pragma omp parallel for private(x) reduction(+: sum)
	for (i = 0; i < n; i++)
	{
		x = a + i * h;
		sum += foo(x) * h;
	}
	*res = sum;
}


void simpsonIntegral(const double a, const double b, const double h, double *res)
{
	int n = (int)((b - a) / h);	// количество точек сетки интегрирования
	double x1, x2;
	double simpson_integral = 0;

#pragma omp parallel for private(x1, x2) reduction(+: simpson_integral)
	for (int step = 0; step < (n-1); step++) {
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
*/
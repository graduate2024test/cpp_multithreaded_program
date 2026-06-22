#include <iostream>
#include <cmath>
#include <time.h>

using namespace std;

#define EXP 2.71828
#define PI 3.1415926535897932384626433832795
double experiment(double *res);
void rectangleIntegral(const double a1, const double b1, const double h1,
	const double a2, const double b2, const double h2,
	double *res);
double foo(double x, double y);

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
	min_time = max_time = avg_time = experiment(&res);
	// оставшиеся запуски

	int thread = 0;

	for (i = 0; i < numbExp - 1; i++)
	{
		time = experiment(&res);
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

	return 0;
}



//**********************************************************
//**********************************************************
//**********************************************************
double experiment(double *res)
{
	double stime, ftime;								// время начала и конца расчета
	double a1 = 0.0;									// левая граница интегрирования
	double b1 = 16;										// правая граница интегрирования
	double h1 = 0.01;									// шаг интегрирования
	double a2 = 0.0;									// левая граница интегрирования
	double b2 = 16;										// правая граница интегрирования
	double h2 = 0.01;									// шаг интегрирования
	stime = clock();
	rectangleIntegral(a1, b1, h1, a2, b2, h2, res);		// вызов функции интегрирования
	ftime = clock();
	return (ftime - stime) / CLOCKS_PER_SEC;
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
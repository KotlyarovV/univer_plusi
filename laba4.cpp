#include "stdafx.h" 
#include <iostream> 
#include <vector> 
#include <omp.h> 
#include <conio.h> 

using namespace std;

void division(vector<int>& v, int left, int right, int &t)
{
	int x = v[left];
	int tmp = 0;
	t = left;
	for (int i = left + 1; i <= right; i++)
	{
		if (v[i] < x)
		{
			t++;
			tmp = v[t];
			v[t] = v[i];
			v[i] = tmp;
		}
	}
	tmp = v[left];
	v[left] = v[t];
	v[t] = tmp;
}

void quick_sort_parallel(vector<int>& v, int left, int right)
{

	if (left < right)
	{
		int t = 0;
		division(v, left, right, t);
		#pragma omp sections nowait 
		{
			#pragma omp section 
			quick_sort_parallel(v, left, t);
			#pragma omp section 
			quick_sort_parallel(v, t + 1, right);
		}
	}

}

void quick_sort(vector<int>& v, int left, int right)
{
	if (left < right)
	{
		int t = 0;
		division(v, left, right, t);
		quick_sort(v, left, t);
		quick_sort(v, t + 1, right);
	}
}

int main()
{

	vector<int> v = vector<int>();
	vector<int> v1 = vector<int>();

	for (int i = 0; i < 60000; i++)
	{
		int x = rand() % 500;
		v.push_back(x);
		v1.push_back(x);
	}

	int size = v.size() - 1;

	double start = omp_get_wtime();
	quick_sort(v, 0, size);
	double end = omp_get_wtime();

	double start_parallel = omp_get_wtime();
	quick_sort_parallel(v1, 0, size);
	double end_parallel = omp_get_wtime();

	cout << endl << "Parallel Time: " << end_parallel - start_parallel << "sec." << endl;
	cout << endl << "Time: " << end - start << "sec." << endl;

	//for (auto i : v) 
	//cout « i « " "; 
	_getch();
	return 0;
}

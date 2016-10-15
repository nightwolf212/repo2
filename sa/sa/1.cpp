	#include <stdio.h>
	#include <locale.h>
	#include <stdlib.h>
	#include <iostream>
	#include <time.h>
	#include <windows.h>

	using namespace std;
	void main() {
	int n, i, j, k, temp, min, answer = 1;
	int *a, *b, c, *a_buf1, *a_buf2;
	LARGE_INTEGER start, finish, freq;//для представ 64 битного целого числа
	double d;
	setlocale(LC_ALL, "rus");
	cout << "Введите размер массива: ";
	cin>>n;
	a = new int[n];
	b = new int[n];
	a_buf1 = new int[n];
	a_buf2 = new int[n];
	srand(time(NULL));
	for (i = 0; i<n; i++) {
	a[i] = rand() % 100000 - 5000;}
	cout<<endl;
	for (i = 0; i<n; i++)
	a_buf1[i] = a[i];a_buf2[i] = a[i];
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	for (i = 0; i <= n - 1; i++) {
	k = 0;
	for (j = 0; j <= n - 1; j++)
	if (a[i] > a[j]) k++;
	b[k + 1] = a[i];
	}
	QueryPerformanceCounter(&finish);
	d = (finish.QuadPart - start.QuadPart) / (double)freq.QuadPart; //расчёт времени
	cout << endl;
	printf("Сортировка подсчетом, затрачено %f секунд.\n", d);
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	for (j = 0; j < n; j++)
	for (i = 0; i < n - 1; i++) 
	if (a_buf1[i + 1] < a_buf1[i]) {
	temp = a_buf1[i + 1];
	a_buf1[i + 1] = a_buf1[i];
	a_buf1[i] = temp;
	}	
	QueryPerformanceCounter(&finish);
	d = (finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
	cout << endl;
	printf("Сортировка обменом, затрачено %f секунд.\n", d); 
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	temp = 0;
	for (i = 0; i< n - 1; i++) {
	min = i;
	for (int j = i + 1; j<n; j++) {
	if (a_buf2[j] < a_buf2[min]) {
	min = j;
	}
	}
	temp = a_buf2[i];
	a_buf2[i] = a_buf2[min];
	a_buf2[min] = temp;
	}
	QueryPerformanceCounter(&finish); 
	d = (finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
	cout << endl;
	printf("Сортировка извлечением, затрачено %f секунд.\n", d); 

	temp = 0;
	for (i = 0; i<n; i++)//обнуление массива b
	b[i] = 0;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	b[0] = a[0];//заносим в массив b первый элемент массива a
	int h = 1;
	for (i = 1; i<n; i++)
	{for (j = 0; j<h; j++)
	{if (a[i]<b[j])
	{for (int k = h; k>j; k--)
	{temp = b[k];//обмен элементов
	b[k] = b[k - 1];
	b[k + 1] = temp;}
	b[j] = a[i];
	break;}
	if (j + 1 == h)
	b[j + 1] = a[i];}
	h++;}
	QueryPerformanceCounter(&finish);
	d = (finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
	cout << endl;
	printf("Сортировка включением, затрачено %f секунд.\n", d);
	system("pause");
	delete[] a;} //отчистка памяти

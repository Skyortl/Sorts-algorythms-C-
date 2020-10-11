#include <iostream>
#include <algorithm>
#include <time.h>
#include <random>
#include <cmath>
#include <vector>

using namespace std;

int shellSort(int arr[], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i += 1)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];

            arr[j] = temp;
        }
    }
    return 0;
}

void bucketSort(int arr[], int n) {
    int max, separ;
    const int buc = 1000;
    vector<int> b[buc];
    max = arr[0];

    for (int i = 0; i < n; i++)
        if (max < arr[i])
            max = arr[i];


    separ = ceil(float(max + 1) / buc);
    for (int i = 0; i < n; i++) {
        int index = floor(arr[i] / separ);
        b[index].push_back(arr[i]);
    }
    for (int i = 0; i < buc; i++) {
        sort(b[i].begin(), b[i].end());
    }
    int index = 0;
    for (int i = 0; i < buc; i++) {
        for (int j = 0; j < b[i].size(); j++)
        {
            arr[index++] = b[i][j];
        }
    }
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quickSort(int arr[], int l, int r)
{
    if (l >= r)
        return;
    int pivot = arr[r];
    int cnt = l;
    for (int i = l; i <= r; i++)
    {
        if (arr[i] <= pivot)
        {
            swap(&arr[cnt], &arr[i]);
            cnt++;
        }
    }
    quickSort(arr, l, cnt - 2);
    quickSort(arr, cnt, r);
}

int main()
{
    srand(time(NULL));
    double startTime;
    double finishTime;
    int* arr0;
    int* arr1;
    const int minNum = 0;
    const int maxNum = 100000;
    default_random_engine generator;
    uniform_int_distribution<int> distribution(minNum, maxNum);
    int min = 50000;
    int max = 1000000;
    int step = 50000;
    for (min; min <= max; min += step)
    {
        arr0 = new int[min];
        arr1 = new int[min];
        for (int i = 0; i < min; i++)
        {
            arr0[i] = arr1[i] = distribution(generator);
        }
        startTime = clock();
        shellSort(arr0, min);
        finishTime = clock();
        cout << min << " Elements in shell sort is " << (finishTime - startTime) / CLOCKS_PER_SEC << " sec" << endl;
        for (int i = 0; i < min; i++)
        {
            arr0[i] = arr1[i];
        }
        startTime = clock();
        quickSort(arr0, 0, min - 1);
        finishTime = clock();
        cout << min << " Elements in quick sort is " << (finishTime - startTime) / CLOCKS_PER_SEC << " sec" << endl;;
        for (int i = 0; i < min; i++)
        {
            arr0[i] = arr1[i];
        }
        startTime = clock();
        bucketSort(arr0, min);
        finishTime = clock();
        cout << min << " Elements in bucket sort is " << (finishTime - startTime) / CLOCKS_PER_SEC << " sec" << endl;
        delete[] arr0;
        delete[] arr1;
    }
    return 0;
}

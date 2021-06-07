#include <iostream>

void BubbleSort(int arr[], int size);
void SelectionSort(int arr[], int size);
void PrintArray(int arr[], int size);
void InsertionSort(int arr[], int size);


int main()
{



}

void BubbleSort(int arr[], int size)
{
	for (int i = 0; i < size ; ++i)
	{
		for (int j = 0; j < size - 1; ++j)

		{
			if (arr[j] > arr[j + i])
			{
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}
void SelectionSort(int arr[], int size)
{
	int smallest;

	for (int i = 0; i < size - 1; ++i)
	{
		smallest = i;
		for (int j = 0; j < size; j++)
		{
			if (arr[j] < arr[smallest])
			{
				smallest = j;
				swap(arr[smallest], arr[i]);
			}
		}
	}
}
void InsertionSort(int arr[], int size)
{
	int currElement;
	int j;
	for (int i = 0; i < size; ++i)
	{
		currElement = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > currElement)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = currElement;
	}


}

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}
void PrintArray(int arr[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		std::cout << arr[i] << " ";
	}
}
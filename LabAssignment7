#include <stdio.h>

void bubbleSort(int arr[], int n, int swap[])
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                // swap elements
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                //swap count for the current index (increse)
                swap[j]++;
            }
        }
    }
}

int main()
{
    int arr[] = {97, 16, 45, 63, 13, 22, 7, 58, 72};
    int n = sizeof(arr) / sizeof(arr[0]);
    int swap[n];

    // swap counts to 0
    for (int i = 0; i < n; i++)
    {
        swap[i] = 0;
    }

    bubbleSort(arr, n, swap);

    // print # of swaps for each index
    for (int i = 1; i < n; i++)
    {
        printf("Index %d: %d swap(s)\n", i, swap[i]);
    }

    return 0;
}

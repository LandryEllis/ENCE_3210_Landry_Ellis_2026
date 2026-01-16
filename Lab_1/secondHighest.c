#include <stdio.h>

#define N 50

int arr[N];
int secondMax;

int main()
{
    // fill the array with unique values 0..49
    for (int i = 0; i < N; i++)
    {
        arr[i] = i;
    }

    // find max and second max
    int max1 = arr[0];
    int max2 = arr[0];

    for (int i = 0; i < N; i++)
    {
        if (arr[i] > max1)
        {
            max2 = max1;
            max1 = arr[i];
        }
        else if (arr[i] < max1 && arr[i] > max2)
        {
            max2 = arr[i];
        }
    }

    secondMax = max2;

    printf("Max = %d\n", max1);
    printf("Second Max = %d\n", secondMax);

    return 0;
}

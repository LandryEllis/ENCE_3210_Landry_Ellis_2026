#include <stdio.h>

// computes 2 * (n^2)
int twiceSquare(int n)
{
    int s;                // holds the square

    s = n * n;            // square the number
    s = 2 * s;            // multiply by 2

    return s;             // return final result
}

int main()
{
    int values[512];      // array to store results from 0..511
    int i;                // loop counter
    int n;                // user input
    int r;                // result for the user input

    // get an integer from the user
    printf("Enter an integer: ");
    scanf("%d", &n);

    // compute result for the entered number
    r = twiceSquare(n);
    printf("Result = %d\n", r);

    // fill the array using the function for numbers 0 to 511
    for (i = 0; i < 512; i++)
    {
        values[i] = twiceSquare(i);   // store each computed value
    }

    // display stored values (formatted output)
    printf("\nStored values (0 to 511):\n");
    for (i = 0; i < 512; i++)
    {
        printf("%d ", values[i]);     // print the value

        // print a new line every 8 values
        if ((i + 1) % 8 == 0)
            printf("\n");
    }

    printf("\n");
    return 0;                         // end program
}

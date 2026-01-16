#include <stdio.h>
#include <math.h>

int main()
{
    double cosValues[361];
    int deg;
    double rad;

    // fill array with cos values from 0 to 360 degrees
    for (deg = 0; deg <= 360; deg++)
    {
        rad = deg * (M_PI / 180.0);   // degrees to radians
        cosValues[deg] = cos(rad);    // store cosine
    }

    // print in one long line
    printf("Cosine values from 0 to 360 degrees:\n");
    for (deg = 0; deg <= 360; deg++)
    {
        printf("%.6f ", cosValues[deg]);
    }

    printf("\n");
    return 0;
}

/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

#define ARRAY_SIZE 10

int myArray[ARRAY_SIZE] = {0};

int main()
{
    for(int i =0; i<ARRAY_SIZE; i++)
    {
        int a;
        scanf("%d", &a);
        myArray[i] = a;
        
    }
    float b;
    for(int i =0; i<ARRAY_SIZE; i++)
    {
        b+= myArray[i];
        
    }
    b/=ARRAY_SIZE;
    printf("%d", &b);
    

    return 0;
}

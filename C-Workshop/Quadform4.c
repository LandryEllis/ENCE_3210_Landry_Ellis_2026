
#include <stdio.h>
#include <math.h>

//global variables
struct s_Quadratic
{
    float x1;
    float x2;
};




struct s_Quadratic quadratic (int a, int b, int c)
{
    
    struct s_Quadratic x;
    
    float w = (b*b - 4 * a * c);
    
    if(w >= 0)
        {x.x1 = (-b + sqrt(w)) / (2 * a);
        x.x2 = (-b - sqrt(w)) / (2 * a);
        return x;}
    else
    {
        x.x1 = 0;
        x.x2 = 0;
        printf("complex roots\n");
    }
    return x;
}

int main()
{
    struct s_Quadratic y;
    int n;
    scanf("%d", &n);
    y = quadratic (1, -5, n);
    printf("result: %.2f, %.2f\n", y.x1, y.x2);
    return 0;
}



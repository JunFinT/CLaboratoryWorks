#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define q 0.0000001

double fun(double x){
    return pow(x,3);
}
double find_int(double a, double b, double eps, double (* f)(double x)){
    double sum = 1000000000 ;
    double sut = -10000000000 ;
    while (fabs(sum* eps-sut* eps/2) > q){
        sum = 0;
        sut = 0;
        for (double i = a; i < b; i+=eps){
            sum += f(i) + f(i+eps);
        }
        for (double i = a; i < b; i+=eps/2){
            sut += f(i) + f(i+eps/2);
        }
        eps=eps/2;
    }
    return sum * eps;
}


int main()
{
    printf("%f", find_int(0, 1, 0.0000001, fun));

    return 0;
}

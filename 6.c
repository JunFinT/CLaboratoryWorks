/*
6. Написать программу для вычисления определенных интегралов от функций методом трапеций с использованием указателей на функции.
 В программе должна присутствовать функция double find_int(double a, double b, double eps, double (* f) (double x)),
 где  a и b - левый и правый пределы интегрирования, eps - требуемая точность, f - указатель на подинтегральную функцию.
 Функция find_int должна возвращать приближенное значение интеграла.
*/

#include <stdio.h>
#include <math.h>


double f(double x){
    return x*x*x;
}




double I(double a, double b, double (* f)(double x), double dl){
    double s = 0;
    for (double i = a; i < b; i += dl){
        s += f(i) + f(i+dl);
    }

    return s * dl/2;
}

double find_int(double a, double b, double (* f)(double x), double eps){
    double dl = b - a;

    while (fabs(I(a, b, f, dl) - I(a, b, f, dl / 2)) > eps) {
        dl /= 2;
    }

    return I(a, b, f, dl);
}

int main()
{
    printf("%f", find_int(0, 1, f, 0.0001));

    return 0;
}


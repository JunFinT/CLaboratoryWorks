/*
1.  Написать программу для приближенного вычисления значений функции exp(x) с некоторой заданной точностью eps с помощью разложения по формуле Тэйлора.
    Программа должна выводить таблицу, состоящую из следующих столбиков:
    1) Количество слагаемых в сумме в формуле Тэйлора
    2) Приближенное значение функции exp(x), вычисленное по формуле Тэйлора с количеством слагаемых, равным значению из первого столбика
    3) Модуль разности приближенного значения exp(x) из второго столбика и значения exp(x), вычисленного с помощью функции exp(x) из стандартной библиотеки языка C.
*/

#include<stdio.h>
#include<math.h>

int main() {
    int x;
    double eps;
    printf("Enter x: ");
    scanf("%d", &x);
    printf("Enter eps: ");
    scanf("%lf", &eps);

    double last_summad = 1.;
    double sum = last_summad;
    int i = 1;
    double ex = exp(x);

    while (fabs(ex - sum) >= eps) {
        last_summad *= x / (double) i;
        sum += last_summad;
        i += 1;
    }

    printf("%d\t%lf\t%lf\n", i, sum, fabs(ex - sum));
    return 0;
}

/*
    2. Написать программу для решения уравнений f(x) - c = 0 методами деления отрезка пополам и хорд.
    В программе должны быть использованы следующие функции
        int solve(int method, double a, double b, double eps, double param);
        double solve_bis(double a, double b, double eps, double param);
        double solve_chord(double a, double b, double eps, double param);
    Здесь method - метод для решения уравнения, method == 1 используется метод бисекции, method == 2 используется метод хорд,
    method == 3 используются последовательно оба метода; a и b - левая и правая границы отрезка, на котором ищется корень;
    eps - требуемая точность; param - значение параметра c в функции f(x) - c = 0.
    Функция solve проверяет условие (f(a) - c)*(f(b) - c) < 0, и если оно ложно, возвращает в функцию main значение 1.
    Если данное условие истинно, то функция solve вызывает в зависимости от значения параметра method соответствующие функции
    solve_bis, solve_chord либо обе,печатает приближенные значения корня, возвращенные solve_bis и solve_chord и возвращает в main значение 0.
*/

#include <stdio.h>
#include <math.h>

double f(double x) {
    return cos(x);
}

void solve_bis(double a, double b, double eps, double param);

void solve_chord(double a, double b, double eps, double param);

int solve(int method, double a, double b, double eps, double param) {
    if (fabs(a - b) < eps) {
        printf("%lf\n", a);
        return 0;
    } else if ((f(a) - param) * (f(b) - param) <= 0) {
        if (method == 1) {
            solve_bis(a, b, eps, param);
            return 0;
        } else if (method == 2) {
            solve_chord(a, b, eps, param);
            return 0;
        } else {
            printf("Корень, найденный методом бисекции: ");
            solve_bis(a, b, eps, param);
            printf("Корень, найденный методом хорд: ");
            solve_chord(a, b, eps, param);
            return 0;
        }
    } else {
        return 1;
    }
}

void solve_bis(double a, double b, double eps, double param) {
    double c = (a + b) / 2.;
    if ((f(a) - param) * (f(c) - param) <= 0) {
        solve(1, a, c, eps, param);
    } else {
        solve(1, c, b, eps, param);
    }
}

void solve_chord(double a, double b, double eps, double param) {
    double fa = f(a), fb = f(b);
    double c = (a - b) * (param - fa) / (fa - fb) + a;
    if (fabs(c - a) < eps) {
        solve(2, a, c, eps, param);
    } else {
        solve(2, c, b, eps, param);
    }
}


int main() {
    if (1 == solve(3, 0, 1.7, 0.000001, 0.5)) {
        printf("На этом участке нет корней");
    }
    return 0;
}
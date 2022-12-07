/*
    3. Написать программу для поиска седловой точки в двумерном массиве.
    Программа должна также искать минимальный и максимальный элементы в данном массиве. Содержательная часть программы,
    реализующая алгоритм поиска седловой точки, должна быть оформлена в виде отдельной функции, которая принимает в качестве аргументов указатель на начало массива,
    количество строк и столбцов в массиве, указатель на переменную, в которую будет записано значение элемента, который есть седловая точка, указатели на переменные,
    в которые будут записаны значения минимального и максимального элементов массива. Функция должна возвращать 0, если седловая точка найдена, и 1,
    если в массиве нет седловой точки.

    Для создания массива, в котором будет седловая точка, можно использовать значения функции x*x - y*y,
    вычисленные на равномерной сетке в плоскости xy. Для создания массива, в котором не будет седловой точки,
    можно использовать псевдослучайные числа.
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define n 10

void initialize_array(double array[n][n]);

void random_initialize_array(double array[n][n], double min_random, double max_random);

int find_saddle_point(double array[n][n], double *saddle_point, int *saddle_point_x, int *saddle_point_y, double *mx, double *mn, int *flag);

int main() {
    double array[n][n], saddle_point, saddle_point_r, mn = 10e10, mx = -10e10, mn_r = 10e10, mx_r = -10e10;
    int  saddle_point_x, saddle_point_y, saddle_point_r_x, saddle_point_r_y;
    int flag = 1, flag_r = 1;

    printf("--------------  Function x*x - y*y  --------------\n");
    initialize_array(array);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%lf\t", array[i][j]);
        }
        printf("\n");
    }
    find_saddle_point(array, &saddle_point, &saddle_point_x, &saddle_point_y, &mx, &mn, &flag);
    if (!flag) {
        printf("saddle_point = array[%d][%d] = %lf\nmax = %lf\nmin = %lf\n\n\n", saddle_point_x, saddle_point_y, saddle_point, mx, mn);

    } else {
        printf("saddle_point - not found\nmax = %lf\nmin = %lf\n\n\n", mx, mn);
    }


    printf("--------------  Function random  --------------\n");
    random_initialize_array(array, -10, 10);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%lf\t", array[i][j]);
        }
        printf("\n");
    }
    find_saddle_point(array, &saddle_point_r, &saddle_point_r_x, &saddle_point_r_y, &mx_r, &mn_r, &flag_r);
    if (!flag_r) {
        printf("saddle_point = array[%d][%d] = %lf\nmax = %lf\nmin = %lf\n\n\n", saddle_point_r_x, saddle_point_r_y, saddle_point_r, mx_r, mn_r);

    } else {
        printf("saddle_point - not found\nmax = %lf\nmin = %lf\n\n\n", mx_r, mn_r);
    }
    return 0;
}


void random_initialize_array(double array[n][n], double min_random, double max_random) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            array[i][j] = (double) rand() / (double) RAND_MAX * (max_random - min_random) + min_random;
        }
    }
}


void initialize_array(double array[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            array[i][j] = (double) (j + i);
        }
    }
}


int find_saddle_point(double array[n][n], double *saddle_point, int *saddle_point_x, int *saddle_point_y, double *mx, double *mn, int *flag) {
    int mx_cols[n];  // mx_cols[i] - это индекс строки,в которой содержится максимальный элемент этого столбца
    int mn_rows[n];  // mn_rows[i] - это индекс столбца,в котором содержится минимальный элемент этой строки
    for (int i = 0; i < n; i++) {
        mx_cols[i] = -1;
        mn_rows[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (array[i][j] > *mx) {
                *mx = array[i][j];
            }
            if (array[i][j] < *mn) {
                *mn = array[i][j];
            }
            if (array[i][j] > array[mx_cols[j]][j]) {
                mx_cols[j] = i;
            }
            if (array[i][j] < array[i][mn_rows[i]]) {
                mn_rows[i] = j;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (mn_rows[mx_cols[i]] == i && mx_cols[i] != -1) {
            *saddle_point = array[i][mx_cols[i]];
            *saddle_point_x = i;
            *saddle_point_y = mx_cols[i];
            *flag = 0;
        }
    }
    return 0;
}
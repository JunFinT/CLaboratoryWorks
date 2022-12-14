/*
5. Написать программу для разбиения исходного файла на фрагменты заданной длины или на заданное количество фрагментов одинаковой длины (за исключением последнего файла, в котором будет содержаться остаток исходного файла). При запуске программа должна получать из командной строки следующие параметры:
1. Имя исходного файла
2. -s 1024, здесь значение 1024 приведено для примера, оно может быть произвольным и задает размер в байтах одного фрагмента, на которые нужно разбить исходный файл.
3. -n 100 , здесь значение 100 приведено для примера, оно может быть произвольным и задает количество фрагментов одинаковой длины, на которые нужно разбить исходный файл.
4. -b base, здесь base имя "основы" для имен файлов с фрагментами, то есть эти файлы будут иметь имена
base_1.txt, base_2.txt и т. д.
Программа должна проверять корректность данных, введенных пользователем в командной строке, выводить сообщение об ошибке и завершать работу, если данные некорректны.
Параметры -s и -n являются взаимоисключающими, допускается наличие в командной строке только одного из них.
Примеры запуска программы:
split file_ini.txt -s 2048 -b name
Файл file_ini.txt должен быть разбит на части длиной 2048 байтов, которые будут называться name_1.txt, name_2.txt и т. д.
split myfile.dat -n 200 -b base
Файл myfile.dat должен быть разбит на 200 равных частей, которые будут называться base_1.txt, base_2.txt и т. д.
Для успешной работы программы под операционными системами семейства MS WINDOWS, необходимо открывать файлы для чтения и записи в "двоичном режиме", т. е. использовать в качестве второго аргумента функции fopen "rb" или "wb".
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void err(char *str){
    fprintf(stderr, str);
    exit(1);
}

int isstringdigit(char *str){
    int fl = 1;
    for(int i = 0; i < strlen(str); i++){
        if(!isdigit(str[i])){
            fl = 0;
            break;
        }
    }
    return fl;
}

int main(int argc, char *argv[]){
    FILE *source;
    FILE *destination;

    int c;
    int count = 0;


    if(argc != 6)
        err("Wrong number of arguments!\n");

    if((source=fopen(argv[1], "rb")) == NULL)
        err("Can't open source file!\n");
    int fl = 0;
    if(strcmp(argv[2],"-s") == 0){
        fl = 1;
    }else if(strcmp(argv[2],"-n") != 0)
        err("Wrong argument! Use -s or -n\n");

    while((c=fgetc(source)) != EOF) {
        count++;
    }
    fclose(source);
    int length = count;
    count = 0;

    if(!(isstringdigit(argv[3])) || strstr(argv[3], "."))
        err("Wrong argument! -s or -n should be an integer");

    int n = atoi(argv[3]);

    if(strcmp(argv[4], "-b") != 0)
        err("Wrong argument! Use -b");

    char *filename = (char*) malloc(sizeof(char) * (strlen(argv[5])));
    strcpy(filename, argv[5]);
    int filesize;
    if (fl){
        filesize = n;
    }else{
        filesize = length / n;
    }

    char *numtxt = (char*) malloc(1 * sizeof(char));

    source=fopen(argv[1], "rb");
    destination = fopen(argv[1], "rb");
    while((c=fgetc(source)) != EOF) {
        if(count % filesize == 0){
            fclose(destination);
            sprintf(numtxt, "_%d.txt", count / filesize + 1);
            strcpy(&(*(filename + strlen(argv[5]))), numtxt);
            destination = fopen(filename, "wb");
        }
        count++;
        fputc(c, destination);
    }
    fclose(source);

    return 0;
}



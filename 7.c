/*
7. Написать программу для создания и использования "базы данных" об успеваемости студентов. Данные об одном студенте должны храниться в структуре следующего вида:
 struct stud
{
   char *first_name, *last_name;
   int year, month, day;
   double av_grade;
   struct stud *next;
};
Здесь first_name и last_name - указатели на имя и фамилию студента; year, month, day - год, месяц и день рождения студента,
 av_grade - текущий средний балл студента, next - указатель на структуру, хранящую информацию о следующем студенте.
Программа должна предоставлять пользователю следующие возможности:
1. Считывать исходную базу данных из файла, имя файла должно запрашиваться у пользователя,
2. Записывать текущую базу данных в файл, имя файла должно запрашиваться у пользователя,
3. Выводить текущее содержимое базы данных на экран,
4. Добавлять запись в базу данных как вводя данные с клавиатуры, так и считывая данные из файла, имя файла должно запрашиваться у пользователя,
5. Удалять произвольные записи из базы данных,
6. Искать студентов в базе данных по фамилии.
Все записи базы данных должны быть объединены в связный список.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Stud
{
    char first_name[100], last_name[100];
    int day, month, year;
    double av_grade;
    struct Stud *next;
} Stud;

// Вспомогательные функции

int exists(const char *filename){
    FILE *file;
    if ((file = fopen(filename, "rb")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

void creator(struct Stud **head, char *first_name, char *last_name, int day, int month, int year, double average_grade){
    Stud *student = (Stud*)malloc(sizeof(Stud));

    strcpy(student->first_name, first_name);
    strcpy(student->last_name, last_name);
    student->day = day;
    student->month = month;
    student->year = year;
    student->av_grade = average_grade;
    student->next = NULL;

    if(*head == NULL){
        *head = student;
    } else {
        Stud *head_student = *head;
        while (head_student->next != NULL) {
            head_student = head_student->next;
        }
        head_student->next = student;
    }
}

// Основные функции

void save(struct Stud *student, char *filename){
    char *filename_full = (char*) malloc((strlen(filename) + strlen(".cdb") + 1) * sizeof(char));
    strcpy(filename_full, filename);
    strcat(filename_full, ".cdb");

    if(exists(filename_full)){
        printf("This file is already exists\n");
        return;
    }

    FILE *file = fopen(filename_full, "wb");

    while(1){
        if(student == NULL)
            break;
        fprintf(file, "-------------------------\n");
        fprintf(file, "%s\n", student->first_name);
        fprintf(file, "%s\n", student->last_name);
        fprintf(file, "%d\n", student->year);
        fprintf(file, "%d\n", student->month);
        fprintf(file, "%d\n", student->day);
        fprintf(file, "%f\n", student->av_grade);
        student = student->next;
    }
    fclose(file);

}  // enter the name of the database

void load(Stud **student, char filename[100]){
    strcat(filename, ".cdb");

    if(!exists(filename)){
        printf("There are no file with this name\n");
        return;
    }

    FILE *file = fopen(filename, "rb");
    char first_name[100], last_name[100], temp[100];
    int day, month, year;
    double average_graduate;
    fgets(temp, 100, file);
    while(1){
        fscanf(file, "%s", first_name);
        fscanf(file, "%s", last_name);
        fgets(temp, 100, file);
        fgets(temp, 100, file);
        day = atoi(temp);
        fgets(temp, 100, file);
        month = atoi(temp);
        fgets(temp, 100, file);
        year = atoi(temp);
        fgets(temp, 100, file);
        average_graduate = atof(temp);
        creator(student, first_name, last_name, day, month, year, average_graduate);
        if(fgets(temp, 100, file) == NULL){
            break;
        }
    }
    fclose(file);
    printf("\nFile loaded successfully.\n");
}  // enter the name of the database

void add(Stud **head){
    char fn[100];
    char sn[100];
    int d, m, y;
    double r;
    printf(" Enter first name: ");
    scanf("%s", fn);
    printf("Enter last name: ");
    scanf("%s", sn);
    printf("Enter date of birth (in the DD.MM.YYYY format): ");
    scanf("%d.%d.%d", &d, &m, &y);
    printf("Enter average grade: ");
    scanf("%lf", &r);

    creator(head, fn, sn, d, m, y, r);
}

void print(Stud *student){
    if(student == NULL){
        printf("This database is empty\n");
        return;
    }
    int c = 0;
    while(student != NULL){
        c++;
        printf("Student №%d:\nName: %s; last_name: %s;\nBirth date: %d.%d.%d;\nAverage grade: %f\n---------------\n", c, student->first_name, student->last_name, student->day, student->month, student->year, student->av_grade);
        student = student->next;
    }
}

void search(Stud *student, char *last_name){
    int c = 0, fl = 1;
    while(student != NULL){
        c++;
        if(strcmp(student->last_name, last_name) == 0){
            printf("Student №%d:\nName: %s; last_name: %s;\nBirth date: %d.%d.%d;\nAverage grade: %f\n", c, student->first_name, student->last_name, student->day, student->month, student->year, student->av_grade);
            fl = 0;
        }
        student = student->next;
    }
    if(fl)
        printf("There are no students with this last_name\n");
}  // enter the last_name of the student



void delete(Stud *student, char *last_name){
    Stud *last = student;
    search(student, last_name);

    while(strcmp(student->last_name, last_name) != 0){
        last = student;
        student = student->next;
    }
    last->next = student->next;
    free(student);
}





int main(void){
    struct Stud *student = NULL;
    char input[100];

    while(1){

        gets(input);


        if(strcmp(input, "") == 0){
            continue;
        }
        char *command = strtok(input, " ");

        if(strcmp(command, "load") == 0){

            char *name = strtok(NULL, " ");
            load(&student, name);

        }else if(strcmp(command, "save") == 0){
            char *filename = strtok(NULL, " ");

            save(student, filename);

        }else if(strcmp(command, "print") == 0){

            print(student);

        }else if(strcmp(command, "add") == 0){

            add(&student);

        }else if(strcmp(command, "delete") == 0){

            char *last_name = strtok(NULL, " ");
            delete(student, last_name);

        }else if(strcmp(command, "search") == 0){

            char *last_name = strtok(NULL, " ");
            search(student, last_name);

        }else

            printf("!Nope!\n");
    }
}


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
    char first_name[50], last_name[50];
    int day, month, year;
    double av_grade;
    struct Stud *next;
} Stud;

struct command
{
    char first[100];
    char second[100];
};


void getArguments(struct command *com){
    char str[50];
    gets(str);
    char *first = strtok(str, " ");
    if(!first){
        return;
    }
    char *second = strtok(NULL, " ");
    strcpy(com->first, "");
    strcpy(com->first, first);
    strcpy(com->second,"");
    if(second){
        strcpy(com->second, second);
    }
};

int exists(const char *firstname){
    FILE *file;
    if ((file = fopen(firstname, "rb")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

void creator(struct Stud **head, char *first_name, char *surname, int day, int month, int year, double average_grade){
    Stud *st = (Stud*)malloc(sizeof(Stud));
    strcpy(st->first_name, first_name);
    strcpy(st->last_name, surname);
    st->day = day;
    st->month = month;
    st->year = year;
    st->av_grade = average_grade;
    st->next = NULL;
    if(*head == NULL){
        *head = st;
        return;
    }
    Stud *h = *head;
    while(h->next != NULL){
        h = h->next;
    }
    h->next = st;
}

int pop(Stud **head) {
    if (*head == NULL)
        return 0;
    Stud* prev = NULL;
    prev = (*head);
    (*head) = (*head)->next;
    free(prev);
    return 1;
}

void save(struct Stud *student, char *filename){
    if(student == NULL){
        printf("\nError! The database you're trying to save is empty!\n\n");
        return;
    }
    char *filen = (char*) malloc((strlen(filename) + strlen(".cdb") + 1) * sizeof(char));
    strcpy(filen, filename);
    strcat(filen, ".cdb");
    if(exists(filen)){
        printf("\nCancelled.\n\n");
        return;
    }
    FILE *f = fopen(filen, "wb");
    while(69){
        if(student == NULL)
            break;
        fprintf(f, "----\n");
        fprintf(f, "%s\n", student->first_name);
        fprintf(f, "%s\n", student->last_name);
        fprintf(f, "%d\n", student->year);
        fprintf(f, "%d\n", student->month);
        fprintf(f, "%d\n", student->day);
        fprintf(f, "%f\n", student->av_grade);
        student = student->next;
    }
    fclose(f);
    printf("\nSaved successfully to %s\n\n", filen);
}  // enter the name of the database

void load(Stud **student, char name[50]){
    strcat(name, ".cdb");
    if(!exists(name)){
        printf("\nThe file you're trying to open does not exist!\n\n");
        return;
    }
    while(pop(student)){}
    FILE *file = fopen(name, "rb");
    char first_name[50], surname[50], temp[50];
    int day, month, year;
    double average_graduate;
    fgets(temp, 50, file);
    while(1){
        fscanf(file, "%s", first_name);
        fscanf(file, "%s", surname);
        fgets(temp, 50, file);
        fgets(temp, 50, file);
        day = atoi(temp);
        fgets(temp, 50, file);
        month = atoi(temp);
        fgets(temp, 50, file);
        year = atoi(temp);
        fgets(temp, 50, file);
        average_graduate = atof(temp);
        creator(student, first_name, surname, day, month, year, average_graduate);
        if(fgets(temp, 50, file) == NULL){
            break;
        }
    }
    fclose(file);
    printf("\nFile loaded successfully.\n\n");
}  // enter the name of the database

void add(Stud **head){
    char fn[50];
    char sn[50];
    int d, m, y;
    double r;
    printf("\nPlease enter all information about the student\nFirst name: ");
    scanf("%s", fn);
    printf("Last name: ");
    scanf("%s", sn);
    printf("Date of birth (in the DD.MM.YYYY format): ");
    scanf("%d.%d.%d", &d, &m, &y);
    printf("Average grade: ");
    scanf("%lf", &r);

    creator(head, fn, sn, d, m, y, r);
    printf("\nStudent saved successfully.\n\n");
}

void printDb(Stud *student){
    if(student == NULL){
        printf("\nThe database is empty!\n\n");
        return;
    }
    int c = 0;
    while(student != NULL){
        c++;
        printf("\nStudent #%d:\nName: %s; Surname: %s;\nBirth date: %d.%d.%d;\nAverage grade: %f\n\n",
               c, student->first_name, student->last_name, student->day, student->month, student->year, student->av_grade);
        student = student->next;
    }
}

void search(Stud *student, char *surname){
    int c = 0, fl = 1;
    while(student != NULL){
        c++;
        if(strcmp(student->last_name, surname) == 0){
            printf("Student №%d:\nName: %s; Surname: %s;\nBirth date: %d.%d.%d;\nAverage grade: %f\n\n",
                   c, student->first_name, student->last_name, student->day, student->month, student->year, student->av_grade);
            fl = 0;
        }
        student = student->next;
    }
    if(fl)
        printf("There are students no with this surname\n");
}

int counter(Stud *student, char *surname){
    int c = 0;
    while(student != NULL){
        if(strcmp(student->last_name, surname) == 0)
            c++;
        student = student->next;
    }
    return c;
}

void delete(Stud *st, char *sn){
    int c = counter(st, sn);
    int choice;
    if(c == 0){
        printf("\nNo students found with this surname.\n\n");
        return;
    }
    Stud *prev = st;
    if(c == 1){
        search(st, sn);

        while(strcmp(st->last_name, sn) != 0){
            prev = st;
            st = st->next;
        }
        prev->next = st->next;
        free(st);
        printf("\nStudent deleted.\n\n");
    }else{
        printf("\nIt appears there are several students with this surname.\nPlease pick one of them by their number:\n");
        search(st, sn);
        scanf("%d", &choice);
    }
    for(int i=0; i<choice - 1; i++){
        printf("%s\n", st->last_name);
        prev = st;
        st = st->next;
    }
    prev->next = st->next;
    free(st);
    printf("\nStudent deleted.\n\n");
}





int main(void){
    struct Stud *st = NULL;

    struct command str;
    while(1){
        strcpy(str.first, "");
        strcpy(str.second, "");
        getArguments(&str);
        if(strcmp(str.first, "") == 0){
            continue;
        }else if(strcmp(str.first, "load") == 0 && strcmp(str.second, "") != 0){
            load(&st, str.second);
        }else if(strcmp(str.first, "save") == 0 && strcmp(str.second, "") != 0){
            save(st, str.second);
        }else if(strcmp(str.first, "print") == 0 && strcmp(str.second, "") == 0){
            printDb(st);
        }else if(strcmp(str.first, "add") == 0 && strcmp(str.second, "") == 0){
            add(&st);
        }else if(strcmp(str.first, "delete") == 0 && strcmp(str.second, "") != 0){
            delete(st, str.second);
        }else if(strcmp(str.first, "search") == 0 && strcmp(str.second, "") != 0){
            search(st, str.second);
        }else
            printf("\nUnknown command or incorrect number of arguments!\n\n");
    }
}


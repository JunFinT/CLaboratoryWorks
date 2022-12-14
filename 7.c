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
    char first[50];
    char second[50];
};

int exists(const char *fname);
void getarg(struct command *com);
void getstring(char *str);
void err(char *str);
void save_db(Stud *st, char *filename);
void load_db(Stud **st, char name[50]);
void print_db(Stud *st);
void add_to_db_helper(Stud **head, char *n, char *sn, int d, int m, int y, double r);
void add_to_db(Stud **head);
void delete_from_db(Stud *st, char *sn);
void search_through_db(Stud *st, char *sn);
int how_many(Stud *st, char *sn);
int verify(char *st);

int main(void){
    printf("Student database\n\nUse commands:\nload (db_name)\nsave (db_name)\n");
    printf("print\nadd\ndelete (student_surname)\nsearch (student_surname)");
    printf("\n(warning: all input values must be under 50 symbols!)\n\n");
    struct Stud *st = NULL;

    struct command str;
    while(1){
        strcpy(str.first, "");
        strcpy(str.second, "");
        getarg(&str);
        if(strcmp(str.first, "") == 0){
            continue;
        }else if(strcmp(str.first, "load") == 0 && strcmp(str.second, "") != 0){
            load_db(&st, str.second);
        }else if(strcmp(str.first, "save") == 0 && strcmp(str.second, "") != 0){
            save_db(st, str.second);
        }else if(strcmp(str.first, "print") == 0 && strcmp(str.second, "") == 0){
            print_db(st);
        }else if(strcmp(str.first, "add") == 0 && strcmp(str.second, "") == 0){
            add_to_db(&st);
        }else if(strcmp(str.first, "delete") == 0 && strcmp(str.second, "") != 0){
            delete_from_db(st, str.second);
        }else if(strcmp(str.first, "search") == 0 && strcmp(str.second, "") != 0){
            search_through_db(st, str.second);
        }else
            printf("\nUnknown command or incorrect number of arguments!\n\n");
    }
    return 0;
}

void getarg(struct command *com){
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
    return;
};


void save_db(struct Stud *st, char *filename){
    if(st == NULL){
        printf("\nError! The database you're trying to save is empty!\n\n");
        return;
    }
    char *filen = (char*) malloc((strlen(filename) + strlen(".cdb") + 1) * sizeof(char));
    strcpy(filen, filename);
    strcat(filen, ".cdb");
    if(exists(filen)){
        if(!verify("\nThis action will rewrite an existing file!\nAre you sure you want to save?")){
            printf("\nCancelled.\n\n");
            return;
        }
    }
    FILE *f = fopen(filen, "wb");
    while(69){
        if(st == NULL)
            break;
        fprintf(f, "----\n");
        fprintf(f, "%s\n", st->first_name);
        fprintf(f, "%s\n", st->last_name);
        fprintf(f, "%d\n", st->year);
        fprintf(f, "%d\n", st->month);
        fprintf(f, "%d\n", st->day);
        fprintf(f, "%f\n", st->av_grade);
        st = st->next;
    }
    fclose(f);
    printf("\nSaved successfully to %s\n\n", filen);
    return;
}

void add_to_db_helper(struct Stud **head, char *fn, char *sn, int d, int m, int y, double r){
    Stud *st = (Stud*)malloc(sizeof(Stud));
    strcpy(st->first_name, fn);
    strcpy(st->last_name, sn);
    st->day = d;
    st->month = m;
    st->year = y;
    st->av_grade = r;
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

void add_to_db(Stud **head){
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

    add_to_db_helper(head, fn, sn, d, m, y, r);
    printf("\nStudent saved successfully.\n\n");
    return;
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

void load_db(Stud **st, char name[50]){
    strcat(name, ".cdb");
    if(!exists(name)){
        printf("\nThe file you're trying to open does not exist!\n\n");
        return;
    }
    if(!verify("\nThis action will erase all the unsaved data!\nAre you sure you want to load?")){
        printf("\nCancelled.\n\n");
        return;
    }
    while(pop(st)){
        continue;
    }
    FILE *f = fopen(name, "rb");
    char fn[50], sn[50], temp[50];
    int d, m, y;
    double gr;
    fgets(temp, 50, f);
    while(1){
        fscanf(f, "%s", fn);
        fscanf(f, "%s", sn);
        fgets(temp, 50, f);
        fgets(temp, 50, f);
        d = atoi(temp);
        fgets(temp, 50, f);
        m = atoi(temp);
        fgets(temp, 50, f);
        y = atoi(temp);
        fgets(temp, 50, f);
        gr = atof(temp);
        add_to_db_helper(st, fn, sn, d, m, y, gr);
        if(fgets(temp, 50, f) == NULL){
            break;
        }
    }
    fclose(f);
    printf("\nFile loaded successfully.\n\n");
    return;
}

int exists(const char *fname){
    FILE *file;
    if ((file = fopen(fname, "rb")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

void print_db(Stud *st){
    if(st == NULL){
        printf("\nThe database is empty!\n\n");
        return;
    }
    int c = 0;
    while(st != NULL){
        c++;
        printf("\nStudent #%d:\nName: %s; Surname: %s;\nBirth date: %d.%d.%d;\nAverage grade: %f\n\n",
               c, st->first_name, st->last_name, st->day, st->month, st->year, st->av_grade);
        st = st->next;
    }
    return;
}

void search_through_db(Stud *st, char *sn){
    printf("\nSearching...\n");
    int c = 0, fl = 1;
    while(st != NULL){
        c++;
        if(strcmp(st->last_name, sn) == 0){
            printf("\nStudent #%d:\nName: %s; Surname: %s;\nBirth date: %d.%d.%d;\nAverage grade: %f\n\n",
                   c, st->first_name, st->last_name, st->day, st->month, st->year, st->av_grade);
            fl = 0;
        }
        st = st->next;
    }
    if(fl)
        printf("\nNo students found with this surname.\n\n");
    return;
}

int how_many(Stud *st, char *sn){
    int c = 0;
    while(st != NULL){
        if(strcmp(st->last_name, sn) == 0)
            c++;
        st = st->next;
    }
    return c;
}

void delete_from_db(Stud *st, char *sn){
    int c = how_many(st, sn);
    int choice;
    if(c == 0){
        printf("\nNo students found with this surname.\n\n");
        return;
    }
    Stud *prev = st;
    if(c == 1){
        search_through_db(st, sn);
        if(!verify("\nAre you sure you want to delete this student?")){
            printf("\nCancelled.\n\n");
            return;
        }
        while(strcmp(st->last_name, sn) != 0){
            prev = st;
            st = st->next;
        }
        prev->next = st->next;
        free(st);
        printf("\nStudent deleted.\n\n");
    }else{
        printf("\nIt appears there are several students with this surname.\nPlease pick one of them by their number:\n");
        search_through_db(st, sn);
        scanf("%d", &choice);
        if(!verify("\nAre you sure you want to delete this student?")){
            printf("Cancelled.\n\n");
            return;
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
    return;
}

int verify(char *st){
    printf("%s [y]/[n]\n", st);
    char ans;
    while(1){
        scanf("%s", &ans);
        if(ans == 'n')
            return 0;
        else if(ans == 'y')
            return 1;
        else
            printf("[y]/[n]\n");
    }
}
 
/*
 4. Написать функции, имитирующие работу функций strlen, strcpy и strstr из стандартной библиотеки языка С:
int my_strlen(char *str);
void my_strcpy(char *source, char *target);
int my_strstr(chat *haystack, char *needle);
Функция strstr возвращает смещение относительно начала haystack, начиная с которого встречается needle или -1, если needle в haystack не встерчается.
*/



#include<stdio.h>
#include<string.h>


int my_strlen(char *str){
    int len = 0;

    while(*str++ != '\0')
        len++;
    return len;
}


void my_strcpy(char *source, char *target){
    int c = 0;
    while(*(source + c) != '\0'){
        *(target + c) = *(source + c);
        c++;
    }
    *(target + c) = '\0';
}


int my_strstr(char *haystack, char *needle){
    for(int i = 0; i < strlen(haystack) - strlen(needle)+1; i++){
        int fl = 1;
        for(int j = 0; j < strlen(needle); j++){
            if(haystack[i + j] != needle[j]){
                fl = 0;
                break;
            }
        }
        if(fl)
            return i;
    }
    return -1;
}


int main()
{
    char st[] = "lemur";
    printf("Length of the sting \"%s\" - %d\n", st, my_strlen(st));
    char st2[] = "54321";
    printf("Before copy: %s\n", st2);
    my_strcpy(st, st2);
    printf("After copy: %s\n\n", st2);
    char haystack[] = "I want to get 'Отл8' on the exam", needle[] = "exam";
    printf("The string to look in: \"%s\"\nThe substring to look for: \"%s\"\n", haystack, needle);
    printf("The substring has been found at index %d", my_strstr(haystack, needle));
}





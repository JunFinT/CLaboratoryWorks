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
    char *l = str;

    while(*l != '\0') {
        len++;
        l++;
    }
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
    char str[] = "lemur";
    printf("len(\"%s\") = %d\n", str, my_strlen(str));
    char old_str[] = "ne lemur";
    printf("old_str = %s\n", old_str);
    my_strcpy(str, old_str);
    printf("str was copied into old_str\n");
    printf("old_str = %s\n\n", old_str);

    char haystack[] = "I want to get 'Отл8' on the exam", needle[] = "exam";
    printf("Index of the substring \"%s\" in the string \"%s\" - It's %d", needle, haystack, my_strstr(haystack, needle));
}





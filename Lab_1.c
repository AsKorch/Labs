#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lab_1.h"

static int proverka(int index, int slovoindex[], int l) {
    for (int i = 0; i < l; i++) {
        if (slovoindex[i] == index) return 1;
    }
    return 0;
}

void highlight_variable_declarations(char s[]) {
    static int kom = 0, text = 0;
    int i = 0, j = 0, ji = 0;
    int indexs[15];
    int len = (int)strlen(s);  // Явное приведение к int
    
    // Поиск всех типов: float, double, long double
    char *ptr_float = strstr(s, "float ");
    char *ptr_double = strstr(s, "double ");
    char *ptr_long_double = strstr(s, "long double ");
    
    // Обработка float
    if (ptr_float) {
        j = (int)(ptr_float - s) + 6;
        while (s[j] != ';' && s[j] != ' ' && j < len && ji < 15) {
            indexs[ji] = j;
            j++;
            ji++;
        }
    }
    
    // Обработка double
    if (ptr_double) {
        j = (int)(ptr_double - s) + 7;
        while (s[j] != ';' && s[j] != ' ' && j < len && ji < 15) {
            indexs[ji] = j;
            j++;
            ji++;
        }
    }
    
    // Обработка long double
    if (ptr_long_double) {
        j = (int)(ptr_long_double - s) + 12;
        while (s[j] != ';' && s[j] != ' ' && j < len && ji < 15) {
            indexs[ji] = j;
            j++;
            ji++;
        }
    }

    while (i < len) {
        if (kom == 0 && s[i] == '/' && i + 1 < len) {
            printf("%c", s[i]);
            i++;
            if (s[i] == '/') kom = 1;
            else if (s[i] == '*') kom = 2;
        }
        
        if (kom == 2 && s[i] == '*' && i + 1 < len && s[i + 1] == '/') {
            printf("%c", s[i]);
            i++;
            kom = 0;
        }

        if (kom == 0) {
            if (text == 0 && s[i] == '\'') text = 1;
            else if (text == 0 && s[i] == '\"') text = 2;
            else if ((text == 1 && s[i] == '\'') || (text == 2 && s[i] == '\"')) text = 0;
            else if (text == 0) {
                if (proverka(i, indexs, ji)) {
                    printf("\033[92m\033[100m%c\033[0m", s[i]); // Цветной вывод
                    i++;
                    continue;
                }
            }
        }
        
        printf("%c", s[i]);
        i++;
    }
    
    if (kom == 1) kom = 0;
}

int process_c_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка: не могу открыть файл %s\n", filename);
        return 1;
    }
    
    char line[1024];  // Используем фиксированный буфер вместо getline
    
    while (fgets(line, sizeof(line), file)) {
        highlight_variable_declarations(line);
    }
    
    fclose(file);
    return 0;
}
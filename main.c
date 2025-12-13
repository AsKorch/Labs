#include <stdio.h>
#include <stdlib.h>
#include "Lab_1.h"
#include "Lab_2.h"
#include "Lab_3.h"
#include "Lab_4.h"
#include "Lab_5.h"

int main(int argc, char *argv[]) {
    int choice;
    
    // Если передан аргумент командной строки - сразу запустить Lab_1
    if (argc == 2) {
        process_c_file(argv[1]);
        return 0;
    }
    
    // Главное меню
    printf("\n=== ВЫБОР ЛАБОРАТОРНОЙ РАБОТЫ ===\n");
    printf("1. Lab_1 - Подсветка переменных в C-коде\n");
    printf("2. Lab_2 - Программа сортировки массивов\n");
    printf("3. Lab_3 - Работа со связными списками\n");
    printf("4. Lab_4 - Работа с бинарными деревьями\n");
    printf("5. Lab_5 - Поиск кратчайшего пути в графе\n");
    printf("0. Выход\n");
    printf("> ");
    
    if (scanf("%d", &choice) != 1) {
        printf("Ошибка ввода!\n");
        return 1;
    }
    
    switch (choice) {
        case 0:
            printf("Выход из программы.\n");
            return 0;
            
        case 1: {
            char filename[256];
            printf("\n=== LAB_1: ПОДСВЕТКА ПЕРЕМЕННЫХ ===\n");
            printf("Введите имя файла .c: ");
            scanf("%s", filename);
            process_c_file(filename);
            break;
        }
            
        case 2:
            run_lab2();
            break;
            
        case 3:
            run_lab3();
            break;
            
        case 4:
            run_lab4();
            break;
            
        case 5:
            run_lab5();
            break;
            
        default:
            printf("Неверный выбор! Выберите 0-5.\n");
            return 1;
    }
    
    return 0;
}
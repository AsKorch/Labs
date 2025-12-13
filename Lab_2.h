#ifndef LAB_2_H
#define LAB_2_H

#include <stdbool.h>

// Сортировка выбором
void selection_sort(int arr[], int n);

// Heapsort
void heapsort(int arr[], int n);

// Проверка отсортированности
bool is_sorted(int arr[], int n);

// Вывод массива
void print_array(int arr[], int n);

// Чтение из файла
bool read_from_file(const char* filename, int arr[], int n);

// Заполнение массива
void fill_array(int arr[], int n, int method);

// Главная функция Lab_2
int run_lab2(void);

#endif /* LAB_2_H */
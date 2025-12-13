#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "Lab_2.h"

// Сортировка выбором
void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) min_idx = j;
        }
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

// Просеивание для Heapsort
static void heapify(int arr[], int n, int i) {
    int largest = i, left = 2 * i + 1, right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

// Heapsort
void heapsort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

// Проверка отсортированности
bool is_sorted(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        if (arr[i] > arr[i + 1]) return false;
    return true;
}

// Вывод массива
void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

// Чтение из файла
bool read_from_file(const char* filename, int arr[], int n) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка открытия файла %s\n", filename);
        return false;
    }
    
    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%d", &arr[i]) != 1) {
            printf("Ошибка чтения элемента %d\n", i + 1);
            fclose(file);
            return false;
        }
    }
    
    fclose(file);
    return true;
}

// Заполнение массива
void fill_array(int arr[], int n, int method) {
    if (method == 1) { // Ввод с клавиатуры
        printf("Введите %d элементов: ", n);
        for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    } 
    else if (method == 2) { // Случайные числа
        srand((unsigned)time(NULL));
        for (int i = 0; i < n; i++) arr[i] = rand() % 100;
    }
    else if (method == 3) { // Из файла
        char filename[100];
        printf("Введите имя файла: ");
        scanf("%s", filename);
        if (!read_from_file(filename, arr, n)) exit(1);
    }
}

// Главная функция Lab_2
int run_lab2(void) {
    int n, sort_method, fill_method;
    
    printf("\n=== LAB_2: ПРОГРАММА СОРТИРОВКИ ===\n");
    printf("Размер массива: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Неверный размер массива!\n");
        return 1;
    }
    
    int* arr = malloc(n * sizeof(int));
    if (!arr) {
        printf("Ошибка выделения памяти\n");
        return 1;
    }
    
    printf("Способ заполнения:\n");
    printf("1 - С клавиатуры\n");
    printf("2 - Случайные числа\n");
    printf("3 - Из файла\n");
    printf("Выбор: ");
    scanf("%d", &fill_method);
    
    fill_array(arr, n, fill_method);
    
    printf("\nИсходный массив:\n");
    print_array(arr, n);
    
    printf("\nМетод сортировки:\n");
    printf("1 - Сортировка выбором\n");
    printf("2 - Heapsort (пирамидальная)\n");
    printf("Выбор: ");
    scanf("%d", &sort_method);
    
    clock_t start = clock();
    
    if (sort_method == 1) {
        selection_sort(arr, n);
        printf("\nОтсортировано выбором:\n");
    } 
    else if (sort_method == 2) {
        heapsort(arr, n);
        printf("\nОтсортировано Heapsort:\n");
    } 
    else {
        printf("Неверный выбор!\n");
        free(arr);
        return 1;
    }
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    print_array(arr, n);
    printf("\nПроверка сортировки: %s\n", is_sorted(arr, n) ? "✓ Успешно" : "✗ Ошибка");
    printf("Время выполнения: %.6f секунд\n", time_spent);
    printf("Размер массива: %d элементов\n", n);
    
    free(arr);
    return 0;
}
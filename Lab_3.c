#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Lab_3.h"

// Функция создания нового элемента
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Функция вывода списка
void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) {
            printf(" -> ");
        }
        temp = temp->next;
    }
    printf(" -> NULL\n");
}

// Функция поиска элемента по значению
struct Node* findNode(struct Node* head, int value) {
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->data == value) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// Функция добавления ПОСЛЕ элемента q
void insertAfter(struct Node* q, int x) {
    if (q == NULL) {
        printf("Ошибка: указатель q равен NULL\n");
        return;
    }
    
    printf("Добавляем %d ПОСЛЕ элемента %d\n", x, q->data);
    
    // Создаем новый элемент
    struct Node* newNode = createNode(x);
    
    // Вставляем после q
    newNode->next = q->next;
    q->next = newNode;
}

// Функция добавления ДО элемента q
int insertBefore(struct Node** head, struct Node* q, int x) {
    if (q == NULL) {
        printf("Ошибка: указатель q равен NULL\n");
        return 0;
    }
    
    printf("Добавляем %d ДО элемента %d\n", x, q->data);
    
    // Создаем новый элемент
    struct Node* newNode = createNode(x);
    
    // Если q - первый элемент списка
    if (*head == q) {
        newNode->next = *head;
        *head = newNode;
        return 1;
    }
    
    // Ищем предыдущий элемент
    struct Node* current = *head;
    while (current != NULL && current->next != q) {
        current = current->next;
    }
    
    // Если элемент q не найден в списке
    if (current == NULL) {
        printf("Ошибка: элемент q не найден в списке\n");
        free(newNode);
        return 0;
    }
    
    // Вставляем перед q
    newNode->next = q;
    current->next = newNode;
    return 1;
}

// Функция создания списка со случайными значениями от 1 до 100
struct Node* createRandomList(int length) {
    if (length <= 0) {
        return NULL;
    }
    
    struct Node* head = NULL;
    struct Node* tail = NULL;
    
    srand(time(NULL)); // Инициализация генератора случайных чисел
    
    for (int i = 0; i < length; i++) {
        int value = rand() % 100 + 1; // Случайное число от 1 до 100
        
        struct Node* newNode = createNode(value);
        
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    
    return head;
}

// Функция полного удаления списка
void deleteList(struct Node** head) {
    if (*head == NULL) {
        printf("Список уже пуст!\n");
        return;
    }
    
    struct Node* current = *head;
    struct Node* next;
    int count = 0;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
        count++;
    }
    
    *head = NULL;
    printf("Список полностью удален. Освобождено %d элементов.\n", count);
}

// Функция освобождения памяти (вспомогательная)
void freeList(struct Node* head) {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Главная функция Lab_3
int run_lab3(void) {
    int length;
    int choice;
    int value, targetValue;
    struct Node* head = NULL;
    struct Node* targetNode = NULL;
    
    printf("\n=== LAB_3: РАБОТА СО СПИСКАМИ ===\n");
    
    // Запрос длины списка
    printf("Введите длину списка: ");
    scanf("%d", &length);
    
    if (length <= 0) {
        printf("Длина списка должна быть положительным числом!\n");
        return 1;
    }
    
    // Создание списка со случайными значениями от 1 до 100
    head = createRandomList(length);
    
    printf("\nСгенерированный список (%d элементов): ", length);
    printList(head);
    
    // Главное меню
    while (1) {
        printf("\n=== МЕНЮ LAB_3 ===\n");
        printf("1. Добавить элемент ПОСЛЕ указанного значения\n");
        printf("2. Добавить элемент ДО указанного значения\n");
        printf("3. Показать список\n");
        printf("4. Полностью удалить список\n");
        printf("5. Создать новый случайный список\n");
        printf("6. Выйти в главное меню\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                if (head == NULL) {
                    printf("Список пуст! Сначала создайте список.\n");
                    break;
                }
                printf("Введите значение, ПОСЛЕ которого нужно добавить элемент: ");
                scanf("%d", &targetValue);
                
                targetNode = findNode(head, targetValue);
                if (targetNode == NULL) {
                    printf("Элемент со значением %d не найден в списке!\n", targetValue);
                } else {
                    printf("Введите значение нового элемента: ");
                    scanf("%d", &value);
                    
                    insertAfter(targetNode, value);
                    printf("Обновленный список: ");
                    printList(head);
                }
                break;
                
            case 2:
                if (head == NULL) {
                    printf("Список пуст! Сначала создайте список.\n");
                    break;
                }
                printf("Введите значение, ДО которого нужно добавить элемент: ");
                scanf("%d", &targetValue);
                
                targetNode = findNode(head, targetValue);
                if (targetNode == NULL) {
                    printf("Элемент со значением %d не найден в списке!\n", targetValue);
                } else {
                    printf("Введите значение нового элемента: ");
                    scanf("%d", &value);
                    
                    if (insertBefore(&head, targetNode, value)) {
                        printf("Обновленный список: ");
                        printList(head);
                    }
                }
                break;
                
            case 3:
                if (head == NULL) {
                    printf("Список пуст!\n");
                } else {
                    printf("Текущий список: ");
                    printList(head);
                }
                break;
                
            case 4:
                deleteList(&head);
                break;
                
            case 5:
                // Удаляем старый список если он существует
                if (head != NULL) {
                    freeList(head);
                }
                
                printf("Введите длину нового списка: ");
                scanf("%d", &length);
                
                if (length <= 0) {
                    printf("Длина списка должна быть положительным числом!\n");
                    head = NULL;
                    break;
                }
                
                head = createRandomList(length);
                printf("Новый сгенерированный список (%d элементов): ", length);
                printList(head);
                break;
                
            case 6:
                printf("Выход в главное меню...\n");
                if (head != NULL) {
                    freeList(head);
                }
                return 0;
                
            default:
                printf("Неверный выбор! Попробуйте снова.\n");
        }
    }
    
    return 0;
}
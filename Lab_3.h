#ifndef LAB_3_H
#define LAB_3_H

// Структура элемента списка
struct Node {
    int data;
    struct Node* next;
};

// Функции работы со списком
struct Node* createNode(int data);
void printList(struct Node* head);
struct Node* findNode(struct Node* head, int value);
void insertAfter(struct Node* q, int x);
int insertBefore(struct Node** head, struct Node* q, int x);
struct Node* createRandomList(int length);
void deleteList(struct Node** head);
void freeList(struct Node* head);
int run_lab3(void);

#endif /* LAB_3_H */
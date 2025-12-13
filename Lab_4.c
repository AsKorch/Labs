#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Lab_4.h"

// Структура для красивого вывода дерева
struct Trunk {
    struct Trunk* prev;
    char* str;
};

// Вспомогательные функции для вывода дерева
static void showTrunks(struct Trunk* p) {
    if (p == NULL) return;
    showTrunks(p->prev);
    printf("%s", p->str);
}

static void printTreeHelper(struct TreeNode* root, struct Trunk* prev, int isLeft) {
    if (root == NULL) return;

    // Создаем новую ветвь
    struct Trunk* trunk = (struct Trunk*)malloc(sizeof(struct Trunk));
    trunk->prev = prev;
    trunk->str = "    ";

    // Сначала правое поддерево
    printTreeHelper(root->right, trunk, 1);

    // Рисуем соединения
    if (!prev) {
        trunk->str = "---";
    }
    else if (isLeft) {
        trunk->str = ".---";
        prev->str = "   |";
    }
    else {
        trunk->str = "`---";
        prev->str = "    ";
    }

    // Печатаем узел
    showTrunks(trunk);
    printf(" %d\n", root->key);

    if (prev) prev->str = "   |";
    trunk->str = "   |";

    // Затем левое поддерево
    printTreeHelper(root->left, trunk, 0);
    free(trunk);
}

// Создать новый узел дерева
struct TreeNode* createTreeNode(int key) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Вставить элемент в дерево
struct TreeNode* insertTreeNode(struct TreeNode* root, int key) {
    if (root == NULL) {
        return createTreeNode(key);
    }
    
    if (key < root->key) {
        root->left = insertTreeNode(root->left, key);
    }
    else if (key > root->key) {
        root->right = insertTreeNode(root->right, key);
    }
    
    return root;
}

// Найти минимальный элемент в дереве
int findTreeMinValue(struct TreeNode* root) {
    if (root == NULL) return -1;
    
    // В двоичном дереве поиска минимальный элемент - самый левый
    while (root->left != NULL) {
        root = root->left;
    }
    return root->key;
}

// Найти высоту поддерева
int getTreeHeight(struct TreeNode* root) {
    if (root == NULL) return 0;
    
    int leftHeight = getTreeHeight(root->left);
    int rightHeight = getTreeHeight(root->right);
    
    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    } else {
        return rightHeight + 1;
    }
}

// Посчитать всех потомков
int countTreeDescendants(struct TreeNode* root) {
    if (root == NULL) return 0;
    
    int leftCount = countTreeDescendants(root->left);
    int rightCount = countTreeDescendants(root->right);
    
    return leftCount + rightCount + 1;
}

// Найти особые вершины
int countTreeSpecialNodes(struct TreeNode* root) {
    if (root == NULL) return 0;
    
    // Вычисляем высоты
    int leftHeight = getTreeHeight(root->left);
    int rightHeight = getTreeHeight(root->right);
    
    // Считаем потомков
    int leftDescendants = countTreeDescendants(root->left);
    int rightDescendants = countTreeDescendants(root->right);
    
    // Проверяем условие
    if (leftHeight == rightHeight || leftDescendants == rightDescendants) {
        printf("Вершина %d: ", root->key);
        
        if (leftHeight == rightHeight) {
            printf("высоты равны (%d) ", leftHeight);
        }
        if (leftDescendants == rightDescendants) {
            printf("потомки равны (%d)", leftDescendants);
        }
        printf("\n");
        
        return 1;
    }
    
    // Проверяем левое и правое поддеревья
    int leftCount = countTreeSpecialNodes(root->left);
    int rightCount = countTreeSpecialNodes(root->right);
    
    return leftCount + rightCount;
}

// Удалить дерево из памяти
void deleteTree(struct TreeNode** root) {
    if (*root == NULL) return;
    
    // Сначала удаляем детей
    deleteTree(&(*root)->left);
    deleteTree(&(*root)->right);
    
    // Затем удаляем сам узел
    free(*root);
    *root = NULL;
}

// Напечатать дерево (публичная функция)
void printTree(struct TreeNode* root) {
    printTreeHelper(root, NULL, 0);
}

// Записать случайные числа в файл и посчитать сумму
int generateNumbersToFile() {
    FILE* file = fopen("numbers.txt", "w");
    if (file == NULL) {
        printf("Ошибка создания файла!\n");
        return 0;
    }
    
    srand(time(NULL));
    int sum = 0;
    
    printf("Генерируем 10 случайных чисел: ");
    for (int i = 0; i < 10; i++) {
        int num = rand() % 100 + 1;
        printf("%d ", num);
        fprintf(file, "%d ", num);
        sum += num;
    }
    printf("\n");
    
    fclose(file);
    printf("Числа записаны в файл 'numbers.txt'\n");
    return sum;
}

// Прочитать числа из файла и построить дерево
struct TreeNode* readNumbersAndBuildTree() {
    FILE* file = fopen("numbers.txt", "r");
    if (file == NULL) {
        printf("Ошибка открытия файла!\n");
        return NULL;
    }
    
    struct TreeNode* root = NULL;
    int num;
    
    printf("Читаем числа из файла: ");
    while (fscanf(file, "%d", &num) == 1) {
        printf("%d ", num);
        root = insertTreeNode(root, num);
    }
    printf("\n");
    
    fclose(file);
    return root;
}

// Достроить граф методом параллельных пар чисел
struct TreeNode* extendGraphFromMin(struct TreeNode* originalRoot, int targetSum) {
    if (originalRoot == NULL) return NULL;
    
    // Находим минимальное число в исходном дереве
    int minValue = findTreeMinValue(originalRoot);
    printf("\nМинимальное число в дереве: %d\n", minValue);
    
    // Вычисляем сколько нужно добавить
    int remainingSum = targetSum - minValue;
    printf("Сумма которую нужно достичь: %d\n", targetSum);
    printf("Уже есть от минимального числа: %d\n", minValue);
    printf("Осталось добавить: %d\n", remainingSum);
    
    if (remainingSum <= 0) {
        printf("Сумма уже достигнута! Возвращаем только минимальное число.\n");
        return createTreeNode(minValue);
    }
    
    // Создаем новое дерево, начиная с минимального числа
    struct TreeNode* newRoot = createTreeNode(minValue);
    int currentSum = minValue;
    
    srand(time(NULL) + 1);
    
    printf("\nДостройка дерева методом параллельных пар:\n");
    
    int iteration = 0;
    int maxIterations = 20;
    
    while (currentSum < targetSum && iteration < maxIterations) {
        // Генерируем пару чисел, которые будут параллельными ветками
        int maxNum = (targetSum - currentSum) / 2;
        if (maxNum < 1) maxNum = 1;
        if (maxNum > 50) maxNum = 50;
        
        int num1 = (rand() % maxNum) + 1;
        int num2 = (targetSum - currentSum) - num1;
        
        // Корректируем числа если нужно
        if (num2 <= 0) {
            num1 = targetSum - currentSum;
            num2 = 0;
        }
        else if (num2 > 100) {
            num2 = 100;
            num1 = (targetSum - currentSum) - num2;
            if (num1 <= 0) {
                num1 = 1;
                num2 = targetSum - currentSum - num1;
            }
        }
        
        printf("Итерация %d: добавляем параллельную пару (%d, %d)\n", iteration + 1, num1, num2);
        
        // Находим узел для вставки параллельных веток
        struct TreeNode* insertionNode = newRoot;
        
        // С вероятностью 50% выбираем другой узел для разнообразия
        if (rand() % 2 == 0 && newRoot->left != NULL) {
            insertionNode = newRoot->left;
        }
        else if (rand() % 2 == 0 && newRoot->right != NULL) {
            insertionNode = newRoot->right;
        }
        
        // Добавляем пару как параллельные ветки
        if (insertionNode->left == NULL && num1 > 0) {
            int leftNum = (num1 < num2) ? num1 : num2;
            insertionNode->left = createTreeNode(leftNum);
            currentSum += leftNum;
            printf("Добавлено в левую ветку: %d\n", leftNum);
        }
        else if (insertionNode->left != NULL && num1 > 0) {
            struct TreeNode* temp = insertionNode->left;
            while (temp->right != NULL) {
                temp = temp->right;
            }
            int leftNum = (num1 < num2) ? num1 : num2;
            temp->right = createTreeNode(leftNum);
            currentSum += leftNum;
            printf("Добавлено в правую ветку левого поддерева: %d\n", leftNum);
        }
        
        if (insertionNode->right == NULL && num2 > 0) {
            int rightNum = (num1 > num2) ? num1 : num2;
            insertionNode->right = createTreeNode(rightNum);
            currentSum += rightNum;
            printf("Добавлено в правую ветку: %d\n", rightNum);
        }
        else if (insertionNode->right != NULL && num2 > 0) {
            struct TreeNode* temp = insertionNode->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            int rightNum = (num1 > num2) ? num1 : num2;
            temp->left = createTreeNode(rightNum);
            currentSum += rightNum;
            printf("Добавлено в левую ветку правого поддерева: %d\n", rightNum);
        }
        
        printf("Текущая сумма: %d\n", currentSum);
        iteration++;
        
        // Если осталась маленькая сумма, добавляем ее
        if (targetSum - currentSum > 0 && targetSum - currentSum <= 10) {
            int finalNum = targetSum - currentSum;
            if (newRoot->left == NULL) {
                newRoot->left = createTreeNode(finalNum);
            } else if (newRoot->right == NULL) {
                newRoot->right = createTreeNode(finalNum);
            } else {
                struct TreeNode* temp = newRoot->left;
                while (temp->right != NULL) {
                    temp = temp->right;
                }
                temp->right = createTreeNode(finalNum);
            }
            currentSum += finalNum;
            printf("Добавляем остаток: %d\n", finalNum);
            printf("Итоговая сумма: %d\n", currentSum);
            break;
        }
    }
    
    // Если после всех итераций сумма не достигнута, добавляем остаток
    if (currentSum < targetSum) {
        int finalNum = targetSum - currentSum;
        if (newRoot->left == NULL) {
            newRoot->left = createTreeNode(finalNum);
        } else if (newRoot->right == NULL) {
            newRoot->right = createTreeNode(finalNum);
        } else {
            struct TreeNode* temp = newRoot->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            temp->left = createTreeNode(finalNum);
        }
        currentSum += finalNum;
        printf("Добавляем финальный остаток: %d\n", finalNum);
    }
    
    printf("Итоговая сумма: %d\n", currentSum);
    return newRoot;
}

// Посчитать сумму всех элементов дерева (для проверки)
int sumTree(struct TreeNode* root) {
    if (root == NULL) return 0;
    return root->key + sumTree(root->left) + sumTree(root->right);
}

// Главная функция Lab_4
int run_lab4(void) {
    printf("\n=== LAB_4: РАБОТА С БИНАРНЫМИ ДЕРЕВЬЯМИ ===\n\n");
    
    struct TreeNode* root = NULL;
    
    // 1. Генерируем числа, записываем в файл и сразу считаем сумму
    printf("1. Генерация данных:\n");
    int arraySum = generateNumbersToFile();
    printf("Сумма всех элементов массива: %d\n\n", arraySum);
    
    // 2. Читаем числа из файла и строим дерево
    printf("2. Построение дерева:\n");
    root = readNumbersAndBuildTree();
    
    if (root == NULL) {
        printf("Не удалось построить дерево!\n");
        return 1;
    }
    printf("\n");
    
    // 3. Показываем дерево
    printf("3. Получившееся дерево:\n");
    printTree(root);
    printf("\n");
    
    // 4. Ищем особые вершины
    printf("4. Поиск особых вершин:\n");
    printf("(у которых равны высоты или количество потомков)\n\n");
    
    int result = countTreeSpecialNodes(root);
    printf("\nВсего найдено особых вершин: %d\n\n", result);
    
    // 5. Спрашиваем о достройке графа
    char choice;
    printf("5. Достроить граф от минимального числа? (y/n): ");
    scanf(" %c", &choice);
    
    if (choice == 'y' || choice == 'Y') {
        printf("\n=== ДОСТРОЙКА ГРАФА ===\n");
        
        // Достраиваем граф от минимального числа
        struct TreeNode* extendedRoot = extendGraphFromMin(root, arraySum);
        
        if (extendedRoot != NULL) {
            printf("\nНовое дерево (построено от минимального числа %d):\n", findTreeMinValue(root));
            printTree(extendedRoot);
            
            // Проверяем сумму
            int newSum = sumTree(extendedRoot);
            printf("\nПроверка суммы:\n");
            printf("Сумма нового дерева: %d\n", newSum);
            printf("Целевая сумма была: %d\n", arraySum);
            printf("Суммы %s\n", newSum == arraySum ? "СОВПАДАЮТ!" : "НЕ СОВПАДАЮТ!");
            
            // Удаляем новое дерево
            deleteTree(&extendedRoot);
            printf("Новое дерево удалено из памяти.\n");
        }
    }
    
    // Удаляем исходное дерево
    deleteTree(&root);
    printf("\nИсходное дерево удалено из памяти.\n");
    
    return 0;
}
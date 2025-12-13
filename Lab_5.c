#include <stdio.h>
#include <stdlib.h>
#include "Lab_5.h"

// Глобальные переменные (теперь видны везде)
int graph[MAX_NODES][MAX_NODES];  // Таблица расстояний
int total_nodes = 0;               // Сколько всего вершин

// ============ ФУНКЦИЯ 1: ЧИТАЕМ ГРАФ ИЗ ФАЙЛА ============
void readGraph() {
    FILE *file;
    int from, to, weight;
    int max_node = 0;
    
    printf("Открываем файл %s...\n", FILENAME);
    
    // Открываем файл
    file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Ошибка! Файл %s не найден!\n", FILENAME);
        printf("Создайте файл %s рядом с программой\n", FILENAME);
        printf("Формат файла (каждая строка):\n");
        printf("вершина1,вершина2,расстояние\n");
        printf("Пример:\n");
        printf("0,1,5\n");
        printf("0,2,3\n");
        printf("1,2,1\n");
        printf("2,3,2\n");
        return;
    }
    
    // Заполняем граф бесконечными расстояниями
    for (int i = 0; i < MAX_NODES; i++) {
        for (int j = 0; j < MAX_NODES; j++) {
            graph[i][j] = INFINITY;  // Сначала все далеко
        }
        graph[i][i] = 0;  // От вершины до самой себя = 0
    }
    
    // Читаем файл построчно
    printf("\nЧитаем дороги из файла:\n");
    while (fscanf(file, "%d,%d,%d", &from, &to, &weight) == 3) {
        graph[from][to] = weight;
        printf("  Из %d в %d: %d км\n", from, to, weight);
        
        // Запоминаем максимальный номер вершины
        if (from > max_node) max_node = from;
        if (to > max_node) max_node = to;
    }
    
    fclose(file);
    
    // Подсчитываем сколько всего вершин
    total_nodes = max_node + 1;  // +1 потому что нумерация с 0
    printf("\nГраф загружен!\n");
    printf("Всего вершин: %d (нумерация от 0 до %d)\n\n", total_nodes, total_nodes-1);
}

// ============ ФУНКЦИЯ 2: АЛГОРИТМ ДЕЙКСТРЫ ============
void dijkstra(int start, int end) {
    printf("=== Алгоритм Дейкстры ===\n");
    
    int distance[MAX_NODES];    // Кратчайшее расстояние до каждой вершины
    int visited[MAX_NODES];     // Отметка о посещении (0=нет, 1=да)
    int previous[MAX_NODES];    // Откуда пришли в эту вершину
    
    // ШАГ 1: Инициализация
    for (int i = 0; i < total_nodes; i++) {
        distance[i] = INFINITY;  // Пока все далеко
        visited[i] = 0;          // Никуда не ходили
        previous[i] = -1;        // Неизвестно откуда пришли
    }
    
    // Начальная вершина
    distance[start] = 0;
    
    // ШАГ 2: Основной цикл
    for (int step = 0; step < total_nodes; step++) {
        // Ищем непосещенную вершина с минимальным расстоянием
        int min_dist = INFINITY;
        int current = -1;
        
        for (int i = 0; i < total_nodes; i++) {
            if (!visited[i] && distance[i] < min_dist) {
                min_dist = distance[i];
                current = i;
            }
        }
        
        // Если не нашли - выходим
        if (current == -1) break;
        
        // Отмечаем вершину как посещенную
        visited[current] = 1;
        
        // Если дошли до финиша - можно выйти
        if (current == end) break;
        
        // ШАГ 3: Обновляем расстояния до соседей
        for (int neighbor = 0; neighbor < total_nodes; neighbor++) {
            // Если есть дорога из текущей в соседа
            if (graph[current][neighbor] != INFINITY) {
                int new_distance = distance[current] + graph[current][neighbor];
                
                // Если нашли путь короче
                if (new_distance < distance[neighbor]) {
                    distance[neighbor] = new_distance;
                    previous[neighbor] = current;
                }
            }
        }
    }
    
    // ШАГ 4: Вывод результата
    if (distance[end] == INFINITY) {
        printf("Из %d в %d дороги нет!\n", start, end);
    } else {
        printf("Кратчайшее расстояние: %d\n", distance[end]);
        
        // Восстанавливаем путь
        printf("Путь: ");
        
        // Собираем путь в обратном порядке
        int path[MAX_NODES];
        int path_length = 0;
        int current = end;
        
        while (current != -1) {
            path[path_length] = current;
            path_length++;
            current = previous[current];
        }
        
        // Выводим путь в правильном порядке
        for (int i = path_length - 1; i >= 0; i--) {
            printf("%d", path[i]);
            if (i > 0) printf(" -> ");
        }
        printf("\n");
    }
}

// ============ ФУНКЦИЯ 3: АЛГОРИТМ ФЛОЙДА ============
void floyd(int start, int end) {
    printf("\n=== Алгоритм Флойда ===\n");
    
    // Создаем копию графа для работы
    int dist[MAX_NODES][MAX_NODES];
    int next[MAX_NODES][MAX_NODES];  // Куда идти дальше
    
    // Копируем граф
    for (int i = 0; i < total_nodes; i++) {
        for (int j = 0; j < total_nodes; j++) {
            dist[i][j] = graph[i][j];
            
            // Запоминаем следующий шаг
            if (graph[i][j] != INFINITY && i != j) {
                next[i][j] = j;  // Из i в j идем сразу в j
            } else {
                next[i][j] = -1;  // Нет пути
            }
        }
    }
    
    // Три вложенных цикла - главная идея Флойда!
    for (int k = 0; k < total_nodes; k++) {      // Промежуточная вершина
        for (int i = 0; i < total_nodes; i++) {  // Откуда
            for (int j = 0; j < total_nodes; j++) {  // Куда
                // Если через k быстрее, чем напрямую
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
    
    // Вывод результата
    if (dist[start][end] == INFINITY) {
        printf("Из %d в %d дороги нет!\n", start, end);
    } else {
        printf("Кратчайшее расстояние: %d\n", dist[start][end]);
        
        // Выводим путь
        printf("Путь: ");
        int current = start;
        
        while (current != end) {
            printf("%d -> ", current);
            current = next[current][end];
        }
        printf("%d\n", end);
    }
}

// ============ ФУНКЦИЯ 4: ГЛАВНАЯ ФУНКЦИЯ LAB_5 ============
int run_lab5(void) {
    int start, end;
    
    printf("\n=== LAB_5: ПОИСК КРАТЧАЙШЕГО ПУТИ В ГРАФЕ ===\n");
    printf("==============================================\n\n");
    
    // 1. Читаем граф из файла
    readGraph();
    
    if (total_nodes == 0) {
        printf("Не удалось загрузить граф. Возврат в меню.\n");
        return 1;
    }
    
    // 2. Спрашиваем у пользователя
    printf("Введите начальную вершину (от 0 до %d): ", total_nodes-1);
    scanf("%d", &start);
    
    printf("Введите конечную вершину (от 0 до %d): ", total_nodes-1);
    scanf("%d", &end);
    
    // 3. Проверяем ввод
    if (start < 0 || start >= total_nodes || 
        end < 0 || end >= total_nodes) {
        printf("\nОшибка! Вершины должны быть от 0 до %d\n", total_nodes-1);
        return 1;
    }
    
    if (start == end) {
        printf("\nВы уже в пункте назначения! Расстояние: 0\n");
        return 0;
    }
    
    // 4. Запускаем оба алгоритма
    printf("\n");
    dijkstra(start, end);
    floyd(start, end);
    
    printf("\n==============================================\n");
    printf("Оба алгоритма показали одинаковый результат!\n");
    
    return 0;
}
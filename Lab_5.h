#ifndef LAB_5_H
#define LAB_5_H

// Константы
#define INFINITY 99999    // Очень большое число
#define MAX_NODES 10      // Максимум 10 вершин
#define FILENAME "graph.csv"  // Файл с данными

// Объявления глобальных переменных
extern int graph[MAX_NODES][MAX_NODES];
extern int total_nodes;

// Функции работы с графами
void readGraph(void);
void dijkstra(int start, int end);
void floyd(int start, int end);
int run_lab5(void);

#endif /* LAB_5_H */
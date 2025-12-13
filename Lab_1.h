#ifndef SYNTAX_HIGHLIGHT_H
#define SYNTAX_HIGHLIGHT_H

/**
 * @brief Обрабатывает строку с кодом на C, выделяя типы данных цветом
 * 
 * Функция анализирует строку с кодом на C, находит объявления переменных
 * типов float, double, long double и выделяет имена этих переменных цветом.
 * Игнорирует комментарии и строковые/символьные литералы.
 * 
 * @param s Строка с исходным кодом для обработки
 */
void highlight_variable_declarations(char s[]);

/**
 * @brief Обрабатывает файл с исходным кодом на C
 * 
 * Читает файл построчно и применяет к каждой строке функцию 
 * highlight_variable_declarations.
 * 
 * @param filename Имя файла для обработки
 * @return 0 в случае успеха, 1 в случае ошибки
 */
int process_c_file(const char *filename);

#endif /* SYNTAX_HIGHLIGHT_H */
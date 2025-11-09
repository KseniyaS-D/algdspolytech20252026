#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>


#define MAX_VERTICES 100

bool dfs(int graph[MAX_VERTICES][MAX_VERTICES], int vertices, int start, int end, bool visited[]) {
    if (start == end) {
        return true;
    }

    visited[start] = true;

    for (int i = 0; i < vertices; i++) {
        if (graph[start][i] == 1 && !visited[i]) {
            if (dfs(graph, vertices, i, end, visited)) {
                return true;
            }
        }
    }

    return false;
}

bool path_exists(int graph[MAX_VERTICES][MAX_VERTICES], int vertices, int start, int end) {
    bool visited[MAX_VERTICES] = { false };
    return dfs(graph, vertices, start, end, visited);
}

int main() {
    setlocale(LC_CTYPE, "Russian");
    FILE* input_file = fopen("input.txt", "r");
    FILE* output_file = fopen("output.txt", "w");

    if (input_file == NULL) {
        printf("Ошибка открытия файла input.txt\n");
        return 1;
    }
    if (output_file == NULL) {
        printf("Ошибка открытия файла output.txt\n");
        fclose(input_file);
        return 1;
    }

    int vertices;
    int graph[MAX_VERTICES][MAX_VERTICES];
    int start, end;

    // Проверяем успешность чтения количества вершин
    if (fscanf(input_file, "%d", &vertices) != 1) {
        printf("Ошибка чтения количества вершин\n");
        fclose(input_file);
        fclose(output_file);
        return 1;
    }

    // Проверяем границы
    if (vertices <= 0 || vertices > MAX_VERTICES) {
        printf("Ошибка: некорректное количество вершин: %d\n", vertices);
        fclose(input_file);
        fclose(output_file);
        return 1;
    }

    // Читаем матрицу смежности
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (fscanf(input_file, "%d", &graph[i][j]) != 1) {
                printf("Ошибка чтения матрицы смежности\n");
                fclose(input_file);
                fclose(output_file);
                return 1;
            }
        }
    }

    // Читаем начальную и конечную вершины
    if (fscanf(input_file, "%d %d", &start, &end) != 2) {
        printf("Ошибка чтения номеров вершин\n");
        fclose(input_file);
        fclose(output_file);
        return 1;
    }

    // Проверяем корректность номеров вершин
    if (start < 0 || start >= vertices || end < 0 || end >= vertices) {
        printf("Ошибка: некорректные номера вершин: %d, %d\n", start, end);
        printf("Допустимый диапазон: 0..%d\n", vertices - 1);
        fclose(input_file);
        fclose(output_file);
        return 1;
    }

    fclose(input_file);

    // Проверяем существование пути
    bool exists = path_exists(graph, vertices, start, end);

    // Записываем результат
    if (exists) {
        fprintf(output_file, "YES\n");
        printf("Путь между вершинами %d и %d: ДА\n", start, end);
    }
    else {
        fprintf(output_file, "NO\n");
        printf("Путь между вершинами %d и %d: НЕТ\n", start, end);
    }

    fclose(output_file);

    return 0;
}
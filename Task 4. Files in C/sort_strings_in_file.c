#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// чтение строки из файла до первого \n
char* get_row(FILE*);

// максимальная длина строки в файле
int max_length_of_string(FILE*);

// сортировка строк в файле без копирования в ОП
void sort_strings(FILE*, int);

int main() {
    FILE *source;
    if ((source = fopen("tmp", "r+")) == NULL)
        return 1;

    sort_strings(source, max_length_of_string(source) + 3);

    return 0;
}

char* get_row(FILE *file) {
    char *result;
    int size = 0;
    result = (char*)malloc(sizeof(char));

    char c;
    while ((c = fgetc(file)) != '\n') {
        if (c == EOF) {
            free(result);
            return NULL;
        }
        result[size++] = c;
        result = (char*)realloc(result, sizeof(char) * (size + 1));
    }

    return result;
}

int max_length_of_string(FILE* file) {
    int result = 0;
    
    char* s;
    while ((s = get_row(file)) != NULL) {
        if (strlen(s) > result)
            result = strlen(s);
    }

    return result;
}

void sort_strings(FILE *file, int max_length) { // сортировка выбором
    long max_length_offset, current_offset, sorted_offset;
    int current_max_length = 0, current_length;
    char current_string[max_length], longest_string[max_length];
    fseek(file, 0, SEEK_END);

    sorted_offset = ftell(file);

    while (sorted_offset != 0) {
        fseek(file, 0, SEEK_SET);
        current_offset = 0;
        max_length_offset = 0;
        current_max_length = 0;

        // ищем строку с максимальной длиной
        while (current_offset != sorted_offset) {
            fgets(current_string, max_length, file);
            if (current_max_length <= strlen(current_string)) {
                current_max_length = strlen(current_string);
                max_length_offset = current_offset;
            }
            current_offset = ftell(file);
        }

        fseek(file, max_length_offset, SEEK_SET);
        fgets(longest_string, max_length, file);

        long left_offset = max_length_offset, right_offset = ftell(file);
        
        // все строки после максимальной сдвигаем налево ровно на длину максимальной
        while (right_offset != sorted_offset) {
            fgets(current_string, max_length, file);
            right_offset = ftell(file);
            fseek(file, left_offset, SEEK_SET);
            fputs(current_string, file);
            left_offset = ftell(file);
            fseek(file, right_offset, SEEK_SET);
        }
        sorted_offset = left_offset;
        fseek(file, left_offset, SEEK_SET);

        // записываем максимальную длину в конец
        fputs(longest_string, file);
    }
    return;
}
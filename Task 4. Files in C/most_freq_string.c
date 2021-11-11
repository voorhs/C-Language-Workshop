#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// чтение строки из файла до первого \n
char* get_row(FILE*);

// печать строки, встречающейся чаще других
void the_most_frequent_string(FILE*);

int main() {
    FILE *source;
    if ((source = fopen("tmp", "r")) == NULL)
        return 1;
    
    the_most_frequent_string(source);

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

void the_most_frequent_string(FILE* file) { // классический алгоритм на подсчёт совпадений для каждого элемента, квадратичная сложность
    fseek(file, 0, SEEK_SET);
    char *pivot_string, *current_string;
    int max_frequency = 0, pivot_frequency, pivot_offset = 0, most_frequent_string_offset = 0, next_string_offset;
    
    while ((pivot_string = get_row(file)) != NULL) {
        pivot_offset = next_string_offset;
        next_string_offset = ftell(file);
        pivot_frequency = 1;

        while ((current_string = get_row(file)) != NULL) {
            if (strcmp(current_string, pivot_string) == 0)
                pivot_frequency++;
        }

        if (pivot_frequency > max_frequency) {
            max_frequency = pivot_frequency;
            most_frequent_string_offset = pivot_offset;
        }
        
        fseek(file, next_string_offset, SEEK_SET);
    }

    fseek(file, most_frequent_string_offset, SEEK_SET);
    printf("%s\n", get_row(file));
}
#include <stdio.h>
#include <stdlib.h>

char* read_string() {
    char *result = (char*)malloc(sizeof(char)), c;

    int size_of_str = 0, size_alloc = sizeof(char);

    while ((c = getchar()) != '\n') {
        if (++size_of_str > size_alloc) {
            size_alloc *= 2;
            result = realloc(result, size_alloc);
        }
        result[size_of_str - 1] = c;
    }

    if (size_of_str == size_alloc)
        result = realloc(result, size_of_str + 1);
    result[size_of_str] = '\0';

    if (size_of_str = 0)
        return NULL;
    else
        return result;
}

int main() {
    char *s;
    s = read_string();
    printf("result is %s\n", s);
    return 0;
}
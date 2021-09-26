#include <stdio.h>
#include <stdlib.h>

char* read_string() {
    char *result = (char*)malloc(sizeof(char)), c;

    int size_of_str = 0, size_alloc = sizeof(char);

    while (((c = getchar()) != '\n') && (c != EOF)) {
        if (++size_of_str > size_alloc) {
            size_alloc *= 2;
            result = realloc(result, size_alloc);
        }
        result[size_of_str - 1] = c;
    }

    if (size_of_str == size_alloc)
        result = realloc(result, size_of_str + 1);
    result[size_of_str] = '\0';

    if (size_of_str == 0) {
        free(result);
        return NULL;
    }
    else
        return result;
}

char** read_str_array() {
    char **result = (char**)malloc(sizeof(char*));

    int size_alloc = 1, str_count = 0;

    while (1) {
        if (str_count == size_alloc) {
            size_alloc *= 2;
            result = (char**)realloc(result, size_alloc);
        }            
        result[str_count] = read_string();
        if (result[str_count] == NULL)
            break;
        else
            str_count++;                    //check whether str_count can be placed in while or not
    }

    if (str_count == 0)
        return NULL;
    else
        return result;

}

int main() {
    char **sarray = read_str_array();
    return 0;
}
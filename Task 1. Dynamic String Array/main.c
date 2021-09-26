#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_string();                
char** read_str_array();            
void print_str_array(char**);
int array_length(char**);
void sort_str_array(char**, int);

int main() {
    char **sarray = read_str_array();

    printf("\n%s\n", "You typed:");
    print_str_array(sarray);

    sort_str_array(sarray, array_length(sarray));
    printf("\n%s\n", "Sorted:");
    print_str_array(sarray);
    printf("\n\n");

    free(sarray);
    return 0;
}


char* read_string() {
    char *result = (char*)malloc(sizeof(char)), c;

    int size_of_str = 0, size_alloc = sizeof(char);

    while (((c = getchar()) != '\n') && (c != EOF)) {
        if (++size_of_str * sizeof(char) > size_alloc) {
            size_alloc *= 2;
            result = realloc(result, size_alloc);
        }
        result[size_of_str - 1] = c;
    }

    if (size_of_str == size_alloc)
        result = realloc(result, size_of_str + 1);
    result[size_of_str] = '\0';

    if (c == EOF)
        return NULL;
    else
        return result;    
}

char** read_str_array() {
    char **result = (char**)malloc(sizeof(char*));

    int size_alloc = sizeof(char*), str_count = 0;

    while (1) {
        if (str_count * sizeof(char*) == size_alloc) {
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

void print_str_array(char** sarray) {
    int i;
    for(i = 0; sarray[i]; i++) {
        printf("%s\n", sarray[i]);
    }
}

int array_length(char** arr) {
    int res;
    for (res = 0; arr[res]; res++) {}
    return res;
}

void sort_str_array(char** sarray, int size)
{
    int i, j;
    for (i = 0; i < size - 1; i++)
        for (j = size - 1; j > i; j--)
            if (strcmp(sarray[j - 1], sarray[j]) > 0) {
                char* temp = sarray[j - 1];
                sarray[j - 1] = sarray[j];
                sarray[j] = temp;
            }
}


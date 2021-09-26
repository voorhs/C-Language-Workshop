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
        result[size_of_str++] = c;
        size_alloc += sizeof(char);
        result = realloc(result, size_alloc);
    }
    result[size_of_str] = '\0';

    if (c == EOF)
        return NULL;
    else
        return result;    
}

char** read_str_array() {
    char **result = (char**)malloc(sizeof(char*));
    result[0] = read_string();

    int size_alloc = sizeof(char**), str_count = 0;

    while (result[str_count]) {
        size_alloc += sizeof(char**);
        result = (char**)realloc(result, size_alloc);
        result[++str_count] = read_string();
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